/*
 *
 * SCR4 PLIC driver for "S1252MOTOR"
 *
 * created by DVS
 * rewrite by M.A.Terekhov
 *
 * 2023
 *
*/

#include "arch.h"
#include "csr.h"
#include "plic.h"


// pointers to handler functions for machine mode
irqfunc* mach_plic_handler[128] __attribute__((section(".data")));
// pointers to handler functions for supervisor mode
irqfunc* supervisor_plic_handler[128] __attribute__((section(".data")));

/*
 * Registers of PLIC module
 */
 
// mpu and cache
#define SCR_CSR_MPU_SEL  (SCR_CSR_MPU_BASE + 0)
#define SCR_CSR_MPU_CTRL (SCR_CSR_MPU_BASE + 1)
#define SCR_CSR_MPU_ADDR (SCR_CSR_MPU_BASE + 2)
#define SCR_CSR_MPU_MASK (SCR_CSR_MPU_BASE + 3)
#define SCR_CSR_CACHE_GLBL 0xbd4

#define SCR_MPU_MK_ADDR(addr)  ((((addr) / 4) | ((addr) & 0x80000000) | ((addr) & 0x80000000) / 2) & 0xffffffff)
#define SCR_MPU_MK_MASK(size) ((~((size) - 1) / 4) & 0xffffffff)

//#define SCR_MPU_MK_ADDR(addr)  ((addr)>>2)
//#define SCR_MPU_MK_MASK(size) ((~(size-1))>>2)

void cache_enable(uint8_t flash, uint8_t ram)
{
	write_csr(SCR_CSR_CACHE_GLBL, 0xF);

	write_csr(SCR_CSR_MPU_SEL, 0);
	write_csr(SCR_CSR_MPU_ADDR, SCR_MPU_MK_ADDR(0x0));
	write_csr(SCR_CSR_MPU_MASK, SCR_MPU_MK_MASK(1024*1024));
	write_csr(SCR_CSR_MPU_CTRL, 0x7F | (flash & 0x1)<<16);

	write_csr(SCR_CSR_MPU_SEL, 1);
	write_csr(SCR_CSR_MPU_ADDR, SCR_MPU_MK_ADDR(0x20000000));
	write_csr(SCR_CSR_MPU_MASK, SCR_MPU_MK_MASK(256*1024));
	write_csr(SCR_CSR_MPU_CTRL, 0x7F | (ram & 0x1)<<16);

	write_csr(SCR_CSR_MPU_SEL, 2); // AHB
	write_csr(SCR_CSR_MPU_ADDR, SCR_MPU_MK_ADDR(0x40000000));
	write_csr(SCR_CSR_MPU_MASK, SCR_MPU_MK_MASK(32*1024*1024));
	write_csr(SCR_CSR_MPU_CTRL, 0x1007F);

	write_csr(SCR_CSR_MPU_SEL, 3); // ABP
	write_csr(SCR_CSR_MPU_ADDR, SCR_MPU_MK_ADDR(0x50000000));
	write_csr(SCR_CSR_MPU_MASK, SCR_MPU_MK_MASK(32*1024*1024));
	write_csr(SCR_CSR_MPU_CTRL, 0x1007F);

	ifence();
}

typedef struct {
    uint32_t INTEN_BANK[32]; // offset 0x0 - 0x7c
} PLIC_INTEN_Bank_TypeDef;

typedef struct {
    uint32_t PRI_TRSHLD;
    uint32_t START_END;
    uint32_t Reserved0 [1022];
} PLIC_PRI_SE_TypeDef;

typedef struct {
    uint32_t SRC_PRI[1024]; // 0 - 0xffc
    uint32_t INT_PEND[32];  // 0x1000 - 0x107c
    uint32_t Reserved0 [992]; // 0x1080 - 0x1fff
    PLIC_INTEN_Bank_TypeDef INTEN_TARGET[64]; // 0x2000 - 0x3ffc
    uint32_t Reserved1 [503808]; // 0x4000 - 0x1efffc
    uint32_t SRC_MODE  [1024]; // 0x1f0000 - 0x1f0ffc
    uint32_t Reserved2 [15360]; // 0x1f1000 - 1ffffc
    PLIC_PRI_SE_TypeDef PRI_SE[64]; // 0x200000 -0x23fffc
    uint32_t Reserved3 [3605501]; // 0x240000 - 0xffffff
} PLIC_TypeDef;

#define PLIC_BASE            (0xFE000000UL)
#define PLIC                 ((PLIC_TypeDef                *) PLIC_BASE)

// private functions
uint32_t PLIC_ClaimIrq      (uint8_t target);
void     PLIC_ClaimComplete (uint8_t target, uint32_t isrnum);

// defines
#define NULL_IRQ 0

/*
 * Set PLIC handler function for isr num
 */

void PLIC_SetIrqHandler (uint8_t target, uint32_t isr_num, irqfunc* func)
{
    if(target == Plic_Mach_Target) {
        mach_plic_handler[isr_num] = func;
    } else {
        supervisor_plic_handler[isr_num] = func;
    }
}
/*
 * Set PLIC irq priority
 */

void PLIC_SetPriority (uint32_t isr_num, uint8_t pri)
{
    PLIC->SRC_PRI[isr_num] = pri;
}

/*
 * Set PLIC irq mode
 */

void PLIC_SetMode (uint32_t isr_num, Plic_IrqMode_TypeDef mode)
{
    PLIC->SRC_MODE[isr_num] = (uint32_t)(mode);
}

/*
 * Enable PLIC irq
 */

void PLIC_IntEnable (uint8_t target, uint32_t isr_num)
{
    uint32_t bankNum = isr_num / 32;
    uint32_t bankPos = isr_num - bankNum * 32;
    uint32_t bankVal = PLIC->INTEN_TARGET[target].INTEN_BANK[bankNum];

    //read - modify - write operation

    bankVal |= (1 << bankPos);

    PLIC->INTEN_TARGET[target].INTEN_BANK[bankNum] = bankVal;
}

/*
 * Disable PLIC irq
 */

void PLIC_IntDisable (uint8_t target, uint32_t isr_num)
{
    uint32_t bankNum = isr_num / 32;
    uint32_t bankPos = isr_num - bankNum * 32;
    uint32_t bankVal = PLIC->INTEN_TARGET[target].INTEN_BANK[bankNum];

    //read - modify - write operation

    bankVal &= ~(1 << bankPos);

    PLIC->INTEN_TARGET[target].INTEN_BANK[bankNum] = bankVal;
}

/*
 * Get current isr number
 */

uint32_t PLIC_ClaimIrq (uint8_t target)
{
    return (uint32_t)(PLIC->PRI_SE[target].START_END);
}

/*
 * Set current isr as completed
 */

void PLIC_ClaimComplete (uint8_t target, uint32_t isrnum)
{
    PLIC->PRI_SE[target].START_END = isrnum;
}

/*
 * Set threshold for irqs
 */

void PLIC_SetThreshold(uint8_t target, uint32_t value) {
    PLIC->PRI_SE[target].PRI_TRSHLD = value;
}

/*
 * PLIC Interrupt main handler
*/

void PLIC_MachHandler (void) {
    // handle interrupt
    uint32_t isr_num = PLIC_ClaimIrq(Plic_Mach_Target);
    // check if handler exist
    if(mach_plic_handler[isr_num] != NULL_IRQ) {
        // call isr handler
        mach_plic_handler[isr_num]();
        // set isr completes
        PLIC_ClaimComplete(Plic_Mach_Target, isr_num);
    }
}

/*
 * PLIC trap handler redefine
*/

/* Слабая заглушка. Настоящий обработчик шага 1 мс лежит в user/systick.c. */
__attribute__((weak)) void systick_handler(void) {}

void trap_handler (void) {
    uint32_t mcause_val = read_csr(mcause);

    if ((mcause_val & TRAP_CAUSE_INTERRUPT_FLAG) == 0) {
        // handle exception
        switch (mcause_val & TRAP_CAUSE_EXCEPT_MASK) {
            case TRAP_CAUSE_EXC_FETCH_ALIGN: break;
            case TRAP_CAUSE_EXC_FETCH_ACCESS: break;
            case TRAP_CAUSE_EXC_ILLEGAL: break;
            case TRAP_CAUSE_EXC_BREAKPOINT: break;
            case TRAP_CAUSE_EXC_LOAD_ALIGN: break;
            case TRAP_CAUSE_EXC_LOAD_ACCESS: break;
            case TRAP_CAUSE_EXC_STORE_ALIGN: break;
            case TRAP_CAUSE_EXC_STORE_ACCESS: break;
            case TRAP_CAUSE_EXC_UECALL: break;
            case TRAP_CAUSE_EXC_SECALL: break;
            case TRAP_CAUSE_EXC_RESERVED1: break;
            case TRAP_CAUSE_EXC_MECALL: break;
            case TRAP_CAUSE_EXC_FETCH_PAGE: break;
            case TRAP_CAUSE_EXC_LOAD_PAGE: break;
            case TRAP_CAUSE_EXC_RESERVED2: break;
            case TRAP_CAUSE_EXC_STORE_PAGE: break;
        }
        while(1) {}; //TRAP
    } else if ((mcause_val & TRAP_CAUSE_EXCEPT_MASK) == TRAP_CAUSE_INT_MTIME) {
        /* Машинный таймер не проходит через PLIC. */
        systick_handler();
    } else {
        // handle interrupt
        PLIC_MachHandler();
    }
}
