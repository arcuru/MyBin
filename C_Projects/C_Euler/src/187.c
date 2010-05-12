#include "C_Euler.h"
#include "C_Primes.h"
#include <stdlib.h>

int64 Euler_187()
{
    int N = 100000000;
    int N2 = N >> 1;
    int* primes = primeListE(N2);
    int total = 0, i = 0, n = 0;
    while (primes[i]) {
        i++;
    }
    i--;
    while (n < i) {
        while (primes[i] * primes[n] > N) {
            i--;
        }
        total += i - n + 1;
        n++;
    }
    free(primes);
    return (int64) total;
}
