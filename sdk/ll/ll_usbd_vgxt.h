#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <ll_assert.h>
#include <ll_pll.h>
#include <ll_rcu.h>
#include <prelude.h>
#include <soc.h>

#if defined K1921VG1T
#define LL_USBD_OUT_EP_NUM 4
#define LL_USBD_IN_EP_NUM  4
#elif defined K1921VG3T
#define LL_USBD_OUT_EP_NUM 4
#define LL_USBD_IN_EP_NUM  4
#endif

typedef struct {
    ll_pll_t pll;
    sdk_clock_t clock;
    uint8_t clk_divider;
    bool use_ext_phy;
    bool switch_polarity;
} ll_usbd_init_t;

typedef struct {
    USBDC_TypeDef *usbdc;
    USBCTR_TypeDef *usbctr;
    ll_rcu_periph_t rcu;
    uint32_t isr_vector;
} ll_usbd_t;

#if defined K1921VG1T
#define LL_USBD0 ((ll_usbd_t){USBDC0, USBCTR0, LL_RCU_USBD0, IsrVect_IRQ_USB0})
#define LL_USBD1 ((ll_usbd_t){USBDC1, USBCTR1, LL_RCU_USBD1, IsrVect_IRQ_USB1})
#elif defined K1921VG3T
#define LL_USBD0 ((ll_usbd_t){USBDC, USBCTR, LL_RCU_USBD0, IsrVect_IRQ_USB})
#endif

#if defined K1921VG1T
#define LL_USBD_NUM 2
#elif defined K1921VG3T
#define LL_USBD_NUM 1
#endif

typedef enum __attribute__((packed)) {
    LL_USBD_IRQ_NONE      = 0b0000,
    LL_USBD_IRQ_RESET     = 0b0001,
    LL_USBD_IRQ_VBUSVALID = 0b0010,
    LL_USBD_IRQ_SUSPEND   = 0b0100,
    LL_USBD_IRQ_FRAME     = 0b1000,
} ll_usbd_irq_t;

typedef enum __attribute__((packed)) {
    LL_USBD_SPEED_HIGH   = 0,
    LL_USBD_SPEED_FULL   = 1,
    _LL_USBD_SPEED_LIMIT = 2,  // NOLINT
} ll_usbd_speed_t;

typedef enum __attribute__((packed)) {
    LL_USBD_EP_DIR_OUT = 0x00,
    LL_USBD_EP_DIR_IN  = 0x80,
} ll_usbd_ep_dir_t;

typedef enum __attribute__((packed)) {
    LL_USBD_EP_TYPE_CONTROL   = 0b00,
    LL_USBD_EP_TYPE_ISO       = 0b01,
    LL_USBD_EP_TYPE_BULK      = 0b10,
    LL_USBD_EP_TYPE_INTERRUPT = 0b11,
    _LL_USBD_EP_TYPE_LIMIT    = 0b100,  // NOLINT
} ll_usbd_ep_type_t;

#define LL_USBD_IRQ_DEFAULT (LL_USBD_IRQ_RESET | LL_USBD_IRQ_VBUSVALID | LL_USBD_IRQ_SUSPEND)

typedef struct {
    volatile uint32_t *ctrl;
    volatile uint32_t *dmactrl;
    volatile uint32_t *dmadesc;
    volatile uint32_t *stat;
    uint8_t ev_pos, ed_pos, eh_pos, tt_pos, nt_pos, maxpl_pos, cb_pos, pi_pos;
    uint8_t dma_da_pos, dma_ie_pos, dma_ai_pos, dma_ad_pos;
    uint8_t transfer_done_pos, b0_pos, b1_pos;
    ll_usbd_ep_dir_t _dir;
    uint8_t _num;
} ll_usbd_ep_t;

#ifdef K1921VG1T
#define LL_USBD_PTR_VALID(ptr)                                                                                        \
    (((uint32_t)(ptr) >= (uint32_t)USBDC0_BASE && (uint32_t)(ptr) < (uint32_t)USBDC0_BASE + sizeof(USBDC_TypeDef)) || \
     ((uint32_t)(ptr) >= (uint32_t)USBDC1_BASE && (uint32_t)(ptr) < (uint32_t)USBDC1_BASE + sizeof(USBDC_TypeDef)))
#elif defined K1921VG3T
#define LL_USBD_PTR_VALID(ptr) \
    ((uint32_t)(ptr) >= (uint32_t)USBDC_BASE && (uint32_t)(ptr) < (uint32_t)USBDC_BASE + sizeof(USBDC_TypeDef))
#endif
#define LL_USBD_EPO(usbdc_ptr, n)                              \
    ((ll_usbd_ep_t){                                           \
        .ctrl              = &((usbdc_ptr)->EPO[(n)].CTRL),    \
        .dmactrl           = &((usbdc_ptr)->EPO[(n)].DMACTRL), \
        .dmadesc           = &((usbdc_ptr)->EPO[(n)].DMADESC), \
        .stat              = &((usbdc_ptr)->EPO[(n)].STAT),    \
        .ev_pos            = USBDC_EPO_CTRL_EV_Pos,            \
        .ed_pos            = USBDC_EPO_CTRL_ED_Pos,            \
        .eh_pos            = USBDC_EPO_CTRL_EH_Pos,            \
        .tt_pos            = USBDC_EPO_CTRL_TT_Pos,            \
        .nt_pos            = USBDC_EPO_CTRL_NT_Pos,            \
        .maxpl_pos         = USBDC_EPO_CTRL_MAXPL_Pos,         \
        .cb_pos            = USBDC_EPO_CTRL_CB_Pos,            \
        .pi_pos            = USBDC_EPO_CTRL_PI_Pos,            \
        .dma_da_pos        = USBDC_EPO_DMACTRL_DA_Pos,         \
        .dma_ie_pos        = USBDC_EPO_DMACTRL_IE_Pos,         \
        .dma_ai_pos        = USBDC_EPO_DMACTRL_AI_Pos,         \
        .dma_ad_pos        = USBDC_EPO_DMACTRL_AD_Pos,         \
        .transfer_done_pos = USBDC_EPO_STAT_PR_Pos,            \
        .b0_pos            = USBDC_EPO_STAT_B0_Pos,            \
        .b1_pos            = USBDC_EPO_STAT_B1_Pos,            \
        ._dir              = LL_USBD_EP_DIR_OUT,               \
        ._num              = (n),                              \
    })

#define LL_USBD_EPO0(ll_usb) LL_USBD_EPO(ll_usb.usbdc, 0)
#define LL_USBD_EPO1(ll_usb) LL_USBD_EPO(ll_usb.usbdc, 1)
#define LL_USBD_EPO2(ll_usb) LL_USBD_EPO(ll_usb.usbdc, 2)
#define LL_USBD_EPO3(ll_usb) LL_USBD_EPO(ll_usb.usbdc, 3)

#define LL_USBD_EPI(usbdc_ptr, n)                              \
    ((ll_usbd_ep_t){                                           \
        .ctrl              = &((usbdc_ptr)->EPI[(n)].CTRL),    \
        .dmactrl           = &((usbdc_ptr)->EPI[(n)].DMACTRL), \
        .dmadesc           = &((usbdc_ptr)->EPI[(n)].DMADESC), \
        .stat              = &((usbdc_ptr)->EPI[(n)].STAT),    \
        .ev_pos            = USBDC_EPI_CTRL_EV_Pos,            \
        .ed_pos            = USBDC_EPI_CTRL_ED_Pos,            \
        .eh_pos            = USBDC_EPI_CTRL_EH_Pos,            \
        .tt_pos            = USBDC_EPI_CTRL_TT_Pos,            \
        .nt_pos            = USBDC_EPI_CTRL_NT_Pos,            \
        .maxpl_pos         = USBDC_EPI_CTRL_MAXPL_Pos,         \
        .cb_pos            = USBDC_EPI_CTRL_CB_Pos,            \
        .pi_pos            = USBDC_EPI_CTRL_PI_Pos,            \
        .dma_da_pos        = USBDC_EPI_DMACTRL_DA_Pos,         \
        .dma_ie_pos        = USBDC_EPI_DMACTRL_IE_Pos,         \
        .dma_ai_pos        = USBDC_EPI_DMACTRL_AI_Pos,         \
        .dma_ad_pos        = USBDC_EPI_DMACTRL_AD_Pos,         \
        .transfer_done_pos = USBDC_EPI_STAT_PT_Pos,            \
        .b0_pos            = USBDC_EPI_STAT_B0_Pos,            \
        .b1_pos            = USBDC_EPI_STAT_B1_Pos,            \
        ._dir              = LL_USBD_EP_DIR_IN,                \
        ._num              = (n),                              \
    })

#define LL_USBD_EPI0(ll_usb) LL_USBD_EPI(ll_usb.usbdc, 0)
#define LL_USBD_EPI1(ll_usb) LL_USBD_EPI(ll_usb.usbdc, 1)
#define LL_USBD_EPI2(ll_usb) LL_USBD_EPI(ll_usb.usbdc, 2)
#define LL_USBD_EPI3(ll_usb) LL_USBD_EPI(ll_usb.usbdc, 3)

/// INIT

static inline void ll_usbd_ctr_init(ll_usbd_t usb, ll_usbd_init_t *init)
{
    LL_ASSERT(IS_USBCTR_PERIPH(usb.usbctr));
    LL_ASSERT(init != NULL);
    usb.usbctr->PHYCFG0_bit.EXTPHY = init->use_ext_phy;
    usb.usbctr->PHYCFG0_bit.POL    = init->switch_polarity;
    usb.usbctr->HOSTEN             = 0;
}

static inline bool ll_usbd_wait_utmi(ll_usbd_t usb, uint32_t spins)
{
    LL_ASSERT(IS_USBCTR_PERIPH(usb.usbctr));
    while (spins--) {
        if (usb.usbctr->PHYSTAT_bit.UTMI_CLK_EN) {
            return true;
        }
    }
    return false;
}

static inline void ll_usbd_init(ll_usbd_t usbd, ll_usbd_init_t *init)
{
    LL_ASSERT(IS_USBDC_PERIPH(usbd.usbdc));
    LL_ASSERT(IS_USBCTR_PERIPH(usbd.usbctr));
    LL_ASSERT(init->clk_divider <= 130 && init->clk_divider % 2 == 0);
    ll_rcu_clock_enable(usbd.rcu);
    ll_rcu_reset_release(usbd.rcu);

    if (usbd.rcu.clkcfg) {
        volatile uint32_t *usbcfg = usbd.rcu.clkcfg;
        const uint32_t rstdis_msk = _ll_rcu_rstdis_msk(usbd.rcu);

        *usbcfg |= rstdis_msk;

        ll_rcu_set_source(usbd.rcu, (ll_rcu_clksel_t)init->pll.number);

        if (init->clk_divider == 0) {
            ll_rcu_set_divider(usbd.rcu, false, 0);
        } else {
            ll_rcu_set_divider(usbd.rcu, true, (init->clk_divider / 2) - 1);
        }

        *usbcfg |= (1U << usbd.rcu.clken_pos);
        *usbcfg &= ~rstdis_msk;
    }

    ll_usbd_ctr_init(usbd, init);
    if (!init->use_ext_phy) {
        LL_ASSERT(ll_usbd_wait_utmi(usbd, 10000));
    } else {
        LL_ASSERT(init->clock.sleep != NULL);
        init->clock.sleep(20);
    }
}

/// CONTROL

static inline void ll_usbd_reset_out_ep(ll_usbd_t usbd, uint8_t endpoint_num)
{
    LL_ASSERT(IS_USBDC_PERIPH(usbd.usbdc));
    LL_ASSERT(endpoint_num < LL_USBD_OUT_EP_NUM);
    usbd.usbdc->EPO[endpoint_num].CTRL    = 0;
    usbd.usbdc->EPO[endpoint_num].DMACTRL = 0;
    usbd.usbdc->EPO[endpoint_num].DMADESC = 0;
}

static inline void ll_usbd_reset_in_ep(ll_usbd_t usbd, uint8_t endpoint_num)
{
    LL_ASSERT(IS_USBDC_PERIPH(usbd.usbdc));
    LL_ASSERT(endpoint_num < LL_USBD_IN_EP_NUM);
    usbd.usbdc->EPI[endpoint_num].CTRL    = 0;
    usbd.usbdc->EPI[endpoint_num].DMACTRL = 0;
    usbd.usbdc->EPI[endpoint_num].DMADESC = 0;
}

static inline void ll_usbd_clear_buffers_out_ep(ll_usbd_t usbd, uint8_t endpoint_num)
{
    LL_ASSERT(IS_USBDC_PERIPH(usbd.usbdc));
    LL_ASSERT(endpoint_num < LL_USBD_OUT_EP_NUM);
    usbd.usbdc->EPO[endpoint_num].CTRL_bit.CB = 1;
    usbd.usbdc->EPO[endpoint_num].CTRL_bit.CB = 0;
}

static inline void ll_usbd_clear_buffers_in_ep(ll_usbd_t usbd, uint8_t endpoint_num)
{
    LL_ASSERT(IS_USBDC_PERIPH(usbd.usbdc));
    LL_ASSERT(endpoint_num < LL_USBD_IN_EP_NUM);
    usbd.usbdc->EPI[endpoint_num].CTRL_bit.CB = 1;
    usbd.usbdc->EPI[endpoint_num].CTRL_bit.CB = 0;
}

static inline void ll_usbd_pullup(ll_usbd_t usbd, bool enable)
{
    LL_ASSERT(IS_USBDC_PERIPH(usbd.usbdc));
    usbd.usbdc->GCTRL_bit.EP = enable;
}

static inline void ll_usbd_set_address(ll_usbd_t usbd, uint8_t address)
{
    LL_ASSERT(IS_USBDC_PERIPH(usbd.usbdc));
    usbd.usbdc->GCTRL |= (address << USBDC_GCTRL_UA_Pos) | (1 << USBDC_GCTRL_SU_Pos);
}

static inline void ll_usbd_set_speed(ll_usbd_t usbd, ll_usbd_speed_t speed)
{
    LL_ASSERT(IS_USBDC_PERIPH(usbd.usbdc));
    LL_ASSERT(speed < _LL_USBD_SPEED_LIMIT);
    usbd.usbdc->GCTRL_bit.DH = speed;
}

static inline void ll_usbd_full_reset(ll_usbd_t usbd)
{
    LL_ASSERT(IS_USBDC_PERIPH(usbd.usbdc));
    USBDC_TypeDef *usbdc = usbd.usbdc;
    usbdc->GCTRL         = 0;
    usbdc->GSTAT_bit.UR  = 1;
    for (int i = 0; i < LL_USBD_IN_EP_NUM; ++i) {
        ll_usbd_reset_in_ep(usbd, i);
    }
    for (int i = 0; i < LL_USBD_OUT_EP_NUM; ++i) {
        ll_usbd_reset_out_ep(usbd, i);
    }
}

/// STATE IRQ

static inline ll_usbd_irq_t ll_usbd_state_irq(ll_usbd_t usbd)
{
    LL_ASSERT(IS_USBDC_PERIPH(usbd.usbdc));
    const _USBDC_GSTAT_bits stat = usbd.usbdc->GSTAT_bit;
    return (stat.UR ? LL_USBD_IRQ_RESET : 0) |     //
           (!stat.SU ? LL_USBD_IRQ_SUSPEND : 0) |  //
           (stat.VB ? LL_USBD_IRQ_VBUSVALID : 0);
}

static inline void ll_usbd_reset_irq(ll_usbd_t usbd, ll_usbd_irq_t irq)
{
    LL_ASSERT(IS_USBDC_PERIPH(usbd.usbdc));
    if (irq & LL_USBD_IRQ_RESET) {
        usbd.usbdc->GSTAT_bit.UR = 1;
    }
}

static inline int ll_usbd_frame_number(ll_usbd_t usbd)
{
    LL_ASSERT(IS_USBDC_PERIPH(usbd.usbdc));
    return usbd.usbdc->GSTAT_bit.FN;
}

static inline bool ll_usbd_vbus_valid(ll_usbd_t usbd)
{
    LL_ASSERT(IS_USBDC_PERIPH(usbd.usbdc));
    return usbd.usbdc->GSTAT_bit.VB;
}

static inline void ll_usbd_enable_irq(ll_usbd_t usbd, ll_usbd_irq_t irq)
{
    LL_ASSERT(IS_USBDC_PERIPH(usbd.usbdc));
    USBDC_TypeDef *usbdc = usbd.usbdc;
    usbdc->GCTRL_bit.UI  = (irq & LL_USBD_IRQ_RESET) ? 1U : 0U;
    usbdc->GCTRL_bit.SI  = (irq & LL_USBD_IRQ_SUSPEND) ? 1U : 0U;
    usbdc->GCTRL_bit.VI  = (irq & LL_USBD_IRQ_VBUSVALID) ? 1U : 0U;
    usbdc->GCTRL_bit.FI  = (irq & LL_USBD_IRQ_FRAME) ? 1U : 0U;
}

/// ENDPOINTS

static inline void ll_usbd_ep_valid(ll_usbd_ep_t ep, bool valid)
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.ctrl));
    if (valid) {
        *ep.ctrl |= (1UL << ep.ev_pos);
    } else {
        *ep.ctrl &= ~(1UL << ep.ev_pos);
    }
}

static inline void ll_usbd_ep_enable(ll_usbd_ep_t ep, bool enable)
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.ctrl));
    if (!enable) {
        *ep.ctrl |= (1UL << ep.ed_pos);
    } else {
        *ep.ctrl &= ~(1UL << ep.ed_pos);
    }
}

static inline void ll_usbd_ep_set_max_pkt_len(ll_usbd_ep_t ep, uint16_t max_pkt_len)
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.ctrl));
    LL_ASSERT(max_pkt_len <= 1024);
    *ep.ctrl = (*ep.ctrl & ~(0x7FFUL << ep.maxpl_pos)) | ((uint32_t)max_pkt_len << ep.maxpl_pos);
}

static inline void ll_usbd_ep_set_num_trans(ll_usbd_ep_t ep, uint8_t num_transactions)
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.ctrl));
    LL_ASSERT(num_transactions < 4);
    *ep.ctrl = (*ep.ctrl & ~(0x3UL << ep.nt_pos)) | ((uint32_t)num_transactions << ep.nt_pos);
}

static inline void ll_usbd_ep_set_type(ll_usbd_ep_t ep, ll_usbd_ep_type_t type)
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.ctrl));
    LL_ASSERT(type < _LL_USBD_EP_TYPE_LIMIT);
    *ep.ctrl = (*ep.ctrl & ~(0x3UL << ep.tt_pos)) | ((uint32_t)type << ep.tt_pos);
}

static inline void ll_usbd_ep_halt_enable(ll_usbd_ep_t ep)
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.ctrl));
    *ep.ctrl |= (1 << ep.eh_pos);
}

static inline void ll_usbd_ep_halt_disable(ll_usbd_ep_t ep)
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.ctrl));
    *ep.ctrl &= ~(1 << ep.eh_pos);
}

static inline void ll_usbd_ep_pkt_irq_enable(ll_usbd_ep_t ep)
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.ctrl));
    *ep.ctrl |= (1UL << ep.pi_pos);
}

static inline bool ll_usbd_ep_get_pkt_irq_enabled(ll_usbd_ep_t ep)
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.ctrl));
    return (*ep.ctrl & (1UL << ep.pi_pos)) != 0U;
}

static inline void ll_usbd_ep_pkt_irq_disable(ll_usbd_ep_t ep)
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.ctrl));
    *ep.ctrl &= ~(1UL << ep.pi_pos);
}

static inline void ll_usbd_ep_dma_irq_enable(ll_usbd_ep_t ep)
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.dmactrl));
    *ep.dmactrl |= (1UL << ep.dma_ie_pos);
}

static inline void ll_usbd_ep_dma_irq_disable(ll_usbd_ep_t ep)
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.dmactrl));
    *ep.dmactrl &= ~(1UL << ep.dma_ie_pos);
}

static inline void ll_usbd_ep_dsc_available(ll_usbd_ep_t ep)
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.dmactrl));
    *ep.dmactrl |= (1 << ep.dma_da_pos);
}

static inline bool ll_usbd_ep_packet_irq(ll_usbd_ep_t ep)
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.stat));
    const bool transfer_done = (*ep.stat & (1 << ep.transfer_done_pos)) != 0U;
    if (transfer_done) {
        /// Only if already read to prevent data race
        *ep.stat |= (1 << ep.transfer_done_pos);
    }
    return transfer_done;
}

static inline bool ll_usbd_ep_busy(ll_usbd_ep_t ep)
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.stat));
    return ((*ep.stat & (1 << ep.b0_pos)) && (*ep.stat & (1 << ep.b1_pos))) != 0;
}

static inline void ll_usbd_ep_stop_dma_operation(ll_usbd_ep_t ep)
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.dmactrl));
    *ep.dmactrl |= (1 << ep.dma_ad_pos);
    *ep.dmactrl &= ~(1 << ep.dma_ad_pos);
}

/// DESCRIPTORS

static inline void ll_usbd_dsc_prep_rx(
    ll_usbd_ep_t ep, void *dsc,
    uint8_t *buffer)  // NOLINT : buffer is not const, usb-dma-descriptor is going to write there
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.dmadesc));
    LL_ASSERT(LL_USBD_PTR_VALID(ep.ctrl));
    LL_ASSERT(LL_USBD_PTR_VALID(ep.dmactrl));
    LL_ASSERT(dsc != NULL);
    LL_ASSERT(buffer != NULL);
    LL_ASSERT(SDK_IS_ALIGNED_4(dsc));

    _USBDC_EPO_DESCR_TypeDef *desc = dsc;

    desc->WORD0_bit.NX = 0;                 ///< no next dsc available
    desc->WORD0_bit.IE = 1;                 ///< enable dma irq on this desc
    desc->WORD1        = (uint32_t)buffer;  ///< set buffer to descriptor
    desc->WORD2        = 0x0;               ///< no next dsc available
    desc->WORD0_bit.EN = 1;                 ///< enable descriptor
    *ep.dmadesc        = (uint32_t)desc;    ///< set desc in endpoint
    ll_usbd_ep_pkt_irq_disable(ep);         ///< we dont care about these
    ll_usbd_ep_dma_irq_enable(ep);          ///< we do care about these
    ll_usbd_ep_dsc_available(ep);           ///< desciptor available
}

static inline void *ll_usbd_dsc_prep_rx_ext(
    ll_usbd_ep_t ep, void *dsc, uint16_t maxlen,
    uint8_t *buffer)  // NOLINT : buffer is not const, usb-dma-descriptor is going to write there
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.dmadesc));
    LL_ASSERT(LL_USBD_PTR_VALID(ep.ctrl));
    LL_ASSERT(LL_USBD_PTR_VALID(ep.dmactrl));
    LL_ASSERT(dsc != NULL);
    LL_ASSERT(buffer != NULL);
    LL_ASSERT(SDK_IS_ALIGNED_4(dsc));

    _USBDC_EPO_DESCR_TypeDef *head    = dsc;  ///< it is the linked list of descriptors in metal
    _USBDC_EPO_DESCR_TypeDef *current = head;

    uint16_t buf_idx = 0;

    while (1) {
        _USBDC_EPO_DESCR_TypeDef *next = (_USBDC_EPO_DESCR_TypeDef *)current->WORD2;
        LL_ASSERT(next == NULL || SDK_IS_ALIGNED_4((void *)next));
        void *chunk = &buffer[buf_idx];
        LL_ASSERT(SDK_IS_ALIGNED_4(chunk));
        current->WORD1            = (uint32_t)chunk;
        current->WORD0_bit.IE     = (next == NULL);  ///< enable dma irq only if this is the last descriptor
        current->WORD0_bit.NX     = (next != NULL);  ///< next dsc available if it is
        current->WORD0_bit.LENGTH = 0;
        current->WORD0_bit.EN     = 1;

        if (next == NULL) {
            break;
        }

        buf_idx += maxlen;
        current = next;
    }

    *ep.dmadesc = (uint32_t)head;
    ll_usbd_ep_pkt_irq_disable(ep);  ///< we dont care about these
    ll_usbd_ep_dma_irq_enable(ep);   ///< we do care about these
    ll_usbd_ep_dsc_available(ep);    ///< desciptor available
    return current;
}

static inline void ll_usbd_dsc_prep_tx(ll_usbd_ep_t ep, void *dsc)
{
    LL_ASSERT(LL_USBD_PTR_VALID(ep.dmadesc));
    LL_ASSERT(LL_USBD_PTR_VALID(ep.dmactrl));
    LL_ASSERT(dsc != NULL);
    LL_ASSERT(SDK_IS_ALIGNED_4(dsc));

    _USBDC_EPI_DESCR_TypeDef *head    = dsc;
    _USBDC_EPI_DESCR_TypeDef *current = head;

    while (1) {
        _USBDC_EPI_DESCR_TypeDef *next = (_USBDC_EPI_DESCR_TypeDef *)current->WORD2;
        LL_ASSERT(next == NULL || SDK_IS_ALIGNED_4((void *)next));

        current->WORD0_bit.IE = 1;
        current->WORD0_bit.PI = 1;
        current->WORD0_bit.MO = (next != NULL);
        current->WORD0_bit.NX = (next != NULL);
        current->WORD0_bit.EN = 1;
        if (next == NULL) {
            break;
        }
        current = next;
    }

    *ep.dmadesc = (uint32_t)head;
    ll_usbd_ep_dma_irq_enable(ep);
    ll_usbd_ep_dsc_available(ep);  ///< desciptor available
}

static inline bool ll_usbd_dsc_busy(void *dsc)
{
    LL_ASSERT(dsc != NULL);
    LL_ASSERT(SDK_IS_ALIGNED_4(dsc));
    const uint32_t word_0 = *(uint32_t *)dsc;
    return (word_0 & USBDC_EPO_DESCR_WORD0_EN_Msk) != 0U;
}

static inline bool ll_usbd_dsc_setup(void *dsc)
{
    LL_ASSERT(dsc != NULL);
    LL_ASSERT(SDK_IS_ALIGNED_4(dsc));
    const uint32_t word_0 = *(uint32_t *)dsc;
    return (word_0 & USBDC_EPO_DESCR_WORD0_SE_Msk) != 0U;
}

static inline uint16_t ll_usbd_dsc_get_data(void *dsc, uint8_t *buffer, uint16_t max_size_to_copy)
{
    LL_ASSERT(dsc != NULL && buffer != NULL);
    LL_ASSERT(SDK_IS_ALIGNED_4(dsc));

    _USBDC_EPO_DESCR_TypeDef *desc = dsc;

    uint16_t ret_len = 0;

    while (desc != NULL) {
        uint16_t chunk_len = (uint16_t)desc->WORD0_bit.LENGTH;
        LL_ASSERT(max_size_to_copy - ret_len >= chunk_len);

        uint8_t *src = (uint8_t *)desc->WORD1;
        uint8_t *dst = &buffer[ret_len];

        LL_ASSERT(src >= dst);

        if (src != dst) {
            memcpy(dst, src, chunk_len);
        }

        ret_len += chunk_len;
        desc = (void *)desc->WORD2;
        LL_ASSERT(desc == NULL || SDK_IS_ALIGNED_4((void *)desc));
    }

    return ret_len;
}
