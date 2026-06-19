# Mizar64 PRNG
Mizar64 is an fast, minimalist, robust pseudo-random number generator (PRNG) designed for high-performance applications, simulations, and games. 

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

## License
This project is released under the **Apache 2.0 License** - see the LICENSE file for details.
