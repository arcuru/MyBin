#include "C_Euler.h"
#include "C_Primes.h"

int64 Euler_27()
{
    unsigned char* prime = primeIndexListE(1000000);
    int a, b, value, c, count, mvab = 0, maxcount = 0;
    for (a = -999; a < 1000; a++) {
        for (b = 0; b < 1000; b++) {
            if (prime[b] == 0) {
                continue;
            }
            count = 0;
            for (c = 0; c < 500; c++) {
                value = (c * c) + (a * c) + b;
                if (value > 0 && prime[value]) {
                    count++;
                } else if (count > maxcount) {
                    mvab = a * b;
                    maxcount = count;
                    break;
                } else {
                    break;
                }
            }
        }
    }
    return (int64) mvab;
}
