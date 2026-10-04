/*
 *
 * SCR5 PLIC driver for "1252MOTOR" header file
 *
 * created by DVS, TEMA
 *
*/

#ifndef _PLIC_H
#define _PLIC_H

#include <stdint.h>

enum Plic_Target {
    Plic_Mach_Target = 0x0,
    Plic_SuperVisor_Target
};

typedef enum {
    PLIC_IRQMODE_OFF = 0x0,
    PLIC_IRQMODE_HILEVEL,
    PLIC_IRQMODE_LOLEVEL,
    PLIC_IRQMODE_RISEDGE,
    PLIC_IRQMODE_FALEDGE,
    PLIC_IRQMODE_TWOEDGE
} Plic_IrqMode_TypeDef;

typedef void irqfunc (void);
void cache_enable(uint8_t flash, uint8_t ram);
void PLIC_SetIrqHandler (uint8_t target, uint32_t isr_num, irqfunc* func);
void PLIC_SetPriority (uint32_t isr_num, uint8_t pri);
void PLIC_SetThreshold(uint8_t target, uint32_t value);
void PLIC_SetMode (uint32_t isr_num, Plic_IrqMode_TypeDef mode);
void PLIC_IntEnable (uint8_t target, uint32_t isr_num);
void PLIC_IntDisable (uint8_t target, uint32_t isr_num);
void PLIC_MachHandler(void);

void trap_handler (void);

#endif
