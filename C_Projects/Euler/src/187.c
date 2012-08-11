#include "Euler.h"
#include "Primes.h"
#include <stdlib.h>

int64_t Euler_187()
{
    const uint32_t N = 100000000;
    int N2 = N >> 1;
    uint32_t* primes = primeListE(N2);
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
    return (int64_t) total;
}
