# Mizar64 PRNG
Mizar64 is a fast, minimalist, robust pseudo-random number generator (PRNG) designed for high-performance applications, simulations, and games. 

```C
uint64_t mizar64(uint64_t *state)
{
	*state = 0x9e3779b97f4a7c15ull * ((*state << 32) | (*state >> 32));
	return 0x9e3779b97f4a7c15ull * (*state ^ (*state >> 17));
}
```

## Features
**Period**: $2^{64} - 1$  
**State**: 64 bit  
**Output**: 64 bit  
**Seed**: all 64-bit values ​​except 0  

## Smoke Test
We decided to use SmokeRand as an initial test tool rather than Dieharder as it is a new tool that we found to be more reliable and accurate.  
We ran 12 full tests with 64-bit inputs; 10 tests with random seeds, and 2 tests with limit seeds (1 and UINT64_MAX).  
The test output files are in the test_smokerand/ directory.



## License
This project is released under the **Apache 2.0 License** - see the LICENSE file for details.
