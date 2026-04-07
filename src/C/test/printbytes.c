/*
 * printbyte.c
 *
 * Version: 1.0
 * Date: 2026-04-07
 * Author: Matteo Zapparoli
 *
 * Reads binary bytes from stdin and writes in hex on stdout.
 * Prints a newline every <arg[1]> bytes
 *
 * Compile: gcc -O3 printbytes.c -o printbytes
 *
 * Sintax:
 * 	printbytes                    Print help
 * 	printbytes <n>                Print a newline every n bytes, 0 no print
 *
 */
 
#include <stdio.h>
#include <stdint.h>

void usage(void)
{
	printf("printbytes - Reads binary bytes from stdin and writes in hex on stdout\n");
	printf("Usage:\n");
	printf("      printbytes         Print help\n");
	printf("      printbytes <n>     Print a newline every n bytes, 0 no print\n");
}

int main(int argc, char *argv[])
{
	if(argc == 1) {
		usage();
		return 0;
	}
	
	if(argc != 2) {
		fprintf(stderr, "*** Error: invalid arguments\n");
		return 1;
	}
	
	int num;
	if(sscanf(argv[1], "%d", &num) != 1 || num < 0) {
		fprintf(stderr, "*** Error: invalid number\n");
		return 1;
	}
	
	uint8_t byte;
	size_t n;
	int i = 0;
	while((n = fread(&byte, sizeof(uint8_t), 1, stdin)) > 0) {
		printf("%02X", byte);
		if(++i == num) {
			printf("\n");
			i = 0;
		}
	}
	
}
