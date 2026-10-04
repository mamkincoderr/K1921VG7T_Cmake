/**
 * @file ll_i2c.h
 * @brief Low-level I2C driver for the K1921VG family.
 *
 * The I2C IP block exposes a status-code driven state machine inherited
 * from the Philips/NXP-style controllers: an action (START, byte write,
 * byte read) is initiated by the master, the controller drives SCL/SDA,
 * and after each phase it latches a 6-bit code into @c ST.MODE plus an
 * @c INT flag that holds @c SCL low until the host services it.
 *
 * Register layout is identical across vg015 / vg1t / vg3t / vg5t / vg7t
 * for the common fields (SDA, ST, CST, CTL0..CTL4, ADDR, TOPR). The
 * following extras are SoC-specific and gated behind capability flags:
 *
 * | Capability                | Soc(s) with the feature              |
 * |---------------------------|--------------------------------------|
 * | @c LL_I2C_HAS_DMA_CTL     | K1921VG1T (CTL5/CTL6 DMA-arm bits)   |
 * | @c LL_I2C_HAS_EXT_ADDR    | every SoC except VG015 (EADDR[8])    |
 * | @c LL_I2C_HAS_UNADDR      | every SoC except VG015 (CTL0.UNADDR) |
 *
 * Typical polling-mode master use:
 * @code
 *     ll_rcu_peripheral_init(LL_RCU_I2C0);
 *     ll_i2c_set_scl_freq(I2C0, pclk_hz, 100000U);
 *     ll_i2c_enable(I2C0);
 *
 *     ll_i2c_start(I2C0);
 *     while (!ll_i2c_int_pending(I2C0)) { }
 *     // 0x50 is a 7-bit address, R/W# = 0 (write).
 *     ll_i2c_write_byte(I2C0, (uint8_t)(0x50U << 1));
 *     ll_i2c_clear_int(I2C0);
 *     while (!ll_i2c_int_pending(I2C0)) { }
 *     ll_i2c_status_t st = ll_i2c_status(I2C0);
 *     ll_i2c_stop(I2C0);
 * @endcode
 *
 * @defgroup ll_i2c LL I2C
 * @{
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <ll_assert.h>
#include <soc.h>

#if defined(K1921VG015)
/** @brief 1 if the SoC implements the @c CTL5/@c CTL6 DMA-arm registers. */
#define LL_I2C_HAS_DMA_CTL 0
/** @brief 1 if the SoC implements the @c EADDR[8] extra slave-address registers. */
#define LL_I2C_HAS_EXT_ADDR 0
/** @brief 1 if the SoC implements the @c CTL0.UNADDR unaddressed-slave bit. */
#define LL_I2C_HAS_UNADDR 0
#elif defined(K1921VG1T)
#define LL_I2C_HAS_DMA_CTL  1
#define LL_I2C_HAS_EXT_ADDR 1
#define LL_I2C_HAS_UNADDR   1
#elif defined(K1921VG3T) || defined(K1921VG5T) || defined(K1921VG7T)
#define LL_I2C_HAS_DMA_CTL  0
#define LL_I2C_HAS_EXT_ADDR 1
#define LL_I2C_HAS_UNADDR   1
#else
#error "ll_i2c.h: unsupported SoC"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DOXYGEN_SHOULD_SKIP_THIS
_Static_assert(offsetof(I2C_TypeDef, SDA) == 0x00, "I2C SDA offset drift");
_Static_assert(offsetof(I2C_TypeDef, ST) == 0x04, "I2C ST offset drift");
_Static_assert(offsetof(I2C_TypeDef, CST) == 0x08, "I2C CST offset drift");
_Static_assert(offsetof(I2C_TypeDef, CTL0) == 0x0C, "I2C CTL0 offset drift");
_Static_assert(offsetof(I2C_TypeDef, ADDR) == 0x10, "I2C ADDR offset drift");
_Static_assert(offsetof(I2C_TypeDef, CTL1) == 0x14, "I2C CTL1 offset drift");
_Static_assert(offsetof(I2C_TypeDef, TOPR) == 0x18, "I2C TOPR offset drift");
_Static_assert(offsetof(I2C_TypeDef, CTL2) == 0x1C, "I2C CTL2 offset drift");
_Static_assert(offsetof(I2C_TypeDef, CTL3) == 0x20, "I2C CTL3 offset drift");
_Static_assert(offsetof(I2C_TypeDef, CTL4) == 0x24, "I2C CTL4 offset drift");
#if LL_I2C_HAS_EXT_ADDR
_Static_assert(offsetof(I2C_TypeDef, EADDR) == 0x28, "I2C EADDR offset drift");
#endif
#endif

/**
 * @brief I2C state codes as latched in @c ST.MODE.
 *
 * Taken from the K1921VG1T manual, table 34.2 (FS) and 34.3 (HS). Codes
 * 0x0D..0x0F and 0x2C..0x2F / 0x38..0x3F are reserved.
 */
typedef enum {
    /* General */
    LL_I2C_ST_IDLE   = 0x00, /**< Bus idle, no valid status. */
    LL_I2C_ST_STDONE = 0x01, /**< START condition transmitted. */
    LL_I2C_ST_RSDONE = 0x02, /**< Repeated START transmitted. */
    LL_I2C_ST_IDLARL = 0x03, /**< Arbitration lost, fell back to unaddressed slave. */

    /* FS master transmitter */
    LL_I2C_ST_MTADPA = 0x04, /**< Slave address sent, ACK received. */
    LL_I2C_ST_MTADNA = 0x05, /**< Slave address sent, NACK received. */
    LL_I2C_ST_MTDAPA = 0x06, /**< Data byte sent, ACK received. */
    LL_I2C_ST_MTDANA = 0x07, /**< Data byte sent, NACK received. */

    /* FS master receiver */
    LL_I2C_ST_MRADPA = 0x08, /**< Slave address sent (read), ACK received. */
    LL_I2C_ST_MRADNA = 0x09, /**< Slave address sent (read), NACK received. */
    LL_I2C_ST_MRDAPA = 0x0A, /**< Data byte received, ACK returned. */
    LL_I2C_ST_MRDANA = 0x0B, /**< Data byte received, NACK returned. */

    LL_I2C_ST_MTMCER = 0x0C, /**< Master code sent, bus error detected. */

    /* FS slave receiver */
    LL_I2C_ST_SRADPA = 0x10, /**< Address received, ACK returned. */
    LL_I2C_ST_SRAAPA = 0x11, /**< Address received after arbitration loss. */
    LL_I2C_ST_SRDAPA = 0x12, /**< Data byte received, ACK returned. */
    LL_I2C_ST_SRDANA = 0x13, /**< Data byte received, NACK returned. */

    /* FS slave transmitter */
    LL_I2C_ST_STADPA = 0x14, /**< Address received (slave-tx), ACK returned. */
    LL_I2C_ST_STAAPA = 0x15, /**< Address received after arbitration loss. */
    LL_I2C_ST_STDAPA = 0x16, /**< Data byte sent, ACK received. */
    LL_I2C_ST_STDANA = 0x17, /**< Data byte sent, NACK received. */

    /* FS slave SMBus alert response */
    LL_I2C_ST_SATADP = 0x18, /**< Alert response address received. */
    LL_I2C_ST_SATAAP = 0x19, /**< Alert response address after arbitration loss. */
    LL_I2C_ST_SATDAP = 0x1A, /**< Alert response data sent, ACK received. */
    LL_I2C_ST_SATDAN = 0x1B, /**< Alert response data sent, NACK received. */

    LL_I2C_ST_SSTOP  = 0x1C, /**< STOP condition detected in slave mode. */
    LL_I2C_ST_SGADPA = 0x1D, /**< General-call address received. */
    LL_I2C_ST_SDAAPA = 0x1E, /**< General-call address after arbitration loss. */
    LL_I2C_ST_BERROR = 0x1F, /**< Bus error (illegal START/STOP). */

    /* HS master transmitter / receiver */
    LL_I2C_ST_HMTMCOK = 0x21, /**< Master code accepted, switched to HS mode. */
    LL_I2C_ST_HRSDONE = 0x22, /**< HS repeated START transmitted. */
    LL_I2C_ST_HIDLARL = 0x23, /**< Arbitration lost in HS mode. */
    LL_I2C_ST_HMTADPA = 0x24, /**< HS slave address sent, ACK received. */
    LL_I2C_ST_HMTADNA = 0x25, /**< HS slave address sent, NACK received. */
    LL_I2C_ST_HMTDAPA = 0x26, /**< HS data byte sent, ACK received. */
    LL_I2C_ST_HMTDANA = 0x27, /**< HS data byte sent, NACK received. */
    LL_I2C_ST_HMRADPA = 0x28, /**< HS slave address sent (read), ACK received. */
    LL_I2C_ST_HMRADNA = 0x29, /**< HS slave address sent (read), NACK received. */
    LL_I2C_ST_HMRDAPA = 0x2A, /**< HS data byte received, ACK returned. */
    LL_I2C_ST_HMRDANA = 0x2B, /**< HS data byte received, NACK returned. */

    /* HS slave */
    LL_I2C_ST_HSRADPA = 0x30, /**< HS slave address received. */
    LL_I2C_ST_HSRDAPA = 0x32, /**< HS slave data byte received, ACK returned. */
    LL_I2C_ST_HSRDANA = 0x33, /**< HS slave data byte received, NACK returned. */
    LL_I2C_ST_HSTADPA = 0x34, /**< HS slave address received (slave-tx). */
    LL_I2C_ST_HSTDAPA = 0x36, /**< HS slave data byte sent, ACK received. */
    LL_I2C_ST_HSTDANA = 0x37, /**< HS slave data byte sent, NACK received. */
} ll_i2c_status_t;

/** @brief Lower bound the SCLFRQ divider is clamped to (hardware minimum). */
#define LL_I2C_SCLFRQ_MIN 4U
/** @brief Upper bound for the 15-bit SCLFRQ divider. */
#define LL_I2C_SCLFRQ_MAX 0x7FFFU

/**
 * @name Enable / clocking
 * @{
 */

/**
 * @brief Power the controller on.
 *
 * Sets @c CTL1.ENABLE. The host must also program SCLFRQ before any
 * master transfer; @ref ll_i2c_set_scl_freq is the recommended helper.
 *
 * @param i2c  I2C instance.
 */
static inline void ll_i2c_enable(I2C_TypeDef *i2c)
{
    LL_ASSERT(i2c != NULL);
    i2c->CTL1 |= I2C_CTL1_ENABLE_Msk;
}

/**
 * @brief Power the controller off (resets CTL0/ST/CST per the manual).
 * @param i2c  I2C instance.
 */
static inline void ll_i2c_disable(I2C_TypeDef *i2c)
{
    LL_ASSERT(i2c != NULL);
    i2c->CTL1 &= ~I2C_CTL1_ENABLE_Msk;
}

/**
 * @brief Program SCL frequency from a target rate in Hz.
 *
 * Computes the 15-bit SCLFRQ divider as `pclk_hz / (4 * scl_hz)` and
 * splits it across @c CTL1.SCLFRQ (low 7 bits, positioned at @c CTL1[7:1])
 * and @c CTL3.SCLFRQ (high 8 bits). The result is clamped to the
 * hardware-permitted range [@ref LL_I2C_SCLFRQ_MIN, @ref LL_I2C_SCLFRQ_MAX].
 *
 * Both half-periods of SCL are equal, so the actual SCL frequency is
 * `pclk_hz / (4 * divider)` and the achievable resolution gets coarser
 * at higher target rates.
 *
 * @param i2c     I2C instance.
 * @param pclk_hz Bus clock feeding the I2C block, in Hz.
 * @param scl_hz  Desired SCL frequency, in Hz.
 * @return Actual SCL frequency that the hardware will produce, in Hz.
 */
static inline uint32_t ll_i2c_set_scl_freq(I2C_TypeDef *i2c, uint32_t pclk_hz, uint32_t scl_hz)
{
    LL_ASSERT(i2c != NULL);
    LL_ASSERT(pclk_hz != 0U);
    if (scl_hz == 0U) {
        scl_hz = 1U;
    }
    uint32_t div = pclk_hz / (4U * scl_hz);
    if (div < LL_I2C_SCLFRQ_MIN) {
        div = LL_I2C_SCLFRQ_MIN;
    }
    if (div > LL_I2C_SCLFRQ_MAX) {
        div = LL_I2C_SCLFRQ_MAX;
    }

    uint32_t ctl1 = i2c->CTL1 & ~I2C_CTL1_SCLFRQ_Msk;
    ctl1 |= ((div & 0x7FU) << I2C_CTL1_SCLFRQ_Pos) & I2C_CTL1_SCLFRQ_Msk;
    i2c->CTL1 = ctl1;

    uint32_t ctl3 = i2c->CTL3 & ~I2C_CTL3_SCLFRQ_Msk;
    ctl3 |= (((div >> 7) & 0xFFU) << I2C_CTL3_SCLFRQ_Pos) & I2C_CTL3_SCLFRQ_Msk;
    i2c->CTL3 = ctl3;

    return pclk_hz / (4U * div);
}

/** @} */

/**
 * @name Own address (slave mode)
 * @{
 */

/**
 * @brief Set the 7-bit own address used in slave mode.
 *
 * Writes both the address and the @c SAEN enable bit so any later read
 * of @c ADDR reflects the same state.
 *
 * @param i2c   I2C instance.
 * @param addr  7-bit slave address (lower 7 bits used).
 * @param enable Set to @c true to allow the controller to respond.
 */
static inline void ll_i2c_set_own_address(I2C_TypeDef *i2c, uint8_t addr, bool enable)
{
    LL_ASSERT(i2c != NULL);
    LL_ASSERT(addr <= 0x7FU);
    uint32_t val = ((uint32_t)addr << I2C_ADDR_ADDR_Pos) & I2C_ADDR_ADDR_Msk;
    if (enable) {
        val |= I2C_ADDR_SAEN_Msk;
    }
    i2c->ADDR = val;
}

#if LL_I2C_HAS_UNADDR
/**
 * @brief Toggle "unaddressed slave" mode (CTL0.UNADDR).
 *
 * Only present on K1921VG1T / VG3T / VG5T / VG7T (gated by
 * @c LL_I2C_HAS_UNADDR). When set, the slave ACKs every transaction
 * regardless of address.
 *
 * @param i2c       I2C instance.
 * @param unaddressed Set to @c true to ACK every address.
 */
static inline void ll_i2c_set_unaddressed(I2C_TypeDef *i2c, bool unaddressed)
{
    LL_ASSERT(i2c != NULL);
    if (unaddressed) {
        i2c->CTL0 |= I2C_CTL0_UNADDR_Msk;
    } else {
        i2c->CTL0 &= ~I2C_CTL0_UNADDR_Msk;
    }
}
#endif

/** @} */

/**
 * @name Control register helpers (CTL0)
 * @{
 */

/**
 * @brief Request a START condition.
 * @param i2c I2C instance.
 */
static inline void ll_i2c_start(I2C_TypeDef *i2c)
{
    LL_ASSERT(i2c != NULL);
    i2c->CTL0 |= I2C_CTL0_START_Msk;
}

/**
 * @brief Request a STOP condition.
 * @param i2c I2C instance.
 */
static inline void ll_i2c_stop(I2C_TypeDef *i2c)
{
    LL_ASSERT(i2c != NULL);
    i2c->CTL0 |= I2C_CTL0_STOP_Msk;
}

/**
 * @brief Enable the I2C interrupt line (CTL0.INTEN).
 * @param i2c I2C instance.
 */
static inline void ll_i2c_enable_irq(I2C_TypeDef *i2c)
{
    LL_ASSERT(i2c != NULL);
    i2c->CTL0 |= I2C_CTL0_INTEN_Msk;
}

/**
 * @brief Disable the I2C interrupt line.
 * @param i2c I2C instance.
 */
static inline void ll_i2c_disable_irq(I2C_TypeDef *i2c)
{
    LL_ASSERT(i2c != NULL);
    i2c->CTL0 &= ~I2C_CTL0_INTEN_Msk;
}

/**
 * @brief Arm the receiver to ACK the next incoming byte.
 *
 * Sets @c CTL0.ACK. Per the manual, this controls the bit driven on the
 * 9th SCL cycle of the next byte received in master/slave receiver mode.
 *
 * @param i2c  I2C instance.
 * @param ack  @c true → ACK; @c false → NACK.
 */
static inline void ll_i2c_set_ack(I2C_TypeDef *i2c, bool ack)
{
    LL_ASSERT(i2c != NULL);
    if (ack) {
        i2c->CTL0 |= I2C_CTL0_ACK_Msk;
    } else {
        i2c->CTL0 &= ~I2C_CTL0_ACK_Msk;
    }
}

/**
 * @brief Clear the @c INT flag and release SCL.
 *
 * Writes @c CTL0.CLRST. After every state transition the controller
 * holds SCL low until the host calls this — typically right after
 * reading the new status code and pushing the next byte into @c SDA.
 *
 * @param i2c  I2C instance.
 */
static inline void ll_i2c_clear_int(I2C_TypeDef *i2c)
{
    LL_ASSERT(i2c != NULL);
    i2c->CTL0 |= I2C_CTL0_CLRST_Msk;
}

/** @} */

/**
 * @name Status
 * @{
 */

/**
 * @brief Check whether the controller has latched a new status code.
 * @param i2c I2C instance.
 * @return @c true if @c ST.INT is set.
 */
static inline bool ll_i2c_int_pending(const I2C_TypeDef *i2c)
{
    LL_ASSERT(i2c != NULL);
    return (i2c->ST & I2C_ST_INT_Msk) != 0U;
}

/**
 * @brief Read the 6-bit @c ST.MODE field cast to @ref ll_i2c_status_t.
 * @param i2c I2C instance.
 * @return Current status code.
 */
static inline ll_i2c_status_t ll_i2c_status(const I2C_TypeDef *i2c)
{
    LL_ASSERT(i2c != NULL);
    return (ll_i2c_status_t)((i2c->ST & I2C_ST_MODE_Msk) >> I2C_ST_MODE_Pos);
}

/**
 * @brief Read the bus-busy flag (CST.BB).
 * @param i2c I2C instance.
 * @return @c true if the bus is currently in use.
 */
static inline bool ll_i2c_bus_busy(const I2C_TypeDef *i2c)
{
    LL_ASSERT(i2c != NULL);
    return (i2c->CST & I2C_CST_BB_Msk) != 0U;
}

/** @} */

/**
 * @name Data
 * @{
 */

/**
 * @brief Push a byte into @c SDA for the next phase.
 *
 * For master transmitter mode the byte is the data payload; for the
 * very first byte after @ref LL_I2C_ST_STDONE it must encode the 7-bit
 * slave address shifted left by 1 with the R/W# bit in position 0.
 *
 * @param i2c  I2C instance.
 * @param b    Byte to load into @c SDA.
 */
static inline void ll_i2c_write_byte(I2C_TypeDef *i2c, uint8_t b)
{
    LL_ASSERT(i2c != NULL);
    i2c->SDA = b;
}

/**
 * @brief Read the byte currently latched in @c SDA.
 * @param i2c I2C instance.
 * @return Byte from the @c SDA data register.
 */
static inline uint8_t ll_i2c_read_byte(const I2C_TypeDef *i2c)
{
    LL_ASSERT(i2c != NULL);
    return (uint8_t)(i2c->SDA & I2C_SDA_DATA_Msk);
}

/** @} */

#ifdef __cplusplus
}
#endif

/** @} */ /* end of ll_i2c group */
