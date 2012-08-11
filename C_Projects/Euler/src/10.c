#include "Euler.h"
#include "Primes.h"

int64_t Euler_10()
{
    int N = 2000000;
    uint8_t* list = SieveEratosthenes(N);
    int n = 1;
    uint64_t total = NextPrime(N, list);
    while (n > 0) {
        n = NextPrime(N, (void *)0);//(void*)0 = NULL, this avoids including stdio.h
        total += n;
    }
    return (int64_t) total;
}

