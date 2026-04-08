/*
 * simplegen.c
 *
 * Version: 1.0
 * Date: 2026-04-07
 * Author: Matteo Zapparoli
 *
 * Simple mizar64 generator.
 * Used to compare Miza64 java version vs Mizar64 C version
 *
 * Compile: gcc -O3 -I.. simplegen.c ../mizar64.o -o simplegen
 *
 * Sintax:
 * 	 simplegen                         Print help
 *   simplegen <seed c> <seed x> <n>   Print on stdout n pseudo-random 64 bit numbers
 *
 */

#include <stdio.h>

#include "mizar64.h"

void usage(void)
{
	printf("SimpleGen - Print on stdout random number using miza64 PRNG\n");
	printf("Usage: simplegen <seed c> <seed x> <n>\n");
}

int main(int argc, char *argv[])
{
	if(argc == 0) {
		usage();
		return 0;
	}
	
	if(argc != 4) {
		fprintf(stderr, "*** Error: invalid arguments\n");
		return 1;
	}
	
	mizar64_state_t state;
	
	if(sscanf(argv[1], "%ld", &state.c) != 1) {
		fprintf(stderr, "*** Error: invalid number\n");
		return 1;
	}

	if(sscanf(argv[2], "%ld", &state.x) != 1) {
		fprintf(stderr, "*** Error: invalid number\n");
		return 1;
	}
	
	int n;
	if(sscanf(argv[3], "%d", &n) != 1) {
		fprintf(stderr, "*** Error: invalid number\n");
		return 1;
	}
	
	uint64_t checksum = 0ULL;
	while(n-- > 0) {
		uint64_t rand = mizar64(&state);
		printf("%016llX\n", (long long unsigned)rand);
		checksum ^= rand;
	}
	printf("\nChecksum = %016llX\n", (long long unsigned)checksum);
	
	return 0;
}
