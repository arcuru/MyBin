#include "Euler.h"
#include "Primes.h"

int64_t Euler_7()
{
    int N = 105000;
    int* prime = primeListE(N);
    return (int64_t) prime[10000];
}

