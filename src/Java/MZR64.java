package org.mzr;

/**
 * MZR64
 * 
 * Ultra-fast, minimalist, robust pseudo-random number generator (PRNG)
 * 
 * Author: Matteo Zapparoli
 * Date: 2026-04
 * Version 1.0
 *
 * SPDX-FileCopyrightText: 2026 Matteo Zapparoli
 * SPDX-License-Identifier: Apache-2.0
 * See LICENSE file in project root.
 * 
 */

public class MZR64 {

    private static final long MZR_GOLDEN = 0x9E3779B97F4A7C15L;
    private static final long MZR_WEYL   = 0x14057B7EF767814FL;

    private long s; // Internal counter
    private long v; // Mixing state

    public MZR64(long seed) {
        seed(seed);
    }

    public void seed(long seed) {
        this.s = seed;
        this.v = ~seed;
    }

    public long nextLong() {
        // Linear step
        s = s * MZR_GOLDEN + MZR_WEYL;
        
        // Mixing step: Java's >>> is the logical (unsigned) right shift
        v = MZR_GOLDEN * ((s << 32) ^ (s >>> 32) ^ (v << 32) ^ (v >>> 32));
        return v;
    }
}
