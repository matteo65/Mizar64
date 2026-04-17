/**
 * mizar64.c
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
 
#include "mizar64.h"

uint64_t mizar64(mizar64_state_t *state) 
{
    // 1. Linear step: update counter
    state->c *= 0x9e3779b97f4a7c15ULL;

    // 2. Mixing step: cross-coupled XOR-rotation and multiplication
    return state->x = 0x9e3779b97f4a7c15ULL * ((state->c << 32) ^ (state->c >> 32) ^
                                               (state->x << 32) ^ (state->x >> 32));
}
