#!/usr/bin/env python3
"""Консольная утилита записи через UART-загрузчик К1921ВГ7Т.

Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
Telegram: https://t.me/oDeXteRo

Реализует протокол НИИЭТ из k1921vkx_flasher/NOTES.md (те же пакеты, что и у графического
прошивальщика НИИЭТ), но без окна, чтобы проект мог прошивать из скрипта.

Подключение платы NIIET-MINI-K1921VG7T rev 2.0 (перемычки XP3 и XP4 установлены):
    CH340B RTS# -> XP3 -> BOOT.EN# (A6)   pyserial rts=True -> A6 low -> режим загрузчика
    CH340B DTR# -> XP4 -> BOOT.RST#       pyserial dtr=True -> сброс удерживается

Загрузчик занимает 0x0000-0x1FFF и отказывается трогать эти страницы, поэтому утилита
отказывается писать по адресам ниже 0x2000.

Примеры:
    uart_flash.py --list                   список последовательных портов
    uart_flash.py --info                   сведения о кристалле и загрузчике
    uart_flash.py app.bin                  записать с 0x2000, проверить, запустить
    uart_flash.py app.bin --addr 0x2000 --no-run
    uart_flash.py --run                    выйти из загрузчика и запустить приложение
    uart_flash.py --reset                  только аппаратный сброс МК импульсом DTR (перемычка XP4)
"""
import argparse
import sys
import time

try:
    import serial
    import serial.tools.list_ports
except ImportError:
    sys.exit("Не установлен pyserial: pip install pyserial")

SIGN_HOST = 0x5C81
SIGN_DEVICE = 0x7EA3

CMD_GET_INFO = 0x35
CMD_WRITE_PAGE = 0x9A
CMD_READ_PAGE = 0xA5
CMD_EXIT = 0xF5
CMD_MSG = 0xFA

MSG_ERR_CMD, MSG_ERR_CRC, MSG_READY, MSG_OK, MSG_FAIL = 1, 2, 3, 4, 5
MSG_NAMES = {1: "ERR_CMD", 2: "ERR_CRC", 3: "READY", 4: "OK", 5: "FAIL"}

PAGE_SIZE = 1024            # K1921VG7T flash page
BOOT_END = 0x2000           # first byte after the bootloader
FLASH_SIZE = 0x80000

CH340_VID_PID = (0x1A86, 0x7523)


class ProtocolError(Exception):
    pass


def crc16(data, crc=0):
    """CRC16 из протокола НИИЭТ (полином CCITT 0x1021, байты старшим битом вперёд, без дополнения)."""
    for byte in data:
        crc &= 0xFFFF
        d = (byte & 0xFF) | 0x100
        while not (d & 0x10000):
            crc <<= 1
            d <<= 1
            if d & 0x100:
                crc += 1
            if crc & 0x10000:
                crc ^= 0x1021
    return crc & 0xFFFF


def build_packet(cmd, payload=b""):
    if len(payload) % 4:
        raise ValueError("payload length must be a multiple of 4")
    body = bytes([cmd, (~cmd) & 0xFF]) + len(payload).to_bytes(2, "little") + payload
    return SIGN_HOST.to_bytes(2, "little") + body + crc16(body).to_bytes(2, "little")


class Bootloader:
    def __init__(self, port, baud=115200, verbose=False):
        self.verbose = verbose
        self.ser = serial.Serial()
        self.ser.port = port
        self.ser.baudrate = baud
        self.ser.timeout = 2
        self.ser.dtr = False
        self.ser.rts = False
        self.ser.open()

    def close(self):
        self.ser.rts = False
        self.ser.dtr = False
        self.ser.close()

    # ---- low level ------------------------------------------------------
    def _read_exact(self, n):
        data = self.ser.read(n)
        if len(data) != n:
            raise ProtocolError(f"timeout: wanted {n} bytes, got {len(data)}")
        return data

    def _recv(self):
        """Читает один пакет устройства, возвращает (код сообщения, код команды, данные после заголовка)."""
        sig = b""
        deadline = time.time() + 5
        while time.time() < deadline:
            b = self.ser.read(1)
            if not b:
                continue
            sig = (sig + b)[-2:]
            if sig == SIGN_DEVICE.to_bytes(2, "little"):
                break
        else:
            raise ProtocolError("no device packet signature")
        head = self._read_exact(4)
        cmd, inv = head[0], head[1]
        n = int.from_bytes(head[2:4], "little")
        if cmd != (~inv & 0xFF):
            raise ProtocolError("bad command inversion in reply")
        payload = self._read_exact(n)
        crc_rx = int.from_bytes(self._read_exact(2), "little")
        if crc_rx != crc16(head + payload):
            raise ProtocolError("reply CRC mismatch")
        if cmd != CMD_MSG or n < 4:
            raise ProtocolError(f"unexpected reply cmd=0x{cmd:02X} n={n}")
        if self.verbose:
            print(f"  <- msg={MSG_NAMES.get(payload[0], payload[0])} cmd=0x{payload[1]:02X} n={n}")
        return payload[0], payload[1], payload[4:]

    def _xfer(self, cmd, payload=b"", expect=MSG_OK):
        self.ser.write(build_packet(cmd, payload))
        msg, rcmd, data = self._recv()
        if msg != expect:
            raise ProtocolError(
                f"command 0x{cmd:02X}: device answered {MSG_NAMES.get(msg, msg)} "
                f"(cmd echo 0x{rcmd:02X})")
        return data

    # ---- connection -----------------------------------------------------
    def enter_bootloader(self):
        """Сбрасывает МК при низком BOOT.EN#, настраивает скорость байтом 0x7F, ждёт READY."""
        ser = self.ser
        ser.reset_input_buffer()
        ser.rts = True           # BOOT.EN# (A6) в низкий уровень
        ser.dtr = True           # сброс включён
        time.sleep(0.15)
        ser.dtr = False          # сброс снят, МК стартует с низким A6 и входит в загрузчик
        time.sleep(0.4)
        ser.reset_input_buffer()
        ser.write(b"\x7F")
        ack = ser.read(2)
        if ack != SIGN_DEVICE.to_bytes(2, "big"):
            raise ProtocolError(
                f"no bootloader answer (got {ack.hex() or 'nothing'}). Check jumpers XP3 and XP4, "
                "that the bootloader is flashed (run.ps1 boot-flash) and the COM port.")
        ser.rts = False          # отпускаем BOOT.EN#
        msg, cmd, _ = self._recv()
        if msg != MSG_READY:
            raise ProtocolError(f"expected READY, got {MSG_NAMES.get(msg, msg)}")

    def info(self):
        d = self._xfer(CMD_GET_INFO)
        chipid = int.from_bytes(d[0:4], "little")
        cpuid = int.from_bytes(d[4:8], "little")
        ver = int.from_bytes(d[8:12], "little")
        return chipid, cpuid, f"{ver >> 16}.{ver & 0xFFFF}"

    def write_page(self, addr, page):
        assert len(page) == PAGE_SIZE and addr % PAGE_SIZE == 0
        cfg = 1 << 6                                  # сначала стереть страницу, основная область, flash 0
        payload = addr.to_bytes(3, "little") + bytes([cfg]) + page
        self._xfer(CMD_WRITE_PAGE, payload)

    def read_page(self, addr):
        payload = addr.to_bytes(3, "little") + bytes([0])
        d = self._xfer(CMD_READ_PAGE, payload)
        return bytes(d[4:4 + PAGE_SIZE])

    def run(self):
        """Выходит из загрузчика: аппаратный сброс при отпущенном BOOT.EN#."""
        self.ser.rts = False
        self.ser.dtr = True
        time.sleep(0.15)
        self.ser.dtr = False


def find_port():
    for p in serial.tools.list_ports.comports():
        if (p.vid, p.pid) == CH340_VID_PID:
            return p.device
    return None


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("image", nargs="?", help="файл .bin для записи")
    ap.add_argument("--port", help="COM-порт (по умолчанию первый найденный CH340)")
    ap.add_argument("--addr", type=lambda x: int(x, 0), default=BOOT_END, help="адрес во Flash (по умолчанию 0x2000)")
    ap.add_argument("--list", action="store_true", help="показать последовательные порты и выйти")
    ap.add_argument("--info", action="store_true", help="показать сведения о кристалле и загрузчике и выйти")
    ap.add_argument("--reset", action="store_true", help="только аппаратный сброс МК импульсом DTR и выход")
    ap.add_argument("--run", action="store_true", help="выйти из загрузчика и запустить приложение")
    ap.add_argument("--no-verify", action="store_true")
    ap.add_argument("--no-run", action="store_true", help="остаться в загрузчике после записи")
    ap.add_argument("-v", "--verbose", action="store_true")
    args = ap.parse_args()

    if args.list:
        for p in serial.tools.list_ports.comports():
            print(f"{p.device:8} {p.vid or 0:04X}:{p.pid or 0:04X}  {p.description}")
        return 0

    port = args.port or find_port()
    if not port:
        sys.exit("Порт CH340 не найден, укажите --port COMx")

    if args.reset:
        # Сброс по линии DTR (перемычка XP4), RTS отпущен: МК стартует в обычном режиме.
        # Это настоящий аппаратный сброс; он же снимает зависание флеш-контроллера.
        ser = serial.Serial(port, 115200)
        ser.rts = False
        ser.dtr = True
        time.sleep(0.2)
        ser.dtr = False
        time.sleep(0.3)
        ser.close()
        print(f"Аппаратный сброс по DTR выполнен ({port})")
        return 0

    image = None
    if args.image:
        image = open(args.image, "rb").read()
        if args.addr < BOOT_END:
            sys.exit("Запись ниже 0x2000 запрещена: эта область принадлежит загрузчику")
        if args.addr % PAGE_SIZE:
            sys.exit("Адрес должен быть кратен размеру страницы (1024)")
        if args.addr + len(image) > FLASH_SIZE:
            sys.exit("Образ не помещается во Flash")

    bl = Bootloader(port, verbose=args.verbose)
    try:
        print(f"Порт {port}: вход в загрузчик ...")
        bl.enter_bootloader()
        chipid, cpuid, ver = bl.info()
        print(f"Загрузчик {ver}, SIU.CHIPID=0x{chipid:08X}, SCB.CPUID=0x{cpuid:08X}")

        if image is not None:
            pages = [image[i:i + PAGE_SIZE].ljust(PAGE_SIZE, b"\xFF") for i in range(0, len(image), PAGE_SIZE)]
            t0 = time.time()
            for n, page in enumerate(pages):
                addr = args.addr + n * PAGE_SIZE
                bl.write_page(addr, page)
                print(f"\rзапись {n + 1}/{len(pages)} (0x{addr:05X})", end="", flush=True)
            print(f"\nЗаписано {len(image)} байт за {time.time() - t0:.1f} с")
            if not args.no_verify:
                for n, page in enumerate(pages):
                    addr = args.addr + n * PAGE_SIZE
                    if bl.read_page(addr) != page:
                        raise ProtocolError(f"Проверка не прошла на странице 0x{addr:05X}")
                    print(f"\rпроверка {n + 1}/{len(pages)}", end="", flush=True)
                print("\nПроверка пройдена")

        if (image is not None and not args.no_run) or args.run:
            bl.run()
            print("Приложение запущено")
    except ProtocolError as e:
        print(f"ОШИБКА: {e}", file=sys.stderr)
        return 1
    finally:
        bl.close()
    return 0


if __name__ == "__main__":
    sys.exit(main())
