/*==============================================================================
 * UART загрузчик для К1921ВГXT
 *
 * Ядро загрузчика.
 * Обработка полученных комманд и формирование исходящих пакетов.
 *------------------------------------------------------------------------------
 * НИИЭТ, Александр Дыхно <dykhno@niiet.ru>
 * НИИЭТ, Штоколов Филипп
 * НИИЭТ, Долгополов Алексей <dolgopolov@niiet.ru>
 *==============================================================================
 * ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ПРЕДОСТАВЛЯЕТСЯ «КАК ЕСТЬ», БЕЗ КАКИХ-ЛИБО
 * ГАРАНТИЙ, ЯВНО ВЫРАЖЕННЫХ ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ ГАРАНТИИ ТОВАРНОЙ
 * ПРИГОДНОСТИ, СООТВЕТСТВИЯ ПО ЕГО КОНКРЕТНОМУ НАЗНАЧЕНИЮ И ОТСУТСТВИЯ
 * НАРУШЕНИЙ, НО НЕ ОГРАНИЧИВАЯСЬ ИМИ. ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ
 * ПРЕДНАЗНАЧЕНО ДЛЯ ОЗНАКОМИТЕЛЬНЫХ ЦЕЛЕЙ И НАПРАВЛЕНО ТОЛЬКО НА
 * ПРЕДОСТАВЛЕНИЕ ДОПОЛНИТЕЛЬНОЙ ИНФОРМАЦИИ О ПРОДУКТЕ, С ЦЕЛЬЮ СОХРАНИТЬ ВРЕМЯ
 * ПОТРЕБИТЕЛЮ. НИ В КАКОМ СЛУЧАЕ АВТОРЫ ИЛИ ПРАВООБЛАДАТЕЛИ НЕ НЕСУТ
 * ОТВЕТСТВЕННОСТИ ПО КАКИМ-ЛИБО ИСКАМ, ЗА ПРЯМОЙ ИЛИ КОСВЕННЫЙ УЩЕРБ, ИЛИ
 * ПО ИНЫМ ТРЕБОВАНИЯМ, ВОЗНИКШИМ ИЗ-ЗА ИСПОЛЬЗОВАНИЯ ПРОГРАММНОГО ОБЕСПЕЧЕНИЯ
 * ИЛИ ИНЫХ ДЕЙСТВИЙ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ.
 *
 *                              2026 АО "НИИЭТ"
 *==============================================================================
 */

#include "boot_core.h"
#include "boot_flash.h"
#include "boot_packet.h"
#include "stdbool.h"
#include <riscv-csr.h>
#include <string.h>

//-- Private variables ---------------------------------------------------------
static uint8_t bootflash_program[BOOT_FLASH_SIZE_TOTAL_BYTES]
    __attribute__((section(".ramvars")));

//-- Private function prototypes -----------------------------------------------
static void msg_cmd(Packet_TypeDef *packet);
static void get_info_cmd(Packet_TypeDef *packet);
static void get_cfgword_cmd(Packet_TypeDef *packet);
static void set_cfgword_cmd(Packet_TypeDef *packet);
static void read_page_cmd(Packet_TypeDef *packet);
static void write_page_cmd(Packet_TypeDef *packet);
static void jump_cmd(Packet_TypeDef *packet);
static void erase_cmd(Packet_TypeDef *packet);
static void exit_cmd(Packet_TypeDef *packet);
__attribute__((section(".ramfunc"), noinline)) static void
memcpy_ramfunc(uint8_t *to, uint8_t *from, uint32_t size);
__attribute__((section(".ramfunc"), noinline)) static void
memcpy_flash_ramfunc(uint32_t to_flash, uint32_t *from, uint32_t size);
__attribute__((section(".ramfunc"), noinline)) static void
flash_write_128_ramfunc(uint32_t addr, uint32_t *data);
__attribute__((section(".ramfunc"), noinline)) static void
flash_erase_full_ramfunc(void);
__attribute__((section(".ramfunc"), noinline)) static void
save_and_erase_all_ramfunc(void);

int wait_uart_rx(uint32_t value) {
//    uint32_t timeout_start;
//    TIMEOUT_TMR->CTRL_bit.MODE = 0;
//    TIMEOUT_TMR->CTRL_bit.CLR = 1;
//    timeout_start = TIMEOUT_TMR->COUNT;
//    TIMEOUT_TMR->CTRL_bit.MODE = 2;
#if UART_PIN_RX_POS < 8
  while ((bool)(UART_PORT->MASKLB[1 << UART_PIN_RX_POS].MASKLB) !=
         (bool)value) {
#else
  /* В исходнике НИИЭТ было MASKHB[1 << pos]. Для выводов 8..15 индекс - это маска старшего
   * байта, то есть 1 << (pos - 8). Вывод RX по умолчанию (A0) в эту ветку не попадал, а у нашей
   * платы RX на A8. Исправил: Дмитрий (GitHub: mamkincoderr), Telegram: https://t.me/oDeXteRo */
  while ((bool)(UART_PORT->MASKHB[1 << (UART_PIN_RX_POS - 8)].MASKHB) !=
         (bool)value) {
#endif
    //        if((uint32_t)(TIMEOUT_TMR->COUNT - timeout_start) >
    //        (uint32_t)(SYSCLK / 1000 * UART_TIMEOUT_MS)) {
    //            return -1;
    //        }
  }
  return 0;
}
volatile uint32_t ticks_counted;
int boot_init() {

  // TODO REMOVE THIS

  uint32_t ticks_counted;
  uint32_t baud_i;
  uint32_t baud_f;

  // Waiting for the start bit - 0
  UART_TMR->CTRL_bit.CLR = 1;
  UART_TMR->COUNT = 0;
  wait_uart_rx(0);

  //    if(wait_uart_rx(0) < 0){
  //        return -1;
  //    }

  // turn on timer
  // We are waiting for the start of a group of seven 1 (0x7F)
  UART_TMR->CTRL_bit.MODE = 2;
  wait_uart_rx(1);

  //    if(wait_uart_rx(1) < 0){
  //        return -1;
  //    }

  ticks_counted = UART_TMR->COUNT;
  // Waiting for bit - 0
  wait_uart_rx(0);

  //    if(wait_uart_rx(0) < 0){
  //        return -1;
  //    }

  ticks_counted = UART_TMR->COUNT - ticks_counted;
  UART_TMR->CTRL_bit.MODE = 0;
  // calculate baudrate
  baud_i = ticks_counted / (16 * 7);
  baud_f = (uint32_t)((ticks_counted / (16 * 7.0f) - baud_i) * 64 + 0.5f);

  // Waiting for stop bit - 1
  wait_uart_rx(1);

  //    if(wait_uart_rx(1) < 0){
  //        return -1;
  //    }

  // turn on UART
  UART->IBRD = baud_i;
  UART->FBRD = baud_f;
  UART->LCRH = (1 << UART_LCRH_FEN_Pos) | (3 << UART_LCRH_WLEN_Pos);
  UART->CR = (1 << UART_CR_RXE_Pos) | (1 << UART_CR_TXE_Pos) |
             (1 << UART_CR_UARTEN_Pos);
  // transmit the device signature with bytes swapped
  UART->DR = (PACKET_DEVICE_SIGN & 0xFF00) >> 8;
  UART->DR = PACKET_DEVICE_SIGN & 0x00FF;

  return 0;
}

void boot_exit(uint32_t jumpaddr) {
  /* Restore PLIC to known state: */
  // disable all interrupts
  csr_clr_bits_mstatus(MSTATUS_MIE_BIT_MASK);
  csr_clr_bits_mstatus(MSTATUS_MPIE_BIT_MASK);
  // PLIC_init(); //TODO
  /* Disable all interrupts: */
  csr_write_mie(0);

  // Disable periph
  TIMER_CLK = 0;
  TIMER_RST = 0;
  UART_CLK_PORT = 0;
  UART_RST_PORT = 0;

  RCU->UARTCFG[0].UARTCFG = 0;
  RCU->UARTCFG[1].UARTCFG = 0;

  RCU->SYSCLKCFG_bit.SRC = RCU_SYSCLKCFG_SRC_HSECLK;
  while (RCU->CLKSTAT_bit.SRC != RCU_CLKSTAT_SRC_HSECLK) {
    __asm__ volatile("nop");
  }

#if __TARGET_IDX__ == 1
  RCU->PLL[0].DIV = 0;
  RCU->PLL[0].MOD = 0;
  RCU->PLL[0].FRAC = 0;
  RCU->PLL[0].CFG = 0;
#else
  RCU->PLLDIV = 0;
  RCU->PLLMOD = 0;
  RCU->PLLFRAC = 0;
  RCU->PLLCFG = 0;
#endif

  /* Start executing from  after end of bootloader section: */
  __asm__ volatile("jr %0" : : "value"(jumpaddr));

  /*User application execution should now start and never return here.... */
}

__attribute__((noreturn)) void boot_core() {
  Packet_TypeDef packet;
  packet_fifo_init();
  // send a message about readiness to accept commands
  packet.cmd_code = CMD_NONE;
  packet.tmp_data8[0] = MSG_READY;
  msg_cmd(&packet);
  while (1) {
    packet_receive(&packet);
    switch (packet.cmd_code) {
    // Get commands
    case CMD_GET_INFO:
      get_info_cmd(&packet);
      break;
    case CMD_GET_CFGWORD:
      get_cfgword_cmd(&packet);
      break;
    // Set commands
    case CMD_SET_CFGWORD:
      set_cfgword_cmd(&packet);
      break;
    // Jump commands
    case CMD_JUMP:
      jump_cmd(&packet);
      break;
    // Write commands
    case CMD_WRITE_PAGE:
      write_page_cmd(&packet);
      break;
    // Read commands
    case CMD_READ_PAGE:
      read_page_cmd(&packet);
      break;
    // Erase commands
    case CMD_ERASE_FULL:
      erase_cmd(&packet);
      break;
    case CMD_ERASE_PAGE:
      erase_cmd(&packet);
      break;
    // Exit
    case CMD_EXIT:
      exit_cmd(&packet);
      break;
    case CMD_NONE:
      msg_cmd(&packet);
      break;
    default:
      break;
    }
  }
}

void msg_cmd(Packet_TypeDef *packet) {
  if (packet->cmd_code == CMD_NONE)
    packet->data_n = 4;
  packet->tmp_data8[1] = packet->cmd_code;
  packet->tmp_data8[2] = PACKET_EMPTY_DATA;
  packet->tmp_data8[3] = PACKET_EMPTY_DATA;
  packet->cmd_code = CMD_MSG;

  packet_transmit(packet);
}

void get_info_cmd(Packet_TypeDef *packet) {
  uint16_t rx_crc;

  rx_crc = packet_fifo_read_u16();

  if (packet->crc != rx_crc) {
    packet->tmp_data8[0] = MSG_ERR_CRC;
    packet->data_n = 4;
  } else {
    packet->tmp_data8[0] = MSG_OK;
    packet->tmp_data32[1] =
        SIU->CHIPID & 0xFFFFFFF0; //  		PMUSYS_CHIPID;
    packet->tmp_data32[2] = 0x0;
    packet->tmp_data32[3] = BOOT_VER;
    size_t boot_name_len = sizeof(BOOT_NAME);
    memcpy(&(packet->tmp_data32[4]), BOOT_NAME, boot_name_len);
    packet->data_n = 16 + boot_name_len;
  }

  msg_cmd(packet);
}

__attribute__((noinline, optimize("O0"))) void
get_cfgword_cmd(Packet_TypeDef *packet) {
  uint16_t rx_crc;
  uint32_t data[FLASH_CELL_WORD_WIDTH];

  rx_crc = packet_fifo_read_u16();

  if (packet->crc != rx_crc) {
    packet->tmp_data8[0] = MSG_ERR_CRC;
    packet->data_n = 4;
  } else {
    packet->tmp_data8[0] = MSG_OK;
    flash_read(FLASH_NVR_CFGWORD_PAGE_ADDR + FLASH_PAGE_SIZE_BYTES -
                   4 * FLASH_CELL_WORD_WIDTH,
               FLASH_NVR, data);
    packet->tmp_data32[1] = data[0];
    packet->data_n = 8;
  }

  msg_cmd(packet);
}

void set_cfgword_cmd(Packet_TypeDef *packet) {
  uint32_t cfgword;
  uint16_t rx_crc;
  uint16_t calc_crc;
  uint32_t page_arr[FLASH_CELL_WORD_WIDTH];
  /* Убрана неиспользуемая переменная modify_en (предупреждение компилятора, автор правки:
   * Дмитрий, GitHub mamkincoderr, Telegram t.me/oDeXteRo) */

  cfgword = packet_fifo_read_u32();
  calc_crc = crc_upd_u32(packet->crc, cfgword);

  rx_crc = packet_fifo_read_u16();

  uint32_t w_cfgword = cfgword;
  for (int i = 0; i < FLASH_CELL_WORD_WIDTH; i++) {
    w_cfgword = w_cfgword & (0b101);
    w_cfgword = w_cfgword | ~(0b101);
    page_arr[i] = w_cfgword;
  }

  packet->data_n = 8;
  if (calc_crc != rx_crc)
    packet->tmp_data8[0] = MSG_ERR_CRC;
  else {
    flash_erase_page(FLASH_NVR_CFGWORD_PAGE_ADDR, FLASH_NVR);
    flash_write(FLASH_NVR_CFGWORD_PAGE_ADDR + FLASH_PAGE_SIZE_BYTES -
                    4 * FLASH_CELL_WORD_WIDTH,
                FLASH_NVR, page_arr);
  }

  packet->tmp_data32[1] = cfgword;

  msg_cmd(packet);
}
uint16_t s_calc_crc[10] = {0};
uint16_t s_read_crc[10] = {0};
uint16_t s_ctr = 0;
__attribute__((noinline, optimize("O0"))) void
write_page_cmd(Packet_TypeDef *packet) {
  uint32_t rx_data;
  uint8_t cfg;
  uint32_t addr;
  uint32_t addr_i;
  uint32_t flash_type;
  uint32_t erase_option;
  uint32_t data[FLASH_CELL_WORD_WIDTH];
  uint16_t rx_crc;
  uint16_t calc_crc;
  uint32_t modify_en;

  // read the address, determine the required flash type and page number, then
  // erase it if necessary
  rx_data = packet_fifo_read_u32();

  cfg = (uint8_t)(rx_data >> 24);

  // determine the type of flash and whether it can be written
  flash_type = (FlashType_TypeDef)((cfg & CMD_WRITE_PAGE_OPT_NVR_MSK) >>
                                   CMD_WRITE_PAGE_OPT_NVR_POS);
  flash_read(FLASH_NVR_CFGWORD_PAGE_ADDR + FLASH_PAGE_SIZE_BYTES - 4 * 4,
             FLASH_NVR, data);
  if (flash_type == FLASH_MAIN)
    modify_en = (data[0] & CFGWORD_FLASHWE_MSK) >> CFGWORD_FLASHWE_POS;
  else
    modify_en = 1;

  // should erase before writing
  erase_option =
      (cfg & CMD_WRITE_PAGE_OPT_ERASE_MSK) >> CMD_WRITE_PAGE_OPT_ERASE_POS;

  addr = rx_data & ~(FLASH_PAGE_SIZE_BYTES - 1) & 0x00FFFFFF;

  // bootloader modification protection
  modify_en &= !((addr < (BOOT_FLASH_SIZE_TOTAL_BYTES)));

  if (erase_option && modify_en)
    flash_erase_page(addr, flash_type);
  calc_crc = crc_upd_u32(packet->crc, rx_data);

  // read 8 bytes of data and write the whole page
  addr_i = addr;

  for (uint32_t i = 0; i < FLASH_PAGE_SIZE_CELLS; i++) {
    for (int j = 0; j < FLASH_CELL_WORD_WIDTH; j++) {
      data[j] = packet_fifo_read_u32();
      calc_crc = crc_upd_u32(calc_crc, data[j]);
    }
    if (modify_en)
      flash_write(addr_i, flash_type, data);
    addr_i += (FLASH_CELL_WORD_WIDTH * 4);
  }

  rx_crc = packet_fifo_read_u16();

  packet->data_n = 8;
  if (calc_crc != rx_crc) {
    s_calc_crc[s_ctr] = calc_crc;
    s_read_crc[s_ctr] = rx_crc;
    s_ctr++;
    packet->tmp_data8[0] = MSG_ERR_CRC;
  } else if (!modify_en) {
    packet->tmp_data8[0] = MSG_FAIL;
  } else {
    packet->tmp_data8[0] = MSG_OK;
  }

  packet->tmp_data32[1] = rx_data;

  msg_cmd(packet);
}

void jump_cmd(Packet_TypeDef *packet) {
  uint32_t jumpaddr;
  uint32_t rx_data;
  uint16_t calc_crc;
  uint16_t rx_crc;

  jumpaddr = rx_data = packet_fifo_read_u32();
  calc_crc = crc_upd_u32(packet->crc, rx_data);

  rx_crc = packet_fifo_read_u16();
  if (calc_crc != rx_crc) {
    packet->tmp_data8[0] = MSG_ERR_CRC;
  }

  packet->tmp_data32[1] = rx_data;

  msg_cmd(packet);

  packet_fifo_read_u32();

  boot_exit(jumpaddr);
}

void read_page_cmd(Packet_TypeDef *packet) {
  uint32_t rx_data;
  uint8_t cfg;
  uint32_t addr;
  uint32_t addr_i;
  uint32_t flash_type;
  uint32_t data[FLASH_CELL_WORD_WIDTH];
  uint16_t rx_crc;
  uint16_t calc_crc;
  uint32_t read_en;

  flash_read(FLASH_NVR_CFGWORD_PAGE_ADDR + FLASH_PAGE_SIZE_BYTES - 4 * 4,
             FLASH_NVR, data);

  // read the address, determine the required flash type and page number, then
  // erase it if necessary
  rx_data = packet_fifo_read_u32();

  cfg = (uint8_t)(rx_data >> 24);
  flash_type = (FlashType_TypeDef)((cfg & CMD_READ_PAGE_OPT_NVR_MSK) >>
                                   CMD_READ_PAGE_OPT_NVR_POS);
  // can HOST read flash

  addr = rx_data & ~(FLASH_PAGE_SIZE_BYTES - 1) & 0x00FFFFFF;
  // bootloader read protection
  // read_en &= !((addr < (BOOT_FLASH_SIZE_TOTAL_BYTES)));
  read_en = 1; // No protection

  calc_crc = crc_upd_u32(packet->crc, rx_data);
  rx_crc = packet_fifo_read_u16();

  packet->data_n = 8;
  if (calc_crc != rx_crc)
    packet->tmp_data8[0] = MSG_ERR_CRC;
  else if (!read_en)
    packet->tmp_data8[0] = MSG_FAIL;
  else {
    addr_i = addr;
    for (uint32_t i = 0; i < FLASH_PAGE_SIZE_CELLS; i++) {
      flash_read(addr_i, flash_type, data);
      for (int j = 0; j < FLASH_CELL_WORD_WIDTH; j++) {
        packet->tmp_data32[2 + i * FLASH_CELL_WORD_WIDTH + j] = data[j];
      }
      addr_i += FLASH_CELL_WORD_WIDTH * 4;
    }
    packet->tmp_data8[0] = MSG_OK;
    packet->data_n += FLASH_PAGE_SIZE_BYTES;
  }

  packet->tmp_data32[1] = rx_data;

  msg_cmd(packet);
}

void erase_cmd(Packet_TypeDef *packet) {
  uint32_t rx_data;
  uint8_t cfg;
  uint32_t addr;
  uint32_t flash_type;
  uint16_t rx_crc;
  uint16_t calc_crc;
  uint32_t data[2];
  uint32_t modify_en;

  rx_data = packet_fifo_read_u32();
  cfg = (uint8_t)(rx_data >> 24);

  // determine the type of flash and whether the host can erase it
  flash_type = (FlashType_TypeDef)((cfg & CMD_WRITE_PAGE_OPT_NVR_MSK) >>
                                   CMD_WRITE_PAGE_OPT_NVR_POS);
  flash_read(FLASH_NVR_CFGWORD_PAGE_ADDR + FLASH_PAGE_SIZE_BYTES - 4 * 4,
             FLASH_NVR, data);
  if (flash_type == FLASH_MAIN)
    modify_en = (data[0] & CFGWORD_FLASHWE_MSK) >> CFGWORD_FLASHWE_POS;
  else
    modify_en = 1;

  addr = rx_data & ~(FLASH_PAGE_SIZE_BYTES - 1) & 0x00FFFFFF;

  // bootloader modification protection
  modify_en &= !((addr < (BOOT_FLASH_SIZE_TOTAL_BYTES)));

  calc_crc = crc_upd_u32(packet->crc, rx_data);
  rx_crc = packet_fifo_read_u16();

  packet->data_n = 8;
  if (calc_crc != rx_crc)
    packet->tmp_data8[0] = MSG_ERR_CRC;
  else if (!modify_en)
    packet->tmp_data8[0] = MSG_FAIL;
  else {
    if (packet->cmd_code == CMD_ERASE_FULL) {
      save_and_erase_all_ramfunc();
    } else {
      flash_erase_page(addr, flash_type);
    }

    packet->tmp_data8[0] = MSG_OK;
  }

  packet->tmp_data32[1] = rx_data;

  msg_cmd(packet);
}

void exit_cmd(Packet_TypeDef *packet) {
  uint16_t rx_crc;
  uint16_t calc_crc;

  calc_crc = packet->crc;
  rx_crc = packet_fifo_read_u16();

  packet->data_n = 4;
  if (calc_crc != rx_crc)
    packet->tmp_data8[0] = MSG_ERR_CRC;
  else
    packet->tmp_data8[0] = MSG_OK;

  msg_cmd(packet);
  while (packet_transmit_status_busy()) {
  };

  boot_exit(USER_JUMP_ADDRESS);
}

void flash_erase_full_ramfunc(void) {
  __asm__ volatile("nop");
  __asm__ volatile("nop");
  while (FLASH->STAT_bit.BUSY) {
  };
  FLASH->ADDR = 0;
  FLASH->CMD = FLASH_MAGICKEY_CONST << FLASH_CMD_KEY_Pos | FLASH_ALLSEC |
               FLASH_MAIN << FLASH_CMD_NVRON_Pos;
  while (FLASH->STAT_bit.BUSY) {
  };
}

void flash_write_128_ramfunc(uint32_t addr, uint32_t *data) {
  FLASH->ADDR = addr;

  for (int cell = 0; cell < FLASH_CELL_WORD_WIDTH; cell++) {
    FLASH->DATA[cell].DATA = (uint32_t)data[cell];
  }
  FLASH->CMD = (0xC0DE << 16) | FLASH_CMD_WR_Msk;
  while (FLASH->STAT & 0x01)
    ;
}

void memcpy_flash_ramfunc(uint32_t to_flash, uint32_t *from, uint32_t size) {
  for (uint32_t i = 0; i < size; i += 4) {
    flash_write_128_ramfunc(to_flash + i * 4, from + i);
  }
}

void memcpy_ramfunc(uint8_t *to, uint8_t *from, uint32_t size) {
  for (uint32_t i = 0; i < size; i++) {
    to[i] = from[i];
  }
}

void save_and_erase_all_ramfunc(void) {
  memcpy_ramfunc((uint8_t *)bootflash_program, (uint8_t *)0x00000000,
                 BOOT_FLASH_SIZE_TOTAL_BYTES);
  flash_erase_full_ramfunc();
  memcpy_flash_ramfunc(0x00000000, (uint32_t *)bootflash_program,
                       BOOT_FLASH_SIZE_TOTAL_BYTES / 4);
}
