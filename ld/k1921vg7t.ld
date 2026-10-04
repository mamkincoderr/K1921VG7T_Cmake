/* Скрипт компоновщика приложения К1921ВГ7Т.
 * Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
 * Telegram: https://t.me/oDeXteRo
 *
 * Карта памяти:
 *   Flash 0x00000000-0x00001FFF  UART-загрузчик (8 КБ, свой скрипт bootloader/ld/)
 *   Flash 0x00002000-0x0007FFFF  приложение: код, константы, начальные значения данных
 *   RAM   0x20000000-0x20007FFF  32 КБ: .data/.bss сначала, стек сверху, куча между ними
 *   TCM   0xF0000000-0xF0007FFF  32 КБ, пока не используется
 *
 * Имена символов совпадают с SDK НИИЭТ, чтобы startup_k1921vg7t.S работал без правок:
 *   __global_pointer$, __TLS0_BASE__, __C_STACK_TOP__, __bss_start/__bss_end и т.д.
 */

OUTPUT_ARCH("riscv")
ENTRY(_start)

MEMORY
{
  /* Область UART-загрузчика. Ни одна секция приложения сюда не помещается, область описана
   * для наглядности: она видна в таблице памяти и в отчёте компоновщика (BOOT: 0 B). */
  BOOT (r)  : ORIGIN = 0x00000000, LENGTH = 8K
  ROM (rx)  : ORIGIN = 0x00002000, LENGTH = 504K
  RAM (rwx) : ORIGIN = 0x20000000,   LENGTH = 32K
  TCM (rwx) : ORIGIN = 0xF0000000,   LENGTH = 32K
}

/* Приложение обязано начинаться сразу за загрузчиком */
ASSERT(ORIGIN(ROM) == ORIGIN(BOOT) + LENGTH(BOOT), "ROM приложения должен начинаться за областью загрузчика")

STACK_SIZE = 2048;            /* размер основного стека, байт */

SECTIONS
{
  /* Точка входа после сброса. Загрузчик делает "jr 0x2000", поэтому
   * _start обязан стоять самым первым в ROM. */
  .text.startup ORIGIN(ROM) :
  {
    KEEP(*(.startup.entry))
    *(.startup.*)
    . = ALIGN(16);
    *(.init.rodata .init.rodata.*)
    . = ALIGN(16);
    *(.init.data .init.data.*)
    . = ALIGN(16);
    *(.init.text .init.text.*)
  } > ROM

  __TEXT_INIT_START__ = LOADADDR(.text.startup);
  __TEXT_INIT_SIZE__  = SIZEOF(.text.startup);

  .text.crt : ALIGN(16)
  {
    KEEP(*(.text.crt*))
  } > ROM

  .text : ALIGN(4)
  {
    PROVIDE(__TEXT_START__ = .);
    *(.text .text.*)
    *(.gnu.linkonce.t.*)
    PROVIDE(__TEXT_END__ = .);
  } > ROM

  .rodata : ALIGN(4)
  {
    *(.rodata .rodata.*)
    *(.gnu.linkonce.r.*)
  } > ROM

  .srodata : ALIGN(4)
  {
    *(.srodata.cst16) *(.srodata.cst8) *(.srodata.cst4) *(.srodata.cst2) *(.srodata .srodata.*)
  } > ROM

  .init_array : ALIGN(4)
  {
    PROVIDE_HIDDEN(__init_array_start = .);
    KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*) .init_array))
    PROVIDE_HIDDEN(__init_array_end = .);
  } > ROM

  .fini_array : ALIGN(4)
  {
    PROVIDE_HIDDEN(__fini_array_start = .);
    KEEP(*(SORT_BY_INIT_PRIORITY(.fini_array.*) .fini_array))
    PROVIDE_HIDDEN(__fini_array_end = .);
  } > ROM

  __etext = .;

  /* ---- инициализированные данные: живут в RAM, образ хранится в ROM ---- */
  .sdata : ALIGN(4)
  {
    __SDATA_BEGIN__ = .;
    *(.sdata .sdata.* .sdata2.* .gnu.linkonce.s.*)
  } > RAM AT > ROM

  .data : ALIGN(4)
  {
    __DATA_BEGIN__ = .;
    *(.data .data.* .gnu.linkonce.d.*)
    . = ALIGN(4);
    _edata = .;
    PROVIDE(edata = .);
  } > RAM AT > ROM

  /* Одно копирование покрывает .sdata и .data */
  __data_lma   = LOADADDR(.sdata);
  __data_start = ADDR(.sdata);
  __data_end   = ADDR(.data) + SIZEOF(.data);

  /* ---- код, исполняемый из RAM (работа с Flash и т.п.) ---- */
  .ramfunc : ALIGN(4)
  {
    PROVIDE(_ramfunc_start = .);
    *(.ramfunc .ramfunc.*)
    . = ALIGN(4);
    PROVIDE(_ramfunc_end = .);
  } > RAM AT > ROM

  __ramfunc_lma = LOADADDR(.ramfunc);

  /* ---- TCM ---- */
  .tcmcode : ALIGN(4)
  {
    PROVIDE(_tcmcode_start = .);
    *(.tcmcode .tcmcode.*)
    . = ALIGN(4);
    PROVIDE(_tcmcode_end = .);
  } > TCM AT > ROM

  .tcmdata : ALIGN(4)
  {
    PROVIDE(_tcmdata_start = .);
    *(.tcmdata .tcmdata.* .tcmconst .tcmconst.*)
    . = ALIGN(4);
    PROVIDE(_tcmdata_end = .);
  } > TCM AT > ROM

  __tcmcode_lma = LOADADDR(.tcmcode);
  __tcmdata_lma = LOADADDR(.tcmdata);

  .tcmbss (NOLOAD) : ALIGN(4)
  {
    PROVIDE(_tcmbss_start = .);
    *(.tcmbss .tcmbss.* .tcmvar .tcmvar.* .ramvars)
    . = ALIGN(4);
    PROVIDE(_tcmbss_end = .);
  } > TCM

  /* ---- данные, обнулённые при старте ---- */
  .sbss (NOLOAD) : ALIGN(4)
  {
    PROVIDE(__bss_start = .);
    *(.sbss .sbss.* .gnu.linkonce.sb.*)
    *(.scommon)
  } > RAM

  .bss (NOLOAD) : ALIGN(4)
  {
    *(.bss .bss.* .gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN(4);
    __BSS_END__ = .;
    PROVIDE(__bss_end = .);
    PROVIDE(_end = .);
    PROVIDE(end = .);
    PROVIDE(_ebss = .);
  } > RAM

  __global_pointer$ = MIN(__DATA_BEGIN__ + 0x780,
                          MAX(__SDATA_BEGIN__ + 0x780, __BSS_END__ - 0x780));

  /* ---- стек в верхней части RAM, куча занимает промежуток под ним ----
   * Стек задан символами, а не секцией. Раньше он был секцией на самом верху RAM, и компоновщик
   * показывал "RAM 100 %": занятым считается всё от начала области до последнего адреса секции.
   * Теперь в отчёте только реально занятая RAM (данные и bss), а переполнение ловит ASSERT. */
  __C_STACK_TOP__ = ORIGIN(RAM) + LENGTH(RAM);
  __STACK_END__   = __C_STACK_TOP__;
  __STACK_START__ = __C_STACK_TOP__ - STACK_SIZE;
  __TLS0_BASE__   = __C_STACK_TOP__;

  /* Локальной памяти потоков (TLS) на этом кристалле нет. */
  __TLS_SIZE__ = 0;

  _heap_start = ALIGN(__bss_end, 16);
  _heap_end   = __STACK_START__ & ~15;

  ASSERT(_heap_start <= _heap_end, "RAM переполнена: данные, bss и стек не помещаются в 32 КБ")

  /DISCARD/ :
  {
    *(.eh_frame .eh_frame.*)
    *(.init.text.plf_init_relocate)
  }
}
