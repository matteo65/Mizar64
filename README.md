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
**Period**: from ($2^{62} - 1$) to ($2^{64} - 1$) depending on seed  
**State**: 64 bit  
**Output**: 64 bit  
**Seed**: all 64-bit values ​​except 0  

## Tools
The [tools/](https://github.com/matteo65/Mizar64/tree/main/tools) directory contains the programs used to run quality and speed tests; they are:
- **mizar64gen**: writes a continuous stream of binary numbers generated with mizar64 to stdout
- **testu01_mizar64_high32**: runs mizar64 TestU01 SmallCrush, Crush or BigCrush on the high 32 bits
- **testu01_mizar64_mid32**: runs mizar64 TestU01 SmallCrush, Crush or BigCrush on the middle 32 bits
- **testu01_mizar64_low32**: runs mizar64 TestU01 SmallCrush, Crush or BigCrush on the low 32 bits

## SmokeRand v.0.47-gcc-linux Tests
We decided to use [SmokeRand](https://github.com/alvoskov/SmokeRand) (**v. 0.47-gcc-linux64**) as an initial test tool rather than Dieharder as it is a new tool that we found to be more reliable and accurate.  
We ran 12 full runs with 64-bit inputs; 10 runs with random seeds, and 2 runs with limit seeds (1 and MAX_UINT64).  
The output files are in the [test_smokerand/](https://github.com/matteo65/Mizar64/tree/main/test_smokerand) directory.
Each full run performs 50 tests, for a total of 600 tests.
No failures were detected, and three suspects were found, a number consistent with the expected value.
All runs scored a quality of 4 (good) on a scale from 0 to 4.  

### SmokeRand Test Summary Table

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
|12|MAX_UINT64          |       -         |

## PractRand v.0.96 Tests
We used [PractRand](https://pracrand.sourceforge.net/) version **0.96** with 64-bit input. We performed 12 runs from **1GB** to **64TB**.  

## TestU01 v.1.2.3 Tests
Number of session tests: 100  
Number of big_crush runs: 300  
Nomber of TestU01 statistics: 48000  
Number of failures: 0  
Number of anomalies: 99  
Number of anomalies expected: 96.0  

|Runs|high32|mid32|low32|**Total**|
|----|------|-----|-----|---------|
|With anomalies|27|26|29|**82**|
|Without anomalies|73|74|71|218|
|**Total**|**100**|**100**|**100**|

### Details of anomalies for each session test
| Test | high32 | mid32 | low32 |
|------|--------|--------|--------|
|00|-|-|-|
|01|-|26 SimpPoker, r = 0 (0.9993);<br>32 CouponCollector, r = 20 (0.9994)|-|
|02|22 ClosePairs mNP, t = 3 (0.9998)|-|72 Savir2 (4.7e-4);<br>79 RandomWalk1 C (L=10000, r=15) (0.9995)|
|03|-|106 AutoCor, d=3, r=27 (1.5e-4)|-|
|04|-|-|-|
|05|-|-|22 ClosePairs mNP2S, t = 3 (7.3e-4);<br>65 SumCollector (5.4e-4)|
|06|-|-|-|
|07|-|-|-|
|08|-|22 ClosePairs NP, t = 3 (0.9993)|96 HammingIndep, L=30, r=27 (7.1e-5)|
|09|-|12 CollisionOver, t = 21 (0.9996)|-|
|10|-|-|-|
|11|-|-|99 HammingIndep, L=1200, r=0 (0.9998)|
|12|-|49 MaxOft, t = 32 (0.9995)|-|
|13|64 WeightDistrib, r = 26 (2.7e-4);<br>89 PeriodsInStrings, r = 20 (9.8e-4)|3 CollisionOver, t = 2 (0.9998)|-|
|14|-|78 RandomWalk1 H (L=10000, r=0) (4.4e-5)|-|
|15|4 CollisionOver, t = 2 (0.9998);<br>102 Run of bits, r = 27 (6.5e-4)|-|-|
|16|-|-|-|
|17|-|79 RandomWalk1 J (L=10000, r=15) (1 - 9.9e-5)|-|
|18|-|-|-|
|19|-|-|24 ClosePairs NJumps, t = 9 (6.2e-4)|
|20|-|-|-|
|21|79 RandomWalk1 C (L=10000, r=15) (0.9994)|-|-|
|22|-|-|-|
|23|67 MatrixRank, L=30, r=26 (5.5e-4);<br>70 MatrixRank, L=5000 (8.3e-5)|-|22 ClosePairs mNP2, t = 3 (5.4e-4)|
|24|50 SampleProd, t = 8 (0.9994)|-|-|
|25|-|75 RandomWalk1 H (L=50, r=25) (0.9992)|-|
|26|-|-|-|
|27|-|-|-|
|28|-|-|-|
|29|25 ClosePairs mNP1, t = 16 (0.9996);<br>92 HammingCorr, L = 30 (2.3e-4)|-|39 Run, r = 15 (4.4e-4)|
|30|-|-|-|
|31|-|-|-|
|32|-|-|-|
|33|-|-|103 AutoCor, d=1, r=0 (8.9e-5)|
|34|-|-|-|
|35|-|22 ClosePairs mNP1, t = 3 (0.9993)|-|
|36|-|-|101 Run of bits, r = 0 (1.2e-4)|
|37|-|26 SimpPoker, r = 0 (7.5e-5)|-|
|38|-|104 AutoCor, d=3, r=0 (2.4e-4)|-|
|39|-|-|23 ClosePairs mNP, t = 5 (2.0e-4)|
|40|-|-|-|
|41|-|-|-|
|42|-|12 CollisionOver, t = 21 (0.9993)|12 CollisionOver, t = 21 (6.0e-4);<br>67 MatrixRank, L=30, r=26 (0.9992)|
|43|-|1 SerialOver, r = 0 (9.9e-4)|-|
|44|-|-|-|
|45|-|24 ClosePairs mNP1, t = 9 (7.1e-4)|-|
|46|-|11 CollisionOver, t = 21 (8.6e-4)|-|
|47|-|-|-|
|48|-|68 MatrixRank, L=1000, r=0 (2.9e-4)|12 CollisionOver, t = 21 (6.0e-4)|
|49|32 CouponCollector, r = 20 (3.4e-4)|47 MaxOft, t = 16 (2.7e-4)|-|
|50|4 CollisionOver, t = 2 (0.9991)|-|-|
|51|49 MaxOft AD, t = 32 (8.7e-4)|23 ClosePairs NJumps, t = 5 (4.2e-4);<br>97 HammingIndep, L=300, r=0 (0.9995)|-|
|52|53 SampleMean, r = 0 (6.1e-4)|-|-|
|53|-|-|-|
|54|-|-|88 PeriodsInStrings, r = 0 (0.9996)|
|55|-|11 CollisionOver, t = 21 (0.9998);<br>76 RandomWalk1 C (L=1000, r=0) (5.7e-4)|11 CollisionOver, t = 21 (0.9992)|
|56|28 SimpPoker, r = 0 (0.9999);<br>46 MaxOft, t = 8 (1 - 3.8e-5);<br>84 Fourier3, r = 0 (0.9998)|55 SampleCorr, k = 1 (7.6e-4)|37 Gap, r = 20 (6.8e-4)|
|57|-|-|29 SimpPoker, r = 25 (6.2e-4);<br>55 SampleCorr, k = 1 (0.9997)|
|58|-|22 ClosePairs mNP, t = 3 (3.9e-4)|-|
|59|-|40 Permutation, t = 3 (9.9e-4)|-|
|60|-|-|-|
|61|103 AutoCor, d=1, r=0 (7.9e-4)|-|-|
|62|-|-|-|
|63|-|-|-|
|64|78 RandomWalk1 J (L=10000, r=0) (5.5e-4)|-|-|
|65|12 CollisionOver, t = 21 (0.9996);<br>23 ClosePairs mNP2S, t = 5 (9.1e-4)|-|20 BirthdaySpacings, t = 16 (5.9e-4)|
|66|-|-|-|
|67|-|-|-|
|68|-|-|-|
|69|-|-|12 CollisionOver, t = 21 (6.5e-4)|
|70|79 RandomWalk1 H (L=10000, r=15) (3.6e-4)|-|-|
|71|-|-|-|
|72|55 SampleCorr, k = 1 (1 - 5.2e-5)|-|-|
|73|12 CollisionOver, t = 21 (1.4e-4)|-|-|
|74|6 CollisionOver, t = 3 (4.4e-5)|-|-|
|75|79 RandomWalk1 C (L=10000, r=15) (2.3e-4)|-|11 CollisionOver, t = 21 (1 - 6.7e-5)|
|76|-|-|-|
|77|75 RandomWalk1 M (L=50, r=25) (0.9997)|-|38 Run, r = 0 (5.6e-5)|
|78|75 RandomWalk1 M (L=50, r=25) (0.9995)|-|-|
|79|34 Gap, r = 0 (0.9995)|-|25 ClosePairs mNP, t = 16 (5.1e-4)|
|80|-|-|-|
|81|-|-|55 SampleCorr, k = 1 (0.9999)|
|82|-|-|22 ClosePairs mNP2S, t = 3 (8.3e-4)|
|83|-|-|-|
|84|-|55 SampleCorr, k = 1 (8.4e-4)|-|
|85|-|-|-|
|86|-|-|-|
|87|-|-|-|
|88|-|-|-|
|89|-|-|-|
|90|-|12 CollisionOver, t = 21 (1.0e-4)|-|
|91|-|-|-|
|92|64 WeightDistrib, r = 26 (0.9991)|-|-|
|93|-|-|35 Gap, r = 25 (0.9992)|
|94|74 RandomWalk1 H (L=50, r=0) (1 - 3.7e-6)|-|9 CollisionOver, t = 14 (0.9998)|
|95|94 HammingCorr, L = 1200 (0.9990)|-|74 RandomWalk1 J (L=50, r=0) (0.9997);<br>78 RandomWalk1 M (L=10000, r=0) (1 - 8.4e-5)|
|96|34 Gap, r = 0 (1.7e-5)|-|22 ClosePairs mNP2, t = 3 (0.9994)|
|97|-|-|25 ClosePairs mNP1, t = 16 (9.3e-4);<br>25 ClosePairs NJumps, t = 16 (0.9995)|
|98|-|-|47 MaxOft AD, t = 16 (2.5e-4);<br>49 MaxOft AD, t = 32 (0.9993)|
|99|-|76 RandomWalk1 R (L=1000, r=0) (0.9991)|-|

### Ranking by frequency of anomalies
|Anomaly|high32|mid32|low32|
|-------|------|-----|-----|
|22 ClosePairs mNP, t = 3|1|3|4|
|12 CollisionOver, t = 21|2|3|3|
|79 RandomWalk1 C (L=10000, r=15)|3|1|1|
|55 SampleCorr, k = 1|1|2|2|
|25 ClosePairs mNP1, t = 16|1|0|3|
|11 CollisionOver, t = 21|0|2|2|
|49 MaxOft, t = 32|1|1|1|
|78 RandomWalk1 H (L=10000, r=0)|1|1|1|
|75 RandomWalk1 H (L=50, r=25)|2|1|0|
|23 ClosePairs mNP, t = 5|1|1|1|
|26 SimpPoker, r = 0|0|2|0|
|32 CouponCollector, r = 20|1|1|0|
|64 WeightDistrib, r = 26|2|0|0|
|4 CollisionOver, t = 2|2|0|0|
|24 ClosePairs NJumps, t = 9|0|1|1|
|67 MatrixRank, L=30, r=26|1|0|1|
|103 AutoCor, d=1, r=0|1|0|1|
|47 MaxOft, t = 16|0|1|1|
|76 RandomWalk1 C (L=1000, r=0)|0|2|0|
|34 Gap, r = 0|2|0|0|
|74 RandomWalk1 H (L=50, r=0)|1|0|1|
|72 Savir2|0|0|1|
|106 AutoCor, d=3, r=27|0|1|0|
|65 SumCollector|0|0|1|
|96 HammingIndep, L=30, r=27|0|0|1|
|99 HammingIndep, L=1200, r=0|0|0|1|
|89 PeriodsInStrings, r = 20|1|0|0|
|3 CollisionOver, t = 2|0|1|0|
|102 Run of bits, r = 27|1|0|0|
|70 MatrixRank, L=5000|1|0|0|
|50 SampleProd, t = 8|1|0|0|
|92 HammingCorr, L = 30|1|0|0|
|39 Run, r = 15|0|0|1|
|101 Run of bits, r = 0|0|0|1|
|104 AutoCor, d=3, r=0|0|1|0|
|1 SerialOver, r = 0|0|1|0|
|68 MatrixRank, L=1000, r=0|0|1|0|
|97 HammingIndep, L=300, r=0|0|1|0|
|53 SampleMean, r = 0|1|0|0|
|88 PeriodsInStrings, r = 0|0|0|1|
|28 SimpPoker, r = 0|1|0|0|
|46 MaxOft, t = 8|1|0|0|
|84 Fourier3, r = 0|1|0|0|
|37 Gap, r = 20|0|0|1|
|29 SimpPoker, r = 25|0|0|1|
|40 Permutation, t = 3|0|1|0|
|20 BirthdaySpacings, t = 16|0|0|1|
|6 CollisionOver, t = 3|1|0|0|
|38 Run, r = 0|0|0|1|
|35 Gap, r = 25|0|0|1|
|9 CollisionOver, t = 14|0|0|1|
|94 HammingCorr, L = 1200|1|0|0|
|**Total**|**34**|**29**|**36**|
|**Expected**|**32.0**|**32.0**|**32.0**|

### Interval p-value distribution
|p-value Interval|Found|**Expected**|
|----------------|-----|--------|
|[1.0e-4, 1.0e-3)|83|**86.4**|
|[1.0e-5, 1.0e-4)|15|**8.6**|
|[1.0e-6, 1.0e-5)|1|**0.9**|
|[1.0e-7, 1.0e-6)|0|**0.1**|
|[1.0e-8, 1.0e-7)|0|**0.0**|
|[0, 1.0e-7)     |0|**0.0**|
|**Total**       |**99**|**96.0**|

### Top/Bottom p-value distribuition
This table displays the breakdown of p-values ​​close to 1 (top) and close to 0 (bottom); in an ideal uniform distribution the values ​​should be equal.  
|    |high32 | mid32 | low32 |**Total**|
|----|-------|-------|-------|---------|
|Top |17|13|15|**45**|
|Bottom|17|16|21|**54|
|**Total**|**34**|**29**|**36**|99**|

### Statistical of p-values
|    |high32 | mid32 | low32 |
|----|-------|-------|-------|
|Top Average|0.9996|0.9995|0.9996|
|Top Max Value|1 - 3.7e-6|1 - 9.9e-5|1 - 6.7e-5|
|Top Min Value|0.9990|0.9991|0.9992|
|Top Standard Deviation|0.001260|0.000867|0.001011|
|Bottom Average|4.48e-4|4.81e-4|4.83e-4|
|Bottom Max Value|9.8e-4|9.9e-4|9.3e-4|
|Bottom Min Value|1.7e-5|4.4e-5|5.6e-5|
|Bottom Standard Deviation|0.001266|0.001300|0.001143|



## Hamming–Weight Dependencies

... work in progress ...

## License
This project is released under the **Apache 2.0 License** - see the LICENSE file for details.
