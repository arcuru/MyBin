#include "CC_Euler.h"
#include "CC_Primes.h"

int64 Euler_50() {
	int N = 1000000;
	unsigned char* primes = SieveEratosthenes(N);
	int* list = primeListE(N, primes);
	int total = 0;
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
	return (int64) total;
}

