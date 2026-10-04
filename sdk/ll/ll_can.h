/**
 * @file ll_can.h
 * @brief Low-level CAN driver.
 *
 * @defgroup ll_can LL CAN
 * @{
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include <ll_assert.h>
#include <soc.h>

#if defined(K1921VG015) || defined(K1921VG5T) || defined(K1921VG7T)
/** @brief Number of independent CAN nodes the controller exposes. */
#define LL_CAN_NODE_COUNT 2
#elif defined(K1921VG1T) || defined(K1921VG3T)
#define LL_CAN_NODE_COUNT 4
#else
#error "ll_can.h: unsupported SoC"
#endif

/** @brief Total message objects in the shared @c CANMSG pool. */
#define LL_CAN_MO_COUNT 256

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/* CAN_TypeDef top-level register offsets. */
_Static_assert(offsetof(CAN_TypeDef, CLC) == 0x000, "CAN CLC offset drift");
_Static_assert(offsetof(CAN_TypeDef, ID) == 0x008, "CAN ID offset drift");
_Static_assert(offsetof(CAN_TypeDef, FDR) == 0x00C, "CAN FDR offset drift");
_Static_assert(offsetof(CAN_TypeDef, PANCTR) == 0x1C4, "CAN PANCTR offset drift");
_Static_assert(offsetof(CAN_TypeDef, MCR) == 0x1C8, "CAN MCR offset drift");
_Static_assert(offsetof(CAN_TypeDef, Node) == 0x200, "CAN Node[] offset drift");
/* _CAN_Node_TypeDef member offsets (NCR=0, NSR=4, NIPR=8, NPCR=C, NBTR=10). */
_Static_assert(offsetof(_CAN_Node_TypeDef, NCR) == 0x00, "CAN Node NCR offset drift");
_Static_assert(offsetof(_CAN_Node_TypeDef, NSR) == 0x04, "CAN Node NSR offset drift");
_Static_assert(offsetof(_CAN_Node_TypeDef, NPCR) == 0x0C, "CAN Node NPCR offset drift");
_Static_assert(offsetof(_CAN_Node_TypeDef, NBTR) == 0x10, "CAN Node NBTR offset drift");
/* _CANMSG_Msg_TypeDef member offsets (MOFCR=0, MOAMR=C, MODATAL=10, MODATAH=14, MOAR=18, MOCTR/MOSTAT=1C). */
_Static_assert(offsetof(_CANMSG_Msg_TypeDef, MOFCR) == 0x00, "CANMSG Msg MOFCR offset drift");
_Static_assert(offsetof(_CANMSG_Msg_TypeDef, MOAMR) == 0x0C, "CANMSG Msg MOAMR offset drift");
_Static_assert(offsetof(_CANMSG_Msg_TypeDef, MODATAL) == 0x10, "CANMSG Msg MODATAL offset drift");
_Static_assert(offsetof(_CANMSG_Msg_TypeDef, MODATAH) == 0x14, "CANMSG Msg MODATAH offset drift");
_Static_assert(offsetof(_CANMSG_Msg_TypeDef, MOAR) == 0x18, "CANMSG Msg MOAR offset drift");
#endif

/**
 * @brief PANCTR command codes.
 *
 * Commands operate on the shared object pool: most consume an object
 * index in @c PANAR1 and/or a list index in @c PANAR2 and report errors
 * via bit 7 of @c PANAR2 (read back after @c BUSY clears).
 */
typedef enum {
    LL_CAN_PANCMD_NOP            = 0x00, /**< No operation. */
    LL_CAN_PANCMD_INIT_LIST      = 0x01, /**< Initialize all lists (requires INIT+CCE on every node). */
    LL_CAN_PANCMD_STATIC_ALLOC   = 0x02, /**< Move PANAR1 object to list PANAR2. */
    LL_CAN_PANCMD_DYNAMIC_ALLOC  = 0x03, /**< Pop one object from list 0 into list PANAR2; index returned in PANAR1. */
    LL_CAN_PANCMD_STATIC_INS_UP  = 0x04, /**< Move PANAR1 above object PANAR2. */
    LL_CAN_PANCMD_DYNAMIC_INS_UP = 0x05, /**< Pop from list 0, insert above object PANAR2. */
    LL_CAN_PANCMD_STATIC_INS_DN  = 0x06, /**< Move PANAR1 below object PANAR2. */
    LL_CAN_PANCMD_DYNAMIC_INS_DN = 0x07, /**< Pop from list 0, insert below object PANAR2. */
} ll_can_pancmd_t;

/**
 * @brief Node-level bit timing parameters (NBTR fields).
 *
 * The effective baud-rate is:
 *   `f_can / ((brp + 1) * (sync + tseg1 + 1 + tseg2 + 1))`
 * where `sync = 1` and an optional /8 prescaler is enabled via
 * @c div8. Hardware adds 1 to BRP, TSEG1 and TSEG2 internally — pass
 * the raw register values (e.g. tseg1=12 means 13).
 */
typedef struct {
    uint8_t brp;   /**< Baud-rate prescaler, NBTR.BRP[5:0] (raw). */
    uint8_t sjw;   /**< Sync-jump width, NBTR.SJW[1:0]. */
    uint8_t tseg1; /**< Time segment 1, NBTR.TSEG1[3:0] (raw). */
    uint8_t tseg2; /**< Time segment 2, NBTR.TSEG2[2:0] (raw). */
    bool div8;     /**< Apply the extra /8 prescaler (NBTR.DIV8). */
} ll_can_timing_t;

/**
 * @name Module-level controls
 * @{
 */

/**
 * @brief Bring the CAN module out of disabled mode (CLC.DISR=0).
 * @param can CAN controller instance.
 */
static inline void ll_can_module_enable(CAN_TypeDef *can)
{
    LL_ASSERT(can != NULL);
    /* CLC.DISR is bit 0; writing 0 enables. The "endinit" handshake is
     * documented as not required on this implementation. */
    can->CLC = 0U;
}

/**
 * @brief Drive the controller into disabled mode (CLC.DISR=1).
 * @param can CAN controller instance.
 */
static inline void ll_can_module_disable(CAN_TypeDef *can)
{
    LL_ASSERT(can != NULL);
    can->CLC = 0x1U;
}

/**
 * @brief Wait for the panel controller to become idle (PANCTR.BUSY=0).
 * @param can CAN controller instance.
 */
static inline void ll_can_panctr_wait(const CAN_TypeDef *can)
{
    LL_ASSERT(can != NULL);
    while ((can->PANCTR & (CAN_PANCTR_BUSY_Msk | CAN_PANCTR_RBUSY_Msk)) != 0U) {}
}

/**
 * @brief Issue a panel command, blocking until BUSY clears.
 *
 * Both arguments are written verbatim into PANAR1/PANAR2. After the
 * command completes, the host can read @c PANCTR to inspect the result
 * (e.g. PANAR2 bit 7 = error flag for the alloc/insert variants).
 *
 * @param can     CAN controller instance.
 * @param cmd     Command opcode (see @ref ll_can_pancmd_t).
 * @param panar1  Value loaded into PANAR1 (often a message-object index).
 * @param panar2  Value loaded into PANAR2 (often a list index).
 */
static inline void ll_can_panctr_command(CAN_TypeDef *can, ll_can_pancmd_t cmd, uint8_t panar1, uint8_t panar2)
{
    LL_ASSERT(can != NULL);
    ll_can_panctr_wait(can);
    can->PANCTR = (((uint32_t)cmd << CAN_PANCTR_PANCMD_Pos) & CAN_PANCTR_PANCMD_Msk) |
                  (((uint32_t)panar1 << CAN_PANCTR_PANAR1_Pos) & CAN_PANCTR_PANAR1_Msk) |
                  (((uint32_t)panar2 << CAN_PANCTR_PANAR2_Pos) & CAN_PANCTR_PANAR2_Msk);
}

/** @} */

/**
 * @name Per-node configuration
 * @{
 */

/**
 * @brief Enter configuration mode for a node (NCR.INIT=1, NCR.CCE=1).
 *
 * Bit timing and node port-control writes require @c CCE.
 *
 * @param node Node register block (e.g. @c &CAN->Node[0]).
 */
static inline void ll_can_node_config_begin(_CAN_Node_TypeDef *node)
{
    LL_ASSERT(node != NULL);
    node->NCR |= CAN_Node_NCR_INIT_Msk | CAN_Node_NCR_CCE_Msk;
}

/**
 * @brief Leave configuration mode and join the bus.
 * @param node Node register block.
 */
static inline void ll_can_node_config_end(_CAN_Node_TypeDef *node)
{
    LL_ASSERT(node != NULL);
    node->NCR &= ~(CAN_Node_NCR_INIT_Msk | CAN_Node_NCR_CCE_Msk);
}

/**
 * @brief Program the node's bit timing register.
 *
 * Must be called with the node in configuration mode (see
 * @ref ll_can_node_config_begin).
 *
 * @param node    Node register block.
 * @param timing  Pre-computed timing parameters.
 */
static inline void ll_can_set_bit_timing(_CAN_Node_TypeDef *node, const ll_can_timing_t *timing)
{
    LL_ASSERT(node != NULL);
    if (!timing) {
        return;
    }
    uint32_t nbtr = 0;
    nbtr |= ((uint32_t)timing->brp << CAN_Node_NBTR_BRP_Pos) & CAN_Node_NBTR_BRP_Msk;
    nbtr |= ((uint32_t)timing->sjw << CAN_Node_NBTR_SJW_Pos) & CAN_Node_NBTR_SJW_Msk;
    nbtr |= ((uint32_t)timing->tseg1 << CAN_Node_NBTR_TSEG1_Pos) & CAN_Node_NBTR_TSEG1_Msk;
    nbtr |= ((uint32_t)timing->tseg2 << CAN_Node_NBTR_TSEG2_Pos) & CAN_Node_NBTR_TSEG2_Msk;
    if (timing->div8) {
        nbtr |= CAN_Node_NBTR_DIV8_Msk;
    }
    node->NBTR = nbtr;
}

/**
 * @brief Toggle the node's internal loopback mode (NPCR.LBM).
 *
 * Useful for self-test: TX frames are routed straight to the RX path
 * without leaving the chip.
 *
 * @param node     Node register block.
 * @param loopback @c true to enable loopback.
 */
static inline void ll_can_set_loopback(_CAN_Node_TypeDef *node, bool loopback)
{
    LL_ASSERT(node != NULL);
    if (loopback) {
        node->NPCR |= CAN_Node_NPCR_LBM_Msk;
    } else {
        node->NPCR &= ~CAN_Node_NPCR_LBM_Msk;
    }
}

/**
 * @brief Read NSR.LEC (last error code), 3 bits.
 * @param node Node register block.
 * @return Raw 3-bit error code.
 */
static inline uint8_t ll_can_get_lec(const _CAN_Node_TypeDef *node)
{
    LL_ASSERT(node != NULL);
    return (uint8_t)((node->NSR & CAN_Node_NSR_LEC_Msk) >> CAN_Node_NSR_LEC_Pos);
}

/** @brief Check NSR.TXOK (successful transmission flag).
 *  @param node Node register block.
 *  @return @c true if at least one frame has been transmitted since the last clear. */
static inline bool ll_can_tx_ok(const _CAN_Node_TypeDef *node)
{
    LL_ASSERT(node != NULL);
    return (node->NSR & CAN_Node_NSR_TXOK_Msk) != 0U;
}

/** @brief Check NSR.RXOK (successful reception flag).
 *  @param node Node register block.
 *  @return @c true if at least one frame has been received since the last clear. */
static inline bool ll_can_rx_ok(const _CAN_Node_TypeDef *node)
{
    LL_ASSERT(node != NULL);
    return (node->NSR & CAN_Node_NSR_RXOK_Msk) != 0U;
}

/** @brief Clear NSR.TXOK / NSR.RXOK by writing the per-bit zeros mandated by the IP.
 *  @param node Node register block. */
static inline void ll_can_clear_xx_ok(_CAN_Node_TypeDef *node)
{
    LL_ASSERT(node != NULL);
    /* Per the manual, software clears these flags by writing zero into
     * the corresponding bit positions; the rest of NSR is preserved. */
    uint32_t nsr = node->NSR & ~(CAN_Node_NSR_TXOK_Msk | CAN_Node_NSR_RXOK_Msk);
    node->NSR    = nsr;
}

/** @} */

/**
 * @name Message-object setup
 * @{
 */

/**
 * @brief Set the arbitration ID (11- or 29-bit) and IDE flag of an MO.
 *
 * For an 11-bit ID, the value is left-aligned into MOAR.ID per the
 * TwinCAN convention (ID11 → MOAR.ID = id << 18); IDE is cleared. For a
 * 29-bit ID, the value is written into MOAR.ID directly and IDE is set.
 *
 * @param mo        Message-object register block.
 * @param id        11- or 29-bit identifier.
 * @param extended  @c true if @c id is a 29-bit identifier.
 */
static inline void ll_can_mo_set_id(_CANMSG_Msg_TypeDef *mo, uint32_t id, bool extended)
{
    LL_ASSERT(mo != NULL);
    uint32_t moar = mo->MOAR & ~(CANMSG_Msg_MOAR_ID_Msk | CANMSG_Msg_MOAR_IDE_Msk);
    if (extended) {
        moar |= ((id << CANMSG_Msg_MOAR_ID_Pos) & CANMSG_Msg_MOAR_ID_Msk) | CANMSG_Msg_MOAR_IDE_Msk;
    } else {
        moar |= (((id & 0x7FFU) << 18) & CANMSG_Msg_MOAR_ID_Msk);
    }
    mo->MOAR = moar;
}

/**
 * @brief Set the MO acceptance mask (MOAMR).
 *
 * Each bit of @c mask controls whether the corresponding bit in MOAR.ID
 * is compared during arbitration: 1 = "must match", 0 = "don't care".
 *
 * @param mo    Message-object register block.
 * @param mask  29-bit mask, same alignment as @ref ll_can_mo_set_id.
 * @param match_ide @c true to also require IDE to match.
 */
static inline void ll_can_mo_set_mask(_CANMSG_Msg_TypeDef *mo, uint32_t mask, bool match_ide)
{
    LL_ASSERT(mo != NULL);
    uint32_t v = mask & CANMSG_Msg_MOAR_ID_Msk;
    if (match_ide) {
        v |= CANMSG_Msg_MOAR_IDE_Msk;
    }
    mo->MOAMR = v;
}

/**
 * @brief Set the DLC of the MO (MOFCR.DLC).
 * @param mo  Message-object register block.
 * @param dlc Data length code (0..8).
 */
static inline void ll_can_mo_set_dlc(_CANMSG_Msg_TypeDef *mo, uint8_t dlc)
{
    LL_ASSERT(mo != NULL);
    LL_ASSERT(dlc <= 8U);
    uint32_t mofcr = mo->MOFCR & ~CANMSG_Msg_MOFCR_DLC_Msk;
    mofcr |= ((uint32_t)dlc << CANMSG_Msg_MOFCR_DLC_Pos) & CANMSG_Msg_MOFCR_DLC_Msk;
    mo->MOFCR = mofcr;
}

/**
 * @brief Copy up to 8 payload bytes into MODATAL/MODATAH.
 *
 * @c len is clamped to 8. Bytes are little-endian within the 32-bit
 * data registers (byte 0 lands in MODATAL[7:0]).
 *
 * @param mo    Message-object register block.
 * @param data  Source buffer.
 * @param len   Byte count.
 */
static inline void ll_can_mo_set_data(_CANMSG_Msg_TypeDef *mo, const uint8_t *data, size_t len)
{
    LL_ASSERT(mo != NULL);
    if (!data) {
        return;
    }
    if (len > 8U) {
        len = 8U;
    }
    uint32_t lo = 0;
    uint32_t hi = 0;
    for (size_t i = 0; i < len; ++i) {
        if (i < 4U) {
            lo |= ((uint32_t)data[i]) << (i * 8U);
        } else {
            hi |= ((uint32_t)data[i]) << ((i - 4U) * 8U);
        }
    }
    mo->MODATAL = lo;
    mo->MODATAH = hi;
}

/**
 * @brief Read up to 8 payload bytes from MODATAL/MODATAH.
 * @param mo     Message-object register block.
 * @param out    Destination buffer.
 * @param len    Byte count to copy (clamped to 8).
 */
static inline void ll_can_mo_get_data(const _CANMSG_Msg_TypeDef *mo, uint8_t *out, size_t len)
{
    LL_ASSERT(mo != NULL);
    if (!out) {
        return;
    }
    if (len > 8U) {
        len = 8U;
    }
    uint32_t lo = mo->MODATAL;
    uint32_t hi = mo->MODATAH;
    for (size_t i = 0; i < len; ++i) {
        uint32_t w = (i < 4U) ? lo : hi;
        out[i]     = (uint8_t)((w >> ((i & 3U) * 8U)) & 0xFFU);
    }
}

/**
 * @brief Mark the MO as a transmitter (sets DIR via MOCTR.SETDIR).
 * @param mo Message-object register block.
 */
static inline void ll_can_mo_set_dir_tx(_CANMSG_Msg_TypeDef *mo)
{
    LL_ASSERT(mo != NULL);
    mo->MOCTR = CANMSG_Msg_MOCTR_SETDIR_Msk;
}

/**
 * @brief Mark the MO as a receiver (clears DIR via MOCTR.RESDIR + sets RXEN).
 * @param mo Message-object register block.
 */
static inline void ll_can_mo_set_dir_rx(_CANMSG_Msg_TypeDef *mo)
{
    LL_ASSERT(mo != NULL);
    mo->MOCTR = CANMSG_Msg_MOCTR_RESDIR_Msk | CANMSG_Msg_MOCTR_SETRXEN_Msk;
}

/**
 * @brief Toggle MOSTAT.MSGVAL (object is part of the configured list).
 * @param mo    Message-object register block.
 * @param valid @c true to set MSGVAL, @c false to clear.
 */
static inline void ll_can_mo_set_valid(_CANMSG_Msg_TypeDef *mo, bool valid)
{
    LL_ASSERT(mo != NULL);
    mo->MOCTR = valid ? CANMSG_Msg_MOCTR_SETMSGVAL_Msk : CANMSG_Msg_MOCTR_RESMSGVAL_Msk;
}

/**
 * @brief Request transmission of the MO (sets TXRQ via MOCTR).
 * @param mo Message-object register block.
 */
static inline void ll_can_mo_request_tx(_CANMSG_Msg_TypeDef *mo)
{
    LL_ASSERT(mo != NULL);
    mo->MOCTR = CANMSG_Msg_MOCTR_SETTXRQ_Msk | CANMSG_Msg_MOCTR_SETNEWDAT_Msk;
}

/**
 * @brief Read the MOSTAT register.
 * @param mo Message-object register block.
 * @return Raw MOSTAT value (use @c CANMSG_Msg_MOSTAT_* bits to interpret).
 */
static inline uint32_t ll_can_mo_status(const _CANMSG_Msg_TypeDef *mo)
{
    LL_ASSERT(mo != NULL);
    return mo->MOSTAT;
}

/**
 * @brief Clear MOSTAT.NEWDAT (acknowledge a freshly-received frame).
 * @param mo Message-object register block.
 */
static inline void ll_can_mo_clear_newdat(_CANMSG_Msg_TypeDef *mo)
{
    LL_ASSERT(mo != NULL);
    mo->MOCTR = CANMSG_Msg_MOCTR_RESNEWDAT_Msk;
}

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */ /* end of ll_can group */
