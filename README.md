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
The results of each test are available in the project's src/C/test directory.  
This table summarizes the results.

 # | Tools              | Seed c      | Seed x      | File output          | Results
 --|--------------------|-------------|-------------|----------------------|------------------
  1|dieharder -a -g 200 |defalut      |default      |test_01_dieharder.txt |110 PASSED, 4 WEAK
  2|dieharder -a -g 200 |0            |0            |test_02_dieharder.txt |114 PASSED
  3|dieharder -a -g 200 |123456789    |987654321    |test_03_dieharder.txt |110 PASSED, 4 WEAK
  4|dieharder -a -g 200 |max uint64_t |max uint64_t |test_04_dieharder.txt |112 PASSED, 2 WEAK


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
