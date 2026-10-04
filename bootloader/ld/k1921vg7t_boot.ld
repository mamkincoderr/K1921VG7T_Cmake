/* Скрипт компоновщика UART-загрузчика: k1921vg7t_flash.ld от НИИЭТ с одним изменением.
 *   ROM = 8K (0x0000-0x1FFF) вместо 38K: разросшийся загрузчик не поместится и сборка упадёт,
 *   а не затрёт приложение, которое начинается с 0x2000.
 * Автор доработки: Дмитрий (GitHub: mamkincoderr), Telegram: https://t.me/oDeXteRo
 */
OUTPUT_ARCH( "riscv" )
ENTRY(_start)

MEMORY {
  ROM  (rwx) : ORIGIN = 0x00000000, LENGTH = 8k
  RAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
  TCM  (rwx) : ORIGIN = 0xF0000000, LENGTH = 32K
}

REGION_ALIAS("REGION_TEXT",   ROM );
REGION_ALIAS("REGION_RODATA", ROM );
REGION_ALIAS("REGION_DATA",   RAM);
REGION_ALIAS("REGION_BSS",    RAM);
REGION_ALIAS("REGION_STACK",  RAM);
REGION_ALIAS("REGION_TCM",    RAM );

STACK_SIZE = 2048;

INCLUDE "k1921vg7t_common.lds"
