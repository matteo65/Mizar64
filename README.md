# MZR64 PRNG (Minimalist Zap-Rand 64-bit)

MZR64 is an ultra-fast, minimalist, and thread-safe pseudo-random number generator (PRNG) designed for high-performance applications, simulations, and games.

## Features
- **High Performance**: Extremely efficient, averaging **~4.07 cycles per number** on modern x86_64 architectures.
- **Statistical Robustness**: Successfully passes the **Dieharder** battery of tests with excellent p-values.
- **Minimal Footprint**: Only two 64-bit state variables and a few lines of code.
- **Thread-Safe**: Supports reentrant calls via a state structure (`mzr64_state_t`).
- **Deterministic**: Provides consistent results across different platforms using 64-bit constants.

## Algorithm Logic
MZR64 uses a cross-coupled mixing technique. It evolves a linear counter (LCG) using the **Golden Ratio** and a **Weyl sequence**, then applies a non-linear mixing phase involving 32-bit XOR-rotations and a final multiplication to ensure maximum bit diffusion.

## Performance Benchmark

| Algorithm | Cycles/Number (lower is better) | Bit Size |
|-----------|---------------------------------|----------|
| **MZR64** | **4.07**                        | 64-bit   |
| SplitMix64| ~4.2 - 5.0                      | 64-bit   |
| PCG64     | ~5.5 - 7.0                      | 64-bit   |

## Usage

### Simple Version (Single-thread)
```c
#include "mzr64.h"

mzr64_seed(12345);
uint64_t val = mzr64();

### Reentrant Version (Multi-thread)
```c
#include "mzr64.h"

mzr64_state_t state;
mzr64_seed_r(&state, 12345);
uint64_t val = mzr64_r(&state);

