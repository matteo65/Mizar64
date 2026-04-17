package org.mizar64.test;

import org.mizar64.Mizar64;

/**
 * Simple mizar64 generator.
 * Used to compare Miza64 java version vs Mizar64 C version
 * @author Matteo Zapparoli
 * 7 apr 2026
 */
public class SimpleGen {

    private static void usage() {
        System.out.println("SimpleGen - Print on stdout random number using miza64 PRNG");
        System.out.println("Usage: simplegen <seed> <n>");
    }
    
    public static void main(String[] args) {
        if(args == null || args.length == 0) {
            usage();
            System.exit(0);
        }
        
        if(args.length != 2) {
            System.err.println("*** Error: invalid arguments");
            System.exit(1);
        }
        
        long checksum = 0L;
        long seed = Long.parseLong(args[0]);
        int n = Integer.parseInt(args[1]);
        Mizar64 mizar64 = new Mizar64(seed);
        while(n-- > 0) {
            long rand = mizar64.nextLong();
            System.out.printf("%016X\n", rand);
            checksum ^= rand;
        }
        System.out.printf("\nChecksum = %016X\n", checksum);
    }
}

