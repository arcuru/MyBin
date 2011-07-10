#include "Euler.h"
#include "Primes.h"

/*
 * 37 36 35 34 33 32 31
 * 38 17 16 15 14 13 30
 * 39 18  5  4  3 12 29
 * 40 19  6  1  2 11 28
 * 41 20  7  8  9 10 27
 * 42 21 22 23 24 25 26
 * 43 44 45 46 47 48 49
 */

//Right and down produces only odd # squares
//Precalculates initial 3x3 grid
int64_t Euler_58()
{
    double primenum = 3;
    double totalnum = 5;
    int sidelength = 3;
    int diff = 6;
    int rtop = 3;
    int ltop = 5;
    int lbot = 7;
    while ((primenum / totalnum) > 0.1) {
        totalnum += 4;
        diff += 8;
        sidelength += 2;
        rtop += (diff - 4);
        ltop += (diff - 2);
        lbot += diff;
        if (isPrime(rtop)) {
            primenum++;
        }
        if (isPrime(ltop)) {
            primenum++;
        }
        if (isPrime(lbot)) {
            primenum++;
        }
    }
    return (int64_t) sidelength;
}
