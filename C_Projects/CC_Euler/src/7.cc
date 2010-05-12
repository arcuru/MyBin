#include "CC_Euler.h"
#include "CC_Primes.h"

int64 Euler_7()
{
	int N = 105000;
	int* prime = primeListE(N);
	return (int64)prime[10000];
}

