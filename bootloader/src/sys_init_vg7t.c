/// @file
/// @brief platform init funcs

#include <sys/errno.h>
#include <string.h>
#include <unistd.h>

#include "memasm.h"

extern char _tdata_start[], _tdata_end[], _tbss_start[], _tbss_end[];

extern void plf_init_relocate(void) __attribute__((weak));

extern char __bss_start[], __bss_end[];
extern char _ramfunc_start[], _ramfunc_end[];
extern char _tcmcode_start[], _tcmcode_end[];
extern char _tcmconst_start[], _tcmconst_end[];
extern char __etext[];
extern char __tcmcode_pos[];
extern char __tcmconst_pos[];
extern char __tcmvar_pos[];

extern const uint8_t __ramfunc_source_start;
extern uint8_t __ramfunc_target_start;
extern uint8_t __ramfunc_target_end;

void __init plf_init_noreloc(void)
{
    // do nothing
}

void CopyToRAM(void* dest, void* src, uint32_t cnt)
{
    uint32_t *sp;
    uint32_t *dp;
    uint32_t i;
    uint32_t size=cnt>>2;
    sp=(uint32_t *)src;
    dp=(uint32_t *)dest;

    for (i=0; i<size; i++)
    {
        *dp=*sp;
        dp++;
        sp++;
    }
}
void __init plf_init_generic(void)
{
    // do relocations
    //plf_init_relocate();
    // init TLS
    //register void *tp asm ("tp");
    //plf_init_tls(tp);
    // init BSS
    memset(__bss_start, 0, (size_t)(__bss_end - __bss_start));

    /*(*(volatile uint32_t *)(0x20004000)) = (uint32_t)_ramfunc_start;
    (*(volatile uint32_t *)(0x20004004)) = (uint32_t)_ramfunc_end;
    (*(volatile uint32_t *)(0x20004008)) = (uint32_t)__etext;
    (*(volatile uint32_t *)(0x20004010)) = (uint32_t)_tcmcode_start;
    (*(volatile uint32_t *)(0x20004014)) = (uint32_t)_tcmcode_end;
    (*(volatile uint32_t *)(0x20004018)) = (uint32_t)__tcmcode_pos;
    (*(volatile uint32_t *)(0x20004020)) = (uint32_t)_tcmconst_start;
    (*(volatile uint32_t *)(0x20004024)) = (uint32_t)_tcmconst_end;
    (*(volatile uint32_t *)(0x20004028)) = (uint32_t)__tcmconst_pos;
    (*(volatile uint32_t *)(0x20004030)) = (uint32_t)__tcmvar_pos;*/

    //memcpy(_ramfunc_start, __etext, (size_t)(_ramfunc_end - _ramfunc_start));
    /* Размер задан беззнаковым числом, иначе сравнение uint32_t со знаковой разностью указателей
     * даёт предупреждение -Wsign-compare (правка: Дмитрий, GitHub mamkincoderr) */
    const uint32_t ramfunc_size = (uint32_t)(&__ramfunc_target_end - &__ramfunc_target_start);
    for(uint32_t i = 0; i < ramfunc_size; i++) {
        ((uint8_t*)&__ramfunc_target_start)[i] = ((uint8_t*)&__ramfunc_source_start)[i];
    }
    CopyToRAM(_tcmcode_start, __tcmcode_pos, (size_t)(_tcmcode_end - _tcmcode_start));
    CopyToRAM(_tcmconst_start, __tcmconst_pos, (size_t)(_tcmconst_end - _tcmconst_start));


    // enable/init caches
    //plf_l2cache_init();
    //plf_l1cache_init();
    // enable/init MPU
    //mpu_init();
    // init peripheries
    //con_init();
    //rtc_init();
    //leds_init();
    // init smp
    //plf_smp_init();
}

void plf_init(void) __attribute__((weak, alias("plf_init_generic")));

