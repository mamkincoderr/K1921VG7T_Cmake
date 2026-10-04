/* Инициализация платформы: вызывается из startup_k1921vg7t.S до main().
 * Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
 * Telegram: https://t.me/oDeXteRo
 *
 * Заменяет sys_init.c из SDK НИИЭТ, который подключает отсутствующий plf_l1cache.h и ждёт
 * символы, определённые не во всех скриптах компоновщика. Здесь используются символы из
 * ld/k1921vg7t.ld.in.
 *
 * Кэши и MPU остаются в состоянии после сброса (UART-загрузчик НИИЭТ делает так же).
 */

#include <stdint.h>

extern char __bss_start[], __bss_end[];
extern char __data_lma[], __data_start[], __data_end[];
extern char __ramfunc_lma[], _ramfunc_start[], _ramfunc_end[];
extern char __tcmcode_lma[], _tcmcode_start[], _tcmcode_end[];
extern char __tcmdata_lma[], _tcmdata_start[], _tcmdata_end[];

static void copy_words(char *dst, const char *src, char *dst_end)
{
    uint32_t *d = (uint32_t *)dst;
    const uint32_t *s = (const uint32_t *)src;
    uint32_t *e = (uint32_t *)dst_end;
    while (d < e) {
        *d++ = *s++;
    }
}

void plf_init(void)
{
    /* Обнуление .bss */
    uint32_t *b = (uint32_t *)__bss_start;
    uint32_t *be = (uint32_t *)__bss_end;
    while (b < be) {
        *b++ = 0;
    }

    /* Копирование образов из Flash: данные, код в RAM, код и данные в TCM */
    copy_words(__data_start, __data_lma, __data_end);
    copy_words(_ramfunc_start, __ramfunc_lma, _ramfunc_end);
    copy_words(_tcmcode_start, __tcmcode_lma, _tcmcode_end);
    copy_words(_tcmdata_start, __tcmdata_lma, _tcmdata_end);
}
