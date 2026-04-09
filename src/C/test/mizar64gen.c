/*
 * mizar64gen.c
 *
 * Version: 1.0
 * Date: 2026-04-01
 * Author: Matteo Zapparoli
 *
 * Prints a continuous stream of random numbers generated with mzr64 to stdout
 *
 * Compile: gcc -O3 -I.. mizar64gen.c ../mizar64.o -o mizar64gen
 *
 * Sintax:
 *  mizar64gen [-d | -r | <seed> | <seed c> <seed x> [-low32 | -high32]]
 *
 * 	mizar64gen                    Print help
 * 	mizar64gen -d                 Uses default mizar64 seeds
 * 	mizar64gen -r                 Uses random seeds (prints seeds on stderr)
 *  mizar64gen <seed>             Uses same seed for c and x
 * 	mizar64gen <seed c> <seed x>  Uses seeds c and x 
 *
 *  option -low32: write on stdout the lowest 32 bit instead full 64 bit
 *  option -high32: write on stdout the highest 32 bit instead full 64 bit
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

#define BUF_SIZE 65536

void usage(void)
{
	printf("mizar64gen - Continous mizar64 stdout pseudo number generator in binary format\n");
	printf("Usage:\n");
	printf("      mizar64gen [-d | -r | <seed> | <seed c> <seed x> [-low32 | -high32]]\n");
	printf("\n");
	printf("      mizar64gen                    Print help\n");
	printf("      mizar64gen -d                 Uses mizar64 default seeds\n");
	printf("      mizar64gen -r                 Uses random seeds(prints seeds on stderr)\n");
	printf("      mizar64gen <seed>             Uses same seed for c and x\n");
	printf("      mizar64gen <seed c> <seed x>  Uses seeds c and x\n");
	printf("\n");
	printf("option -low32: write on stdout the lowest 32 bit instead full 64 bit\n");
	printf("option -high32: write on stdout the highest 32 bit instead full 64 bit\n");
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

// Return -32 if option = "low32"
//        +32 if option = "high32"
//          0 else
int check_low_high(char *option)
{
	if(strcmp(option, "-low32") == 0) {
		return -32;
	}
	if(strcmp(option, "-high32") == 0) {
		return +32;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	mizar64_state_t s;
	int low_high_option;
	
	if(argc == 1) {
		usage();
		return 0;
	}
	
	if(argc > 4) {
		fprintf(stderr, "*** Error: invalid arguments\n");
		return 1;
	}
	
	if(strcmp(argv[1], "-d") == 0) {
		s.c = MIZAR64_DEFAULT_SEED_C;
		s.x = MIZAR64_DEFAULT_SEED_X;
		if(argc == 3) {
			low_high_option = check_low_high(argv[2]);
			if(low_high_option == 0) {
				fprintf(stderr, "*** Error: unknow argument %s\n", argv[2]);
				return 1;
			}
		}
		else if(argc > 3) {
			fprintf(stderr, "*** Error: invalid arguments\n");
			return 1;
		}
	}
	else if(strcmp(argv[1], "-r") == 0) {
		s.c = random_from_clock();
		s.x = random_from_clock();
		fprintf(stderr, "seed c = %llu, seed x = %llu\n", (long long unsigned)s.c, (long long unsigned)s.x);
		if(argc == 3) {
			low_high_option = check_low_high(argv[2]);
			if(low_high_option == 0) {
				fprintf(stderr, "*** Error: unknow argument %s\n", argv[2]);
				return 1;
			}
		}
		else if(argc > 3) {
			fprintf(stderr, "*** Error: invalid arguments\n");
			return 1;
		}
	}
	else if(is_valid_uint64(argv[1], &s.c)) {
		if(argc == 2) {
			s.x = s.c;
		}
		else if(argc == 3) {
			low_high_option = check_low_high(argv[2]);
			if(low_high_option) {
				s.x = s.c;
			}
			else if(!is_valid_uint64(argv[2], &s.x)) {
				fprintf(stderr, "*** Error: invalid argument %s\n", argv[2]);
				return 1;
			}
		}
		else if(argc == 4) {
			if(!is_valid_uint64(argv[2], &s.x)) {
				fprintf(stderr, "*** Error: invalid argument %s\n", argv[2]);
				return 1;
			}
			low_high_option = check_low_high(argv[3]);
			if(low_high_option == 0) {
				fprintf(stderr, "*** Error: invalid argument %s\n", argv[3]);
				return 1;
			}
		}
	}
	else {
		fprintf(stderr, "*** Error: invalid argument %s\n", argv[1]);
		return 1;
	}
	
	if(low_high_option == -32) { // 4 byte bassi
		uint32_t buffer[BUF_SIZE];
		for(;;) {
			for(int i = 0; i < BUF_SIZE; i++) {
				buffer[i] = (uint32_t)mizar64(&s);
			}
			fwrite(buffer, sizeof(uint32_t), BUF_SIZE, stdout);
		}
	}
	else if(low_high_option == +32) { // 4 byte alti
		uint32_t buffer[BUF_SIZE];
		for(;;) {
			for(int i = 0; i < BUF_SIZE; i++) {
				buffer[i] = (uint32_t)(mizar64(&s) >> 32);
			}
			fwrite(buffer, sizeof(uint32_t), BUF_SIZE, stdout);
		}
	}
	else { // Tutti gli 8 byte
		uint64_t buffer[BUF_SIZE];
		for(;;) {
			for(int i = 0; i < BUF_SIZE; i++) {
				buffer[i] = mizar64(&s);
			}
			fwrite(buffer, sizeof(uint64_t), BUF_SIZE, stdout);
		}
	}
	return 0;
}

