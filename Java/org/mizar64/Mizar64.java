package org.mizar64;

/**
 * Mizar64 - Pseudo Random Number Generator 64 bit output, 64 bit state
 * 
 * Copyright(C) 2026 Matteo Zapparoli - zapparoli.matteo@gmail.com
 * 
 * SPDX-License-Identifier: Apache-2.0
 * 
 * Minimalist implementation
 * 
 */

public class Mizar64 {

	private long state;
	
	public Mizar64(long seed) {
		if(seed == 0) throw new IllegalArgumentException("seed == 0");
		this.state = seed;
	}
	
	public long next() {
		state = 0x9e3779b97f4a7c15L * ((state << 32) | (state >>> 32));
		return 0x9e3779b97f4a7c15L * (state ^ (state >>> 17));
	}
	
}
