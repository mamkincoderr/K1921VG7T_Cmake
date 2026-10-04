/* Системный таймер SCR4, шаг 1 мс.
 * Автор: Дмитрий (GitHub: mamkincoderr, https://github.com/mamkincoderr)
 * Telegram: https://t.me/oDeXteRo
 */
#include "systick.h"

#include "arch.h"
#include "csr.h"
#include "mtimer.h"
#include "system_k1921vg7t.h"

/* Делитель такта mtime. Ноль в регистре означает делитель 1. */
#define MTIME_DIV_ADDR 0xE0000004u

/* Регистры MPU Syntacore. Область системного таймера — регион 1. */
#define MPU_SEL  0xBC4u
#define MPU_CTRL 0xBC5u
#define MPU_ADDR 0xBC6u
#define MPU_MASK 0xBC7u

#define MPU_REGION_MTIMER 1u
#define MTIMER_BASE       0xE0000000u
#define MTIMER_MASK       0xFF000000u
/* Тип памяти config, чтение и запись из M-режима, регион включён. */
#define MPU_CTRL_MTIMER   ((3u << 16) | (1u << 1) | (1u << 2) | 1u)

static volatile uint32_t s_ms;
static uint32_t s_ticks_per_ms;
static uint64_t s_next_cmp;

/* Номер CSR в csrw обязан быть непосредственным операндом, поэтому это макрос. */
#define CSR_WRITE(csr, value) __asm__ volatile("csrw %0, %1" :: "i"(csr), "r"(value))

static void mpu_map_mtimer(void)
{
    CSR_WRITE(MPU_SEL, MPU_REGION_MTIMER);
    CSR_WRITE(MPU_CTRL, 0);
    CSR_WRITE(MPU_ADDR, MTIMER_BASE >> 2);
    CSR_WRITE(MPU_MASK, MTIMER_MASK >> 2);
    CSR_WRITE(MPU_CTRL, MPU_CTRL_MTIMER);
    __asm__ volatile("fence.i" ::: "memory");
}

static void mtimecmp_write(uint64_t value)
{
    volatile uint32_t *lo = (volatile uint32_t *)RISCV_MTIMECMP_ADDR;
    volatile uint32_t *hi = (volatile uint32_t *)(RISCV_MTIMECMP_ADDR + 4u);

    /* Старшая половина сначала уводится в максимум, иначе на середине
     * записи сравнение может сработать раньше времени. */
    *hi = 0xFFFFFFFFu;
    *lo = (uint32_t)value;
    *hi = (uint32_t)(value >> 32);
}

void systick_handler(void)
{
    s_ms++;
    s_next_cmp += s_ticks_per_ms;

    /* Если обработчик опоздал больше чем на шаг, следующий тик берётся
     * от текущего времени, а не от уже прошедшего сравнения. */
    uint64_t now = mtimer_get_raw_time();
    if ((int64_t)(s_next_cmp - now) < (int64_t)s_ticks_per_ms) {
        s_next_cmp = now + s_ticks_per_ms;
    }
    mtimecmp_write(s_next_cmp);
}

void systick_init(void)
{
    mpu_map_mtimer();

    uint32_t div = *(volatile uint32_t *)MTIME_DIV_ADDR;
    uint32_t tick_hz = SystemCoreClock / (div + 1u);
    s_ticks_per_ms = tick_hz / 1000u;
    if (s_ticks_per_ms == 0u) {
        s_ticks_per_ms = 1u;
    }

    s_ms = 0;
    s_next_cmp = mtimer_get_raw_time() + s_ticks_per_ms;
    mtimecmp_write(s_next_cmp);
}

void systick_irq_enable(void)
{
    set_csr(mie, MIE_MTIMER);
}

uint32_t systick_ms(void)
{
    return s_ms;
}

void delay_ms(uint32_t ms)
{
    uint32_t start = s_ms;
    while ((s_ms - start) < ms) {
    }
}
