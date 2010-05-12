#include "CC_Euler.h"
#include "CC_Primes.h"

int64 Euler_10() {
	int N = 2000000;
	int* primes = primeListE(N);
	uns64 total = 0;
	int n;
	for (n = 0; primes[n]; n++)
		total += primes[n];
	return (int64) total;
}

