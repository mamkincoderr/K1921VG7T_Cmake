/*==============================================================================
 * Основной файл загрузчика K1921VGXT
 *------------------------------------------------------------------------------
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

//-- Includes ------------------------------------------------------------------
#if __TARGET_IDX__ == 1
    #include <K1921VG1T.h>
    #include <system_k1921vg1t.h>
#elif __TARGET_IDX__ == 3
    #include <K1921VG3T.h>
    #include <system_k1921vg3t.h>
#elif __TARGET_IDX__ == 5
    #include <K1921VG5T.h>
    #include <system_k1921vg5t.h>
#elif __TARGET_IDX__ == 7
    #include <K1921VG7T.h>
    #include <system_k1921vg7t.h>
#else
    #error "please define correct __TARGET_IDX__ in makefile"
#endif


#include <stdbool.h>
#include "boot_conf.h"
#include "boot_core.h"
#include "boot_packet.h"
#include "boot_led.h"
#include "boot_flash.h"

static void UartInit(void){
	// TODO make active only UARTPORT

	RCU->CGCFGAHB    |= UART_PORT_EN;
	RCU->RSTDISAHB   |= UART_PORT_EN;

    #if __TARGET_IDX__ == 1
        #if UART_PIN_RX_POS < 8
            UART_PORT->ALTFUNCNUM0 |= (UART_ALTFUNCNUM << (UART_PIN_RX_POS * 4));
        #else 
            UART_PORT->ALTFUNCNUM1 |= (UART_ALTFUNCNUM << (UART_PIN_RX_POS * 4));
        #endif
        #if UART_PIN_TX_POS < 8
            UART_PORT->ALTFUNCNUM0 |= (UART_ALTFUNCNUM << (UART_PIN_TX_POS * 4));
        #else 
            UART_PORT->ALTFUNCNUM1 |= (UART_ALTFUNCNUM << (UART_PIN_TX_POS * 4));
        #endif
    #else
        UART_PORT->ALTFUNCNUM &= ~((0b11 << (UART_PIN_TX_POS * 2)) | (0b11 << (UART_PIN_RX_POS * 2)));
        UART_PORT->ALTFUNCNUM |= (UART_ALTFUNCNUM << (UART_PIN_TX_POS * 2)) | (UART_ALTFUNCNUM << (UART_PIN_RX_POS * 2));
    #endif
    
    UART_PORT->ALTFUNCSET |= (1 << UART_PIN_TX_POS) | (1 << UART_PIN_RX_POS);


	UART_CLK_PORT   |= (1 << (UART_CLK_EN + UART_NUMBER));
	UART_RST_PORT   |= (1 << (UART_CLK_EN + UART_NUMBER));

	RCU->UARTCFG[UART_NUMBER].UARTCFG = (1 << RCU_UARTCFG_CLKEN_Pos ) |
								  		(1 << RCU_UARTCFG_RSTDIS_Pos) |
								  		(0 << RCU_UARTCFG_DIVEN_Pos) |
								  		(0 << RCU_UARTCFG_DIVN_Pos) |
								  		(2 << RCU_UARTCFG_CLKSEL_Pos);
	UART->IFLS  = 1 << UART_IFLS_RXIFLSEL_Pos |
    		 	   1 << UART_IFLS_TXIFLSEL_Pos;
	UART->IMSC = UART_IMSC_RXIM_Msk;
	PLIC_SetIrqHandler (Plic_Mach_Target, UART_RX_IRQn, UART_IRQHandler);
    PLIC_SetPriority   (UART_RX_IRQn, 0x1);
    PLIC_SetMode  	   (UART_RX_IRQn, PLIC_IRQMODE_HILEVEL);
    PLIC_IntEnable     (Plic_Mach_Target, UART_RX_IRQn);

}


void GpioInit(void){
    #ifdef BOOTEN
    RCU->CGCFGAHB  |= BOOTEN_PORT_EN;
    RCU->RSTDISAHB |= BOOTEN_PORT_EN;
    BOOTEN_PORT->PULLMODE |= 1 << (BOOTEN_PIN_POS * 2); // enable Pull Up
    #endif
}
void TimersInit(void){
    //tbd015
    TIMER_CLK |= UART_TMR_EN_Msk; // | TIMEOUT_TMR_EN_Msk;
    TIMER_RST |= UART_TMR_EN_Msk; // | TIMEOUT_TMR_EN_Msk;
    UART_TMR->CTRL_bit.MODE = 0;
    UART_TMR->CTRL_bit.CLR = 1;
    SIU_TIMER |= SIU_MASK;
}

void PeriphInit(void){
  //riscv_irq_init();
  //PLIC_Init();
    //allow all interrupts in machine mode
    PLIC_SetThreshold (Plic_Mach_Target, 0); //allow all interrupts in machine mode
    // disable timer interrupt
    clear_csr(mie, MIE_MTIMER);
    // enable machine external interrupt
    set_csr(mie, MIE_MEXTERNAL);
    // enable global interrupts
    set_csr(mstatus, MSTATUS_MIE);
  GpioInit();
  ClkInit();
  UartInit();
  TimersInit();
}

void enter_boot_mode() {
#ifdef BOOTEN
    RCU->CGCFGAHB  = BOOTEN_PORT_EN;
    RCU->RSTDISAHB = BOOTEN_PORT_EN;

    BOOTEN_PORT->PULLMODE = BOOTEN_PIN_MSK;

    if ((BOOTEN_PORT->DATA & BOOTEN_PIN_MSK) != 0) {
        __asm__ volatile("jr %0" : : "value" (USER_JUMP_ADDRESS));
    }
#endif
}

int main(void) {
    enter_boot_mode();
    PeriphInit();

    boot_init();

    boot_core();

    return 0;

}