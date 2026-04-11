# Mizar64 PRNG
Mizar64 is an ultra-fast, minimalist, robust pseudo-random number generator (PRNG) designed for high-performance applications, simulations, and games. 

## Period
The internal state is 128 bits, but the algorithm's design limits the effective state space for cycling. Current estimates place the period around 2<sup>94</sup>.

## Features

## Algorithm Logic
Mizar64 uses a cross-coupled mixing technique. It evolves a linear counter (LCG), then applies a non-linear mixing phase involving 32-bit XOR-rotations and a final multiplication to ensure maximum bit diffusion.

## Performance Benchmark
Numerous tests were performed with different tools:
- **Dieharder v. 3.31.1**
- **RNG_test v. 0.96** (PractRand - SourceForge) (compiler: g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0)
- **SmokeRand v. 0.46** gcc-linux64

The tests are executed on
- Linux mzpc2023 6.6.87.2-microsoft-standard-WSL2 #1 SMP PREEMPT_DYNAMIC Thu Jun  5 18:30:46 UTC 2025 x86_64 x86_64 x86_64 GNU/Linux
  
The results of each test are available in the project's src/C/test directory.  
This table summarizes the results.

  n.| Tool               | Seed c      | Seed x      | Report          | Result  
 --:|:---                |:---         |:---         |:---                  |:---
   1|dieharder -a -g 200 |12345        |67890        |test_01_dieharder.txt |112 PASSED, 2 WEAK  
   2|dieharder -a -g 200 |0            |0            |test_02_dieharder.txt |114 PASSED  
   3|dieharder -a -g 200 |123456789    |987654321    |test_03_dieharder.txt |110 PASSED, 4 WEAK  
   4|dieharder -a -g 200 |max uint64_t |max uint64_t |test_04_dieharder.txt |112 PASSED, 2 WEAK
   5|RNG_test stdin64 -tlmin 4GB|123456789|987654321 |test_05_rng_test.txt| length from 4GB to 32TB, no anomalies in 455 test
   6|smokerand full stdin64|0          |0            |test_06.smokerand.txt|Passed: 50/50, Suspicious: 0, Failed: 0
   7|smokerand full stdin64|123        |456          |test_07.smokerand.txt|Passed: 49/50, Suspicious: 1, Failed: 0
   7|smokerand full stdin64|123456789  |987654321    |test_08.smokerand.txt|Passed: 49/50, Suspicious: 1, Failed: 0
   

### Tests on the 4 lower bytes
These are the results of statistical analysis applied to the lowest 4 bytes

  n.| Tool               | Seed c      | Seed x      | Report          | Result  
 --:|:---                |:---         |:---         |:---                  |:---
  30|dieharder -a -g 200 |12345        |67890        |test_30_dieharder.txt |112 PASSED, 2 WEAK
  31|dieharder -a -g 200 |0            |0            |test_31_dieharder.txt |113 PASSED, 1 WEAK
  32|dieharder -a -g 200 |123456789    |987654321    |test_32_dieharder.txt |112 PASSED, 2 WEAK
  33|dieharder -a -g 200 |max uint64_t |max uint64_t |test_33_dieharder.txt |114 PASSED, 1 WEAK
  
### Tests on the 4 higher bytes
These are the results of statistical analysis applied to the highest 4 bytes

  n.| Tool               | Seed c      | Seed x      | Report          | Result  
 --:|:---                |:---         |:---         |:---                  |:---
  60|dieharder -a -g 200 |12345        |67890        |test_60_dieharder.txt |110 PASSED, 4 WEAK
  61|dieharder -a -g 200 |0            |0            |test_61_dieharder.txt |109 PASSED, 5 WEAK
  62|dieharder -a -g 200 |123456789    |987654321    |test_62_dieharder.txt |114 PASSED
  63|dieharder -a -g 200 |max uint64_t |max uint64_t |test_63_dieharder.txt |111 PASSED, 3 WEAK


## Language	Cycles/Num	Speed (approx)

## Usage

## Compilation
You can compile the library with any C99+ compiler:
```bash
gcc -O3 mizar64.c your_project.c -o your_project
```

## Versioning
Current Version: 1.0.0 (MIZAR64_VERSION 100)

## License
This project is released under the **Apache 2.0 License** - see the LICENSE file for details.
