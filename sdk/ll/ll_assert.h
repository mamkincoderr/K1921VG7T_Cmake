/**
 * @file ll_assert.h
 * @brief Parameter-assertion macro for LL helpers.
 *
 * Gated by CONFIG_LL_ASSERT. When enabled, a failing assertion issues an
 * `ebreak` (so a connected debugger halts at the call site) followed by an
 * infinite loop (so the core traps even with no debugger attached). When
 * disabled, the macro evaluates to (void)0 — zero overhead.
 *
 * Use for caller mistakes that are static or bounds-checkable. Do NOT use
 * for hardware state polling, for things the type system already enforces,
 * or in hot paths. The argument MUST be pure (no side effects) — debug and
 * release builds will diverge otherwise.
 */

#pragma once

/* Индексатор MRS не знает ключевое слово C11 _Static_assert и подчёркивает его.
 * __CDT_PARSER__ есть только у редактора. Компилятор этот макрос не видит. */
#ifdef __CDT_PARSER__
#define _Static_assert(expr, msg)
#endif

#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif

static inline void ll_assert_trap(bool condition)
{
    if (!condition) {
        __asm__ volatile("ebreak");
        for (;;) {}
    }
}

#if defined(CONFIG_LL_ASSERT)
#define LL_ASSERT(condition) ll_assert_trap((condition))
#else
#define LL_ASSERT(condition) ((void)(condition))
#endif

#ifdef __cplusplus
}
#endif
