#include "Euler.h"
#include "Primes.h"
#include <stdlib.h>

int64_t Euler_7()
{
    int N = 105000;
    int* prime = primeListE(N);
    int out = prime[10000];
    free(prime);
    return (int64_t) out;
}

