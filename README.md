# Mizar64 PRNG
Mizar64 is an ultra-fast, minimalist, robust pseudo-random number generator (PRNG) designed for high-performance applications, simulations, and games.

## *Labor omnia vincit*
*This project is the most substantial result to date from an independent R&D effort I started in 2021 on hash functions and PRNGs—a journey that is still ongoing. Mizar64 relies on constants originally identified by Donald Knuth, whose pioneering work has inspired developers since the 1980s; special thanks to him for both these values and his broader impact on computing.  
I also gratefully acknowledge the AI tools that assisted with test planning, software configuration, testing tool development, and translation throughout this process*  

## Period
The internal state is 128 bits, but the algorithm's design limits the effective state space for cycling. Current estimates place the period around 2<sup>80</sup> – 2<sup>90</sup>.

## Features


## Algorithm Logic
Mizar64 uses a cross-coupled mixing technique. It evolves a linear counter (LCG), then applies a non-linear mixing phase involving 32-bit XOR-rotations and a final multiplication to ensure maximum bit diffusion.

## Performance Benchmark
Numerous tests were performed with four different tools: Dieharder, RNG_test (PractRand), SmallCrash (TestU01), and BigCrash (TestU01).
- Dieharder v. 3.31.1
- RNG_test (PractRand - SourceForge) v. 0.96 (compiler g++ (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0)

The tests are executed on
- Linux mzpc2023 6.6.87.2-microsoft-standard-WSL2 #1 SMP PREEMPT_DYNAMIC Thu Jun  5 18:30:46 UTC 2025 x86_64 x86_64 x86_64 GNU/Linux
  
The results of each test are available in the project's src/C/test directory.  
This table summarizes the results.

  n.| Tools              | Seed c      | Seed x      | File output          | Results  
 --:|:---                |:---         |:---         |:---                  |:---
   1|dieharder -a -g 200 |12345        |67890        |test_01_dieharder.txt |112 PASSED, 2 WEAK  
   2|dieharder -a -g 200 |0            |0            |test_02_dieharder.txt |114 PASSED  
   3|dieharder -a -g 200 |123456789    |987654321    |test_03_dieharder.txt |110 PASSED, 4 WEAK  
   4|dieharder -a -g 200 |max uint64_t |max uint64_t |test_04_dieharder.txt |112 PASSED, 2 WEAK
   5|RNG_test stdin64 -tlmin 4GB|123456789|987654321|test_05_rng_test.txt| length from 4GB to 32TB, no anomalies in 455 test

### Tests on the 4 lower bytes
These are the results of statistical analysis applied to the lowest 4 bytes

  n.| Tools              | Seed c      | Seed x      | File output          | Results  
 --:|:---                |:---         |:---         |:---                  |:---
  30|dieharder -a -g 200 |12345        |67890        |test_30_dieharder.txt |112 PASSED, 2 WEAK
  31|dieharder -a -g 200 |0            |0            |test_31_dieharder.txt |113 PASSED, 1 WEAK
  


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
