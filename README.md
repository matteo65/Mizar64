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

## Tools
The tools directory contains the tools used to run quality and speed tests; they are:
- mizar64gen: Writes a continuous stream of binary numbers generated with Mizar64 to stdout
- testu01_mizar64_high32: runs mizar64 TestU01 SmallCrush, Crush or BigCrush on the high 32 bits
- testu01_mizar64_mid32: runs mizar64 TestU01 SmallCrush, Crush or BigCrush on the mmidle 32 bits
- testu01_mizar64_low32: runs mizar64 TestU01 SmallCrush, Crush or BigCrush on thw low 32 bits

## Smoke Test
We decided to use [SmokeRand](https://github.com/alvoskov/SmokeRand) (v0.47-gcc-linux64) as an initial test tool rather than Dieharder as it is a new tool that we found to be more reliable and accurate.  
We ran 12 full runs with 64-bit inputs; 10 runs with random seeds, and 2 runs with limit seeds (1 and UINT64_MAX).  
The output files are in the [test_smokerand/](https://github.com/matteo65/Mizar64/tree/main/test_smokerand) directory.
Each full run performs 50 tests, for a total of 600 tests.
No failures were detected, and three suspects were found, a number consistent with the expected value.
All runs scored a quality of 4 (good) on a scale from 0 to 4.  

### SmokeRand Summary Table

|# |         Seed       | Anomalies       |
|--|--------------------|-----------------|
|01|13105777253706137164|15 bspace4_8d_dec p-value = 2.74e-04<br>27 collover3_13d_high p-value = 1 - 7.90e-04|
|02|1686565851063937383 |       -         |
|03|13596189648237307270|       -         |
|04|5848746668826697502 |41 hamming_ot_u512 p-value = 1 - 1.83e-06|
|05|3696122887039482347 |       -         |
|06|13448597441533183639|       -         |
|07|15606701140595568730|       -         |
|08|5529151067911971518 |       -         |
|09|9243983136210913915 |       -         |
|10|353607324833234878  |       -         |
|11|1                   |       -         |
|12|UMAX_INT64          |       -         |

## PractRand Test
We used PractRand version 0.96 with 64-bit input. We performed 12 runs from 1GB to 64TB.  

## TestU01

... work in progress ...

## License
This project is released under the **Apache 2.0 License** - see the LICENSE file for details.
