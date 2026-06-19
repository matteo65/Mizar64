/*
 * mizar64.c 
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

#include "mizar64.h"

uint64_t mizar64(uint64_t *state)
{
	*state = 0x9e3779b97f4a7c15ull * ((*state << 32) | (*state >> 32));
	return 0x9e3779b97f4a7c15ull * (*state ^ (*state >> 17));
}
