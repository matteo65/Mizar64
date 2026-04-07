/*
 * mizar64gen.c
 *
 * Version: 1.0
 * Date: 2026-04-01
 * Author: Matteo Zapparoli
 *
 * Prints a continuous stream of random numbers generated with mizar64 to stdout
 *
 * Compile: gcc -O3 -I.. mizar64gen.c ../mizar64.o -o mizar64gen
 *
 * Sintax:
 * 	mizar64gen                    Print help
 * 	mizar64gen -d                 Uses default mizar64 seeds
 * 	mizar64gen -r                 Uses random seeds (prints seeds on stderr)
 *  mizar64gen <seed>             Uses same seed for c and x
 * 	mizar64gen <seed c> <seed x>  Uses seeds c and x 
 *
 */

#include <stdio.h> // fwrite()
#include <string.h> // strcmp()
#include <stdint.h> // uint64_t
#include <time.h> // clock_gettime()
#include <stdlib.h> // strtoull()
#include <errno.h> // errno
#include <ctype.h> // isdigit()

#include "mizar64.h"

#define BUFFER_SIZE 1024

void usage()
{
	printf("mizar64gen - Continous mizar64 stdout pseudo number generator in binary format\n");
	printf("Usage:\n");
	printf("      mizar64gen                    Print help\n");
	printf("      mizar64gen -d                 Uses mizar64 default seeds\n");
	printf("      mizar64gen -r                 Uses random seeds(prints seeds on stderr)\n");
	printf("      mizar64gen <seed>             Uses same seed for c and x\n");
	printf("      mizar64gen <seed c> <seed x>  Uses seeds c and x \n");
}

int is_valid_uint64(const char *s, uint64_t *out_value)
{
    if (s == NULL || *s == '\0')
        return 0;

    // Controlla che la stringa contenga solo cifre
    for (const char *p = s; *p; p++)
        if (!isdigit((unsigned char)*p))
            return 0;

    errno = 0;
    char *end;
    unsigned long long v = strtoull(s, &end, 10);

    // end non deve spostarsi oltre la fine
    if (*end != '\0')
        return 0;

    // Overflow rilevato da errno
    if (errno == ERANGE)
        return 0;

    // Controllo ulteriore: strtoull potrebbe essere > UINT64_MAX su alcune piattaforme
    if (v > UINT64_MAX)
        return 0;

    if (out_value)
        *out_value = (uint64_t)v;

    return 1;
}

// Return a simple "pseudo-random" based on clock

uint64_t random_from_clock(void) {
    static uint64_t counter = 0;
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    uint64_t x = ((uint64_t)ts.tv_sec << 32) ^ (uint64_t)ts.tv_nsec;

    // aggiungi un contatore per garantire unicità
    x ^= (++counter * 0x9E3779B97F4A7C15ULL);

    // mixing forte (stile splitmix64)
    x ^= x >> 33;
    x *= 0xff51afd7ed558ccdULL;
    x ^= x >> 33;
    x *= 0xc4ceb9fe1a85ec53ULL;
    x ^= x >> 33;

    return x;
}

int main(int argc, char *argv[])
{
	mizar64_state_t s;
	
	if(argc == 1) {
		usage();
		return 0;
	}
	if(argc == 2) {
		if(strcmp(argv[1], "-d") == 0) {
			s.c = MIZAR64_DEFAULT_SEED_C;
			s.x = MIZAR64_DEFAULT_SEED_X;
		}
		else if(strcmp(argv[1], "-r") == 0) {
			s.c = random_from_clock();
			s.x = random_from_clock();
			fprintf(stderr, "seed c = %llu, seed x = %llu\n", (long long unsigned)s.c, (long long unsigned)s.x);
		}
		else if(is_valid_uint64(argv[1], &s.c)) {
			s.x = s.c;
		}
		else {
			fprintf(stderr, "*** Error: invalid seed number\n");
			return 1;
		}
	}
	else if(argc == 3) {
		if(!is_valid_uint64(argv[1], &s.c)) {
			fprintf(stderr, "*** Error: invalid seed c\n");
		}
		if(!is_valid_uint64(argv[2], &s.x)) {
			fprintf(stderr, "*** Error: invalid seed x\n");
		}	
	}
	else {
		fprintf(stderr, "*** Error: invalid arguments\n");
		return 1;
	}

	for(;;) {
		uint64_t n = mizar64(&s);
		fwrite(&n, sizeof(uint64_t), 1, stdout);
	}

}
