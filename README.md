# Mizar64 PRNG (Minimalist Zap-Rand 64-bit)

Mizar64 is an ultra-fast, minimalist, and thread-safe pseudo-random number generator (PRNG) designed for high-performance applications, simulations, and games.

## Features
- **High Performance**: Extremely efficient, averaging **~4.07 cycles per number** on modern x86_64 architectures.
- **Statistical Robustness**: Successfully passes the **Dieharder** battery of tests with excellent p-values.
- **Minimal Footprint**: Only two 64-bit state variables and a few lines of code.
- **Thread-Safe**: Supports reentrant calls via a state structure (`mzr64_state_t`).
- **Deterministic**: Provides consistent results across different platforms using 64-bit constants.

## Algorithm Logic
Mizar64 uses a cross-coupled mixing technique. It evolves a linear counter (LCG) using the **Golden Ratio** and a **Weyl sequence**, then applies a non-linear mixing phase involving 32-bit XOR-rotations and a final multiplication to ensure maximum bit diffusion.

## Performance Benchmark

| Algorithm | Cycles/Number (lower is better) | Bit Size |
|-----------|---------------------------------|----------|
|**Mizar64**| **4.07**                        | 64-bit   |
| SplitMix64| ~4.2 - 5.0                      | 64-bit   |
| PCG64     | ~5.5 - 7.0                      | 64-bit   |

### Output Dieharder Test
Source: Mizar64 generator (seed = 1234567890)
```txt
#=============================================================================#
#            dieharder version 3.31.1 Copyright 2003 Robert G. Brown          #
#=============================================================================#
   rng_name    |rands/second|   Seed   |
stdin_input_raw|  1.37e+08  | 736478729|
#=============================================================================#
        test_name   |ntup| tsamples |psamples|  p-value |Assessment
#=============================================================================#
   diehard_birthdays|   0|       100|     100|0.77599620|  PASSED
      diehard_operm5|   0|   1000000|     100|0.86076439|  PASSED
  diehard_rank_32x32|   0|     40000|     100|0.24882925|  PASSED
    diehard_rank_6x8|   0|    100000|     100|0.35280338|  PASSED
   diehard_bitstream|   0|   2097152|     100|0.69730734|  PASSED
        diehard_opso|   0|   2097152|     100|0.94703966|  PASSED
        diehard_oqso|   0|   2097152|     100|0.93941364|  PASSED
         diehard_dna|   0|   2097152|     100|0.29016684|  PASSED
diehard_count_1s_str|   0|    256000|     100|0.93788305|  PASSED
diehard_count_1s_byt|   0|    256000|     100|0.45415451|  PASSED
 diehard_parking_lot|   0|     12000|     100|0.38128677|  PASSED
    diehard_2dsphere|   2|      8000|     100|0.59746073|  PASSED
    diehard_3dsphere|   3|      4000|     100|0.90817112|  PASSED
     diehard_squeeze|   0|    100000|     100|0.91577468|  PASSED
        diehard_sums|   0|       100|     100|0.41256406|  PASSED
        diehard_runs|   0|    100000|     100|0.59165351|  PASSED
        diehard_runs|   0|    100000|     100|0.26716530|  PASSED
       diehard_craps|   0|    200000|     100|0.95251055|  PASSED
       diehard_craps|   0|    200000|     100|0.79286955|  PASSED
 marsaglia_tsang_gcd|   0|  10000000|     100|0.62780276|  PASSED
 marsaglia_tsang_gcd|   0|  10000000|     100|0.64021544|  PASSED
         sts_monobit|   1|    100000|     100|0.57153148|  PASSED
            sts_runs|   2|    100000|     100|0.09406608|  PASSED
          sts_serial|   1|    100000|     100|0.63343079|  PASSED
          sts_serial|   2|    100000|     100|0.22394484|  PASSED
          sts_serial|   3|    100000|     100|0.95913300|  PASSED
          sts_serial|   3|    100000|     100|0.67866901|  PASSED
          sts_serial|   4|    100000|     100|0.68843945|  PASSED
          sts_serial|   4|    100000|     100|0.99864349|   WEAK
          sts_serial|   5|    100000|     100|0.78938844|  PASSED
          sts_serial|   5|    100000|     100|0.86788890|  PASSED
          sts_serial|   6|    100000|     100|0.40535163|  PASSED
          sts_serial|   6|    100000|     100|0.49284518|  PASSED
          sts_serial|   7|    100000|     100|0.89146930|  PASSED
          sts_serial|   7|    100000|     100|0.16318957|  PASSED
          sts_serial|   8|    100000|     100|0.91608284|  PASSED
          sts_serial|   8|    100000|     100|0.69564431|  PASSED
          sts_serial|   9|    100000|     100|0.96998367|  PASSED
          sts_serial|   9|    100000|     100|0.69124275|  PASSED
          sts_serial|  10|    100000|     100|0.09185727|  PASSED
          sts_serial|  10|    100000|     100|0.12015344|  PASSED
          sts_serial|  11|    100000|     100|0.47175541|  PASSED
          sts_serial|  11|    100000|     100|0.78437067|  PASSED
          sts_serial|  12|    100000|     100|0.59041652|  PASSED
          sts_serial|  12|    100000|     100|0.29972125|  PASSED
          sts_serial|  13|    100000|     100|0.79632614|  PASSED
          sts_serial|  13|    100000|     100|0.50051244|  PASSED
          sts_serial|  14|    100000|     100|0.79525080|  PASSED
          sts_serial|  14|    100000|     100|0.28941497|  PASSED
          sts_serial|  15|    100000|     100|0.47879128|  PASSED
          sts_serial|  15|    100000|     100|0.80620832|  PASSED
          sts_serial|  16|    100000|     100|0.35009675|  PASSED
          sts_serial|  16|    100000|     100|0.03144032|  PASSED
         rgb_bitdist|   1|    100000|     100|0.38568112|  PASSED
         rgb_bitdist|   2|    100000|     100|0.60240580|  PASSED
         rgb_bitdist|   3|    100000|     100|0.96102568|  PASSED
         rgb_bitdist|   4|    100000|     100|0.45412170|  PASSED
         rgb_bitdist|   5|    100000|     100|0.58151496|  PASSED
         rgb_bitdist|   6|    100000|     100|0.52535957|  PASSED
         rgb_bitdist|   7|    100000|     100|0.56410250|  PASSED
         rgb_bitdist|   8|    100000|     100|0.69491818|  PASSED
         rgb_bitdist|   9|    100000|     100|0.36025282|  PASSED
         rgb_bitdist|  10|    100000|     100|0.55591582|  PASSED
         rgb_bitdist|  11|    100000|     100|0.29855876|  PASSED
         rgb_bitdist|  12|    100000|     100|0.31411738|  PASSED
rgb_minimum_distance|   2|     10000|    1000|0.77894571|  PASSED
rgb_minimum_distance|   3|     10000|    1000|0.90626549|  PASSED
rgb_minimum_distance|   4|     10000|    1000|0.77754863|  PASSED
rgb_minimum_distance|   5|     10000|    1000|0.00106702|   WEAK
    rgb_permutations|   2|    100000|     100|0.45724024|  PASSED
    rgb_permutations|   3|    100000|     100|0.60609226|  PASSED
    rgb_permutations|   4|    100000|     100|0.26241513|  PASSED
    rgb_permutations|   5|    100000|     100|0.63457104|  PASSED
      rgb_lagged_sum|   0|   1000000|     100|0.15467732|  PASSED
      rgb_lagged_sum|   1|   1000000|     100|0.34480093|  PASSED
      rgb_lagged_sum|   2|   1000000|     100|0.75386701|  PASSED
      rgb_lagged_sum|   3|   1000000|     100|0.97975029|  PASSED
      rgb_lagged_sum|   4|   1000000|     100|0.78531513|  PASSED
      rgb_lagged_sum|   5|   1000000|     100|0.74404847|  PASSED
      rgb_lagged_sum|   6|   1000000|     100|0.65309862|  PASSED
      rgb_lagged_sum|   7|   1000000|     100|0.99206160|  PASSED
      rgb_lagged_sum|   8|   1000000|     100|0.58894639|  PASSED
      rgb_lagged_sum|   9|   1000000|     100|0.80269615|  PASSED
      rgb_lagged_sum|  10|   1000000|     100|0.21354971|  PASSED
      rgb_lagged_sum|  11|   1000000|     100|0.23090033|  PASSED
      rgb_lagged_sum|  12|   1000000|     100|0.75242357|  PASSED
      rgb_lagged_sum|  13|   1000000|     100|0.02691858|  PASSED
      rgb_lagged_sum|  14|   1000000|     100|0.22001944|  PASSED
      rgb_lagged_sum|  15|   1000000|     100|0.42120509|  PASSED
      rgb_lagged_sum|  16|   1000000|     100|0.67007363|  PASSED
      rgb_lagged_sum|  17|   1000000|     100|0.50422039|  PASSED
      rgb_lagged_sum|  18|   1000000|     100|0.97189187|  PASSED
      rgb_lagged_sum|  19|   1000000|     100|0.42099023|  PASSED
      rgb_lagged_sum|  20|   1000000|     100|0.28505179|  PASSED
      rgb_lagged_sum|  21|   1000000|     100|0.55206827|  PASSED
      rgb_lagged_sum|  22|   1000000|     100|0.38847931|  PASSED
      rgb_lagged_sum|  23|   1000000|     100|0.69704553|  PASSED
      rgb_lagged_sum|  24|   1000000|     100|0.73322796|  PASSED
      rgb_lagged_sum|  25|   1000000|     100|0.70276874|  PASSED
      rgb_lagged_sum|  26|   1000000|     100|0.05632380|  PASSED
      rgb_lagged_sum|  27|   1000000|     100|0.98281114|  PASSED
      rgb_lagged_sum|  28|   1000000|     100|0.88992313|  PASSED
      rgb_lagged_sum|  29|   1000000|     100|0.66156150|  PASSED
      rgb_lagged_sum|  30|   1000000|     100|0.75155407|  PASSED
      rgb_lagged_sum|  31|   1000000|     100|0.30566073|  PASSED
      rgb_lagged_sum|  32|   1000000|     100|0.57970305|  PASSED
     rgb_kstest_test|   0|     10000|    1000|0.47904992|  PASSED
     dab_bytedistrib|   0|  51200000|       1|0.09090356|  PASSED
             dab_dct| 256|     50000|       1|0.96152611|  PASSED
Preparing to run test 207.  ntuple = 0
        dab_filltree|  32|  15000000|       1|0.46703564|  PASSED
        dab_filltree|  32|  15000000|       1|0.37247385|  PASSED
Preparing to run test 208.  ntuple = 0
       dab_filltree2|   0|   5000000|       1|0.42649189|  PASSED
       dab_filltree2|   1|   5000000|       1|0.35786549|  PASSED
Preparing to run test 209.  ntuple = 0
        dab_monobit2|  12|  65000000|       1|0.78564286|  PASSED
```

## Output quality
The algorithm leverages the **Golden Ratio** (2^64/⌀) for maximum bit diffusion and a **Weyl sequence** to ensure a full period of at least 2^64  
Tests performed on x86_64 (i7-10th Gen) using GCC 11.4 (-O3) and OpenJDK 17.  

## Language	Cycles/Num	Speed (approx)
C	4.07	~850 Mib/s  
Java	~5.5 - 6.5	~600 Mib/s  

## Usage

### Simple Version (Single-thread)
```c
#include "mizar64.h"

mizar64_seed(12345);
uint64_t val = mizar64();
```

### Reentrant Version (Multi-thread)
```c
#include "mizar64.h"

mizar64_state_t state;
mizar64_seed_r(&state, 12345);
uint64_t val = mizar64_r(&state);
```

## Compilation
You can compile the library with any C99+ compiler:
```bash
gcc -O3 mizar64.c your_project.c -o your_project
```

## Versioning
Current Version: 1.0.0 (MZR64_VERSION 100)

## License
This project is released under the **Apache 2.0 License** - see the LICENSE file for details.
