#include "CC_Euler.h"
#include "CC_Primes.h"
#include <stdlib.h>

//Sum of Prime Factors of 20000000!/(15000000!*5000000!)
int64 Euler_231() {
	unsigned char* totallist = SieveEratosthenes(20000000);
	int* primes = primeListE(20000000, totallist);
	int n, s;
	int* low = (int*) (malloc)(sizeof(int) * 5000001);//0-5000000
	int* high = (int*) (malloc)(sizeof(int) * 5000001);//15000000-20000000
	if (!low || !high)
		return 0;
	for (n = 1; n <= 5000000; n++) {
		low[n] = n;
		high[n] = n + 15000000;
	}
	int* factors = (int*) calloc(20000001, sizeof(int));
	for (s = 0; primes[s] * primes[s] <= 5000000; s++) {
		for (n = primes[s]; n <= 5000000; n += primes[s]) {
			low[n] /= primes[s];
			factors[primes[s]]--;
			while (!(low[n] % primes[s]) && low[n] > 1) {
				low[n] /= primes[s];
				factors[primes[s]]--;
			}
		}
	}
	for (s = 0; primes[s] && primes[s] * primes[s] <= 20000000; s++) {
		n = primes[s];
		n = n * (14999999 / n) - 15000000;
		while (n <= 0)
			n += primes[s];
		for (; n <= 5000000; n += primes[s]) {
			high[n] /= primes[s];
			factors[primes[s]]++;
			while (!(high[n] % primes[s]) && high[n] > 1) {
				high[n] /= primes[s];
				factors[primes[s]]++;
			}
		}
	}
	for (n = 1; n <= 5000000; n++) {
		if (low[n] != 1 && n) {
			if (isPrimeE(low[n], totallist)) {
				factors[low[n]]--;
				low[n] = 1;
			}
		}
		if (high[n] != 1) {
			if (isPrimeE(high[n], totallist)) {
				factors[high[n]]++;
				high[n] = 1;
			}
		}
	}
	uns64 total = 0;
	for (n = 0; n <= 20000000; n++) {
		total += factors[n] * n;
	}
	free(factors);
	free(low);
	free(high);
	return (int64) total;
}
