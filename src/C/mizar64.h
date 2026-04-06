/**
 * mizar64.h
 * 
 * Mizar64: ultra-fast, minimalist, robust pseudo-random number generator (PRNG)
 * 
 * Author: Matteo Zapparoli
 * Date: 2026-04-01
 * Version 1.0
 *
 * SPDX-FileCopyrightText: 2026 Matteo Zapparoli
 * SPDX-License-Identifier: Apache-2.0
 * See LICENSE file in project root.
 * 
 */
 
#ifndef MIZAR64_H
#define MIZAR64_H

#include <stdint.h>

#define MIZAR64_VERSION 100 // Version 1.0.0

#define MIZAR64_DEFAULT_SEED_C 0x0123456789abcdefULL
#define MIZAR64_DEFAULT_SEED_X 0xfedcba9876543201ULL

#ifdef __cplusplus
extern "C" {
#endif

/* mizar64 State structure */
typedef struct {
    uint64_t c; // Internal counter
    uint64_t x; // Mixing state
} mizar64_state_t;

uint64_t mizar64(mizar64_state_t *state);

#ifdef __cplusplus
}
#endif

#endif /* MIZAR64_H */
