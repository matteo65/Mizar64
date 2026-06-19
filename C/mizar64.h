/*
 * mizar64.h 
 *
 * Mizar64 - Pseudo Random Number Generator 64 bit output, 64 bit state
 * 
 * Copyright(C) 2026 Matteo Zapparoli - zapparoli.matteo@gmail.com
 * 
 * SPDX-License-Identifier: Apache-2.0
 * 
 * Minimalist implementation
 *
 */

#ifndef MIZAR64_H
#define MIZAR64_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint64_t mizar64(uint64_t *state);

#ifdef __cplusplus
}
#endif

#endif /* MIZAR64_H */
