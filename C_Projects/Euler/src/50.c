#include "Euler.h"
#include "Primes.h"

int64_t Euler_50()
{
    const uint32_t N = 1000000;
    uint8_t* primes = SieveEratosthenes(N);
    uint32_t* list = primeListE_inc(N, primes);
    uint32_t total = 0;
    int n;
    for (n = 0; total + list[n] <= N; n++) {
        total += list[n];
    }
    int bottom = 0;
    int top = n;
    while (!isPrimeE(total, primes)) {
        total -= list[bottom];
        bottom++;
        if (total + list[top] < N) {
            total += list[top];
            top++;
        }
    }
    return (int64_t) total;
}

