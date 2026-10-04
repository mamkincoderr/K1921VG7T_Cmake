/*==============================================================================
 * UART загрузчик для К1921ВГXT
 *
 * Функции работы с флеш-памятью.
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

#include "boot_flash.h"
#include "boot_packet.h"

//-- Private functions ---------------------------------------------------------
__attribute__((noinline, section(".ramfunc")))
static  void flash_cmd(uint32_t addr, FlashType_TypeDef ftype, uint32_t* data, FlashCmd_TypeDef cmd)
{
    while (FLASH->STAT_bit.BUSY);
    UART->IMSC = 0;
    for(int i=0;i<50;i++) __asm__ volatile("nop");
        
    FLASH->ADDR = addr;
    
    if (cmd == FLASH_WR) {
        for(int cell=0;cell<FLASH_CELL_WORD_WIDTH;cell++){
            FLASH->DATA[cell].DATA = (uint32_t) data[cell];
        }
    }
    FLASH->CMD = FLASH_MAGICKEY_CONST << FLASH_CMD_KEY_Pos |
                  cmd | ftype << FLASH_CMD_NVRON_Pos;
    for(int i=0;i<50;i++) __asm__ volatile("nop");
    while (FLASH->STAT_bit.BUSY) UART_IRQHandler();
    UART->IMSC = UART_IMSC_RXIM_Msk;
    if (cmd == FLASH_RD) {
        for(int cell=0;cell<FLASH_CELL_WORD_WIDTH;cell++){
            data[cell] = FLASH->DATA[cell].DATA;
        }
    }
}

void flash_read(uint32_t addr, FlashType_TypeDef ftype, uint32_t* data)
{
    flash_cmd(addr, ftype, data, FLASH_RD);
}

void flash_write(uint32_t addr, FlashType_TypeDef ftype, const uint32_t* data)
{
    flash_cmd(addr, ftype, (uint32_t*)data, FLASH_WR);
    //~42.5us
}

void flash_erase_page(uint32_t addr, FlashType_TypeDef ftype)
{
    flash_cmd(addr, ftype, NULL, FLASH_ERSEC);
    //~160ms
}

void flash_erase_full()
{
    flash_cmd(0, FLASH_MAIN, NULL, FLASH_ALLSEC);
    //~160ms
}


