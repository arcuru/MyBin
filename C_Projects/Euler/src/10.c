#include "Euler.h"
#include "Primes.h"

int64 Euler_10()
{
    int N = 2000000;
    unsigned char* list = SieveEratosthenes(N);
    int n = 1;
    uns64 total = NextPrime(N, list);
    while (n > 0) {
        n = NextPrime(N, (void *)0);
        total += n;
    }
    return (int64) total;
}

