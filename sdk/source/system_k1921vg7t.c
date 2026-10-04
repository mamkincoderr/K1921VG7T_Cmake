/*==============================================================================
 * Инициализация K1921VG7T
 *------------------------------------------------------------------------------
 * НИИЭТ, Александр Дыхно <dykhno@niiet.ru>
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
 *                              2025 АО "НИИЭТ"
 *==============================================================================
 */

//-- Includes ------------------------------------------------------------------
#include "system_k1921vg7t.h"
#include "plic.h"
#include "K1921VG7T.h"

//-- Variables -----------------------------------------------------------------
uint32_t SystemCoreClock; // System Clock Frequency (Core Clock)
uint32_t SystemPllClock; // System PLLClock Frequency

//-- Functions -----------------------------------------------------------------
void SystemCoreClockUpdate(void)
{
    uint32_t current_sysclk;
    uint32_t pll_fvco;
    uint32_t pll_refclk, pll_pda, pll_pdb, pll_prediv, pll_rdiv, pll_ndiv;
    current_sysclk = RCU->CLKSTAT_bit.SRC;
  	pll_refclk = HSECLK_VAL;
   	pll_prediv = RCU->PLLDIV_bit.PREDIV;
   	pll_rdiv = RCU->PLLDIV_bit.RDIV;
    pll_ndiv = RCU->PLLDIV_bit.NDIV;
   	pll_pda = RCU->PLLDIV_bit.DIV1A + 1;
   	pll_pdb = RCU->PLLDIV_bit.DIV1B + 1;
   	pll_fvco = pll_refclk*pll_ndiv*pll_prediv/pll_rdiv;
   	SystemPllClock = pll_fvco/(pll_prediv*pll_pda*pll_pdb);
    switch (current_sysclk) {
    case RCU_CLKSTAT_SRC_HSICLK:
        SystemCoreClock = HSICLK_VAL;
        break;
    case RCU_CLKSTAT_SRC_HSECLK:
        SystemCoreClock = HSECLK_VAL;
        break;
    case RCU_CLKSTAT_SRC_PLLCLK:
#if defined(SYSCLK_PLL) && (HSECLK_VAL == 16000000)
        // Формула SDK для частоты PLL даёт заведомо неверное значение (200 МГц при реальных
        // 100 МГц), поэтому для настройки из ClkInit() частота задана замером.
        SystemPllClock = 100000000;
#endif
    	SystemCoreClock = SystemPllClock;
    	break;
    case RCU_CLKSTAT_SRC_EXTCLK:
    	SystemCoreClock = EXTCLK_VAL;
        break;
    }

}

void ClkInit()
{
    uint32_t timeout_counter = 0;
    uint32_t sysclk_source;

    //clockout control
    #ifndef CKO_NONE
        //A1 clockout
        RCU->CGCFGAHB_bit.GPIOAEN = 1;
        RCU->RSTDISAHB_bit.GPIOAEN = 1;
        GPIOA->ALTFUNCNUM_bit.PIN1 = 3;
        GPIOA->ALTFUNCSET_bit.PIN1 = 1;
    #endif

    #if defined CKO_HSI
        RCU->CLKOUTCFG = (RCU_CLKOUTCFG_CLKSEL_HSICLK << RCU_CLKOUTCFG_CLKSEL_Pos) |
        				  (1 << RCU_CLKOUTCFG_DIVN_Pos) |
						  (0 << RCU_CLKOUTCFG_DIVEN_Pos) |
        				  RCU_CLKOUTCFG_CLKEN_Msk; //CKO = HSICLK
    #elif defined CKO_HSE
        RCU->CLKOUTCFG = (RCU_CLKOUTCFG_CLKSEL_HSECLK << RCU_CLKOUTCFG_CLKSEL_Pos) |
				  	  	  (1 << RCU_CLKOUTCFG_DIVN_Pos) |
						  (0 << RCU_CLKOUTCFG_DIVEN_Pos) |
						  RCU_CLKOUTCFG_CLKEN_Msk; //CKO = HSECLK
    #elif defined CKO_PLL
        RCU->CLKOUTCFG = (RCU_CLKOUTCFG_CLKSEL_PLLCLK << RCU_CLKOUTCFG_CLKSEL_Pos) |
				  	  	  (1 << RCU_CLKOUTCFG_DIVN_Pos) |
						  (1 << RCU_CLKOUTCFG_DIVEN_Pos) |
						  RCU_CLKOUTCFG_CLKEN_Msk; //CKO = PLLCLK / 4
    #elif defined CKO_RTC
        RCU->CLKOUTCFG = (RCU_CLKOUTCFG_CLKSEL_RTCCLK << RCU_CLKOUTCFG_CLKSEL_Pos) |
				  	  	  (1 << RCU_CLKOUTCFG_DIVN_Pos) |
						  (0 << RCU_CLKOUTCFG_DIVEN_Pos) |
						  RCU_CLKOUTCFG_CLKEN_Msk; //CKO = LSICLK or LSECLK
    #endif

//select system clock
#ifdef SYSCLK_PLL
	//PLLCLK = REFCLK * (FBDIV+FRAC/2^24) / (REFDIV*(1+PD0A)*(1+PD0B))
	
	//select HSE as source system clock while config PLL
	RCU->SYSCLKCFG = (RCU_SYSCLKCFG_SRC_HSECLK << RCU_SYSCLKCFG_SRC_Pos);
    // Wait switching done
    timeout_counter = 0;
    while ((RCU->CLKSTAT_bit.SRC != RCU->SYSCLKCFG_bit.SRC) && (timeout_counter < 100)){ //SYSCLK_SWITCH_TIMEOUT))
        timeout_counter++;
    }  						  
#if (HSECLK_VAL == 10000000)
// Fout0 = 100 000 000 Hz
    RCU->PLLDIV = ( 1 << RCU_PLLDIV_DIV1A_Pos ) |
                  ( 1 << RCU_PLLDIV_DIV1B_Pos ) |             // DIV1B + 1
                  ( 2 << RCU_PLLDIV_PREDIV_Pos) |
                  ( 1 << RCU_PLLDIV_NNCLR_Pos ) |             // N-divider enable
                  ( 1 << RCU_PLLDIV_RNCLR_Pos ) |             // R-divider enable
                  ( 1 << RCU_PLLDIV_RDIV_Pos  ) |
                  (80 << RCU_PLLDIV_NDIV_Pos  );
	RCU->PLLMOD  = (1 << RCU_PLLFRAC_FRAC_Pos );
	RCU->PLLFRAC = (1 << RCU_PLLMOD_MOD_Pos   );
	RCU->PLLCFG  = (1 << RCU_PLLCFG_FOUTEN_Pos ) |
			       (3 << RCU_PLLCFG_PFD_Pos    ) |
			       (0 << RCU_PLLCFG_CLKSEL_Pos ) |
			       (1 <<RCU_PLLCFG_VCOMODE_Pos);            // Fout enable
#elif (HSECLK_VAL == 12000000)
// Fout = 100 000 000 Hz
    RCU->PLLDIV = ( 2 << RCU_PLLDIV_DIV1A_Pos ) |
                  ( 1 << RCU_PLLDIV_DIV1B_Pos ) |             // DIV1B + 1
                  ( 2 << RCU_PLLDIV_PREDIV_Pos) |
                  ( 1 << RCU_PLLDIV_NNCLR_Pos ) |             // N-divider enable
                  ( 1 << RCU_PLLDIV_RNCLR_Pos ) |             // R-divider enable
                  ( 1 << RCU_PLLDIV_RDIV_Pos  ) |
                  (100 << RCU_PLLDIV_NDIV_Pos  );
	RCU->PLLMOD  = (1 << RCU_PLLFRAC_FRAC_Pos );
	RCU->PLLFRAC = (1 << RCU_PLLMOD_MOD_Pos   );
	RCU->PLLCFG  = (1 << RCU_PLLCFG_FOUTEN_Pos ) |
			       (3 << RCU_PLLCFG_PFD_Pos    ) |
			       (0 << RCU_PLLCFG_CLKSEL_Pos ) |
			       (1 <<RCU_PLLCFG_VCOMODE_Pos);            // Fout enable
#elif (HSECLK_VAL == 16000000)
// Исправлено относительно SDK НИИЭТ: DIV1A = 2 (в SDK было 3).
// Измерено на плате NIIET-MINI-K1921VG7T rev 2.0 (кварц 16 МГц): с DIV1A = 3 ядро работает на
// ~75 МГц, с DIV1A = 2 на ~100 МГц. Замер: счётчик mcycle против частоты UART и интервал
// таймера против часов ПК.
    RCU->PLLDIV = ( 2 << RCU_PLLDIV_DIV1A_Pos ) |
                  ( 1 << RCU_PLLDIV_DIV1B_Pos ) |             // DIV1B + 1
                  ( 2 << RCU_PLLDIV_PREDIV_Pos) |
                  ( 1 << RCU_PLLDIV_NNCLR_Pos ) |             // N-divider enable
                  ( 1 << RCU_PLLDIV_RNCLR_Pos ) |             // R-divider enable
                  ( 1 << RCU_PLLDIV_RDIV_Pos  ) |
                  (100 << RCU_PLLDIV_NDIV_Pos  );
	RCU->PLLMOD  = (1 << RCU_PLLFRAC_FRAC_Pos );
	RCU->PLLFRAC = (1 << RCU_PLLMOD_MOD_Pos   );
	RCU->PLLCFG  = (1 << RCU_PLLCFG_FOUTEN_Pos ) |
			       (3 << RCU_PLLCFG_PFD_Pos    ) |
			       (0 << RCU_PLLCFG_CLKSEL_Pos ) |
			       (1 <<RCU_PLLCFG_VCOMODE_Pos);            // Fout enable
#elif (HSECLK_VAL == 20000000)
// Fout = 100 000 000 Hz
    RCU->PLLDIV = ( 1 << RCU_PLLDIV_DIV1A_Pos ) |
                  ( 1 << RCU_PLLDIV_DIV1B_Pos ) |             // DIV1B + 1
                  ( 2 << RCU_PLLDIV_PREDIV_Pos) |
                  ( 1 << RCU_PLLDIV_NNCLR_Pos ) |             // N-divider enable
                  ( 1 << RCU_PLLDIV_RNCLR_Pos ) |             // R-divider enable
                  ( 1 << RCU_PLLDIV_RDIV_Pos  ) |
                  (40 << RCU_PLLDIV_NDIV_Pos  );
	RCU->PLLMOD  = (1 << RCU_PLLFRAC_FRAC_Pos );
	RCU->PLLFRAC = (1 << RCU_PLLMOD_MOD_Pos   );
	RCU->PLLCFG  = (1 << RCU_PLLCFG_FOUTEN_Pos ) |
			       (3 << RCU_PLLCFG_PFD_Pos    ) |
			       (0 << RCU_PLLCFG_CLKSEL_Pos ) |
			       (1 <<RCU_PLLCFG_VCOMODE_Pos);            // Fout enable
#elif (HSECLK_VAL == 24000000)
// Fout = 100 000 000 Hz
    RCU->PLLDIV = ( 2 << RCU_PLLDIV_DIV1A_Pos ) |
                  ( 1 << RCU_PLLDIV_DIV1B_Pos ) |             // DIV1B + 1
                  ( 2 << RCU_PLLDIV_PREDIV_Pos) |
                  ( 1 << RCU_PLLDIV_NNCLR_Pos ) |             // N-divider enable
                  ( 1 << RCU_PLLDIV_RNCLR_Pos ) |             // R-divider enable
                  ( 1 << RCU_PLLDIV_RDIV_Pos  ) |
                  (50 << RCU_PLLDIV_NDIV_Pos  );
	RCU->PLLMOD  = (1 << RCU_PLLFRAC_FRAC_Pos );
	RCU->PLLFRAC = (1 << RCU_PLLMOD_MOD_Pos   );
	RCU->PLLCFG  = (1 << RCU_PLLCFG_FOUTEN_Pos ) |
			       (3 << RCU_PLLCFG_PFD_Pos    ) |
			       (0 << RCU_PLLCFG_CLKSEL_Pos ) |
			       (1 <<RCU_PLLCFG_VCOMODE_Pos);            // Fout enable
#else
#error "Please define HSECLK_VAL with correct values!"
#endif
	RCU->PLLCFG_bit.VCOMODE = 1;
	timeout_counter = 1000;
	while(timeout_counter) timeout_counter--;// wait lock signal
	//select PLL as source system clock
	sysclk_source = RCU_SYSCLKCFG_SRC_PLLCLK;
    // FLASH control settings
    FLASH->CTRL_bit.LAT = 3;
//    FLASH->CTRL_bit.CEN = 1;
#elif defined SYSCLK_HSI
    sysclk_source = RCU_SYSCLKCFG_SRC_HSICLK;
#elif defined SYSCLK_HSE
    sysclk_source = RCU_SYSCLKCFG_SRC_HSECLK;
#elif defined SYSCLK_LSI
    sysclk_source = RCU_SYSCLKCFG_SRC_EXTCLK;
#else
#error "Please define SYSCLK source (SYSCLK_PLL | SYSCLK_HSE | SYSCLK_HSI | SYSCLK_EXT)!"
#endif

    //switch sysclk
    RCU->SYSCLKCFG = (sysclk_source << RCU_SYSCLKCFG_SRC_Pos);
    // Wait switching done
    timeout_counter = 0;
    while ((RCU->CLKSTAT_bit.SRC != RCU->SYSCLKCFG_bit.SRC) && (timeout_counter < 100)) //SYSCLK_SWITCH_TIMEOUT))
        timeout_counter++;
/*    if (timeout_counter == SYSCLK_SWITCH_TIMEOUT) //SYSCLK failed to switch
        while (1) {
        };*/

}

void InterruptEnable()
{
	//allow all interrupts in machine mode
	PLIC_SetThreshold (Plic_Mach_Target, 0); //allow all interrupts in machine mode
    // disable timer interrupt
    clear_csr(mie, MIE_MTIMER);
    // enable machine external interrupt
    set_csr(mie, MIE_MEXTERNAL);
    // enable global interrupts
    set_csr(mstatus, MSTATUS_MIE);
}

void InterruptDisable()
{
	//disable all interrupts in machine mode
	PLIC_SetThreshold (Plic_Mach_Target, 7); //Disable all interrupts in machine mode
    // disable machine external interrupt
    clear_csr(mie, MIE_MEXTERNAL);
    // disable global interrupts
    clear_csr(mstatus, MSTATUS_MIE);
}

void SystemInit(void)
{
	// PLIC configuration
	// disable timer interrupt
//	clear_csr(mie, MIE_MTIMER);
	// enable machine external interrupt
//	set_csr(mie, MIE_MEXTERNAL);
	// enable global interrupts
//	set_csr(mstatus, MSTATUS_MIE);
	ClkInit();
}

