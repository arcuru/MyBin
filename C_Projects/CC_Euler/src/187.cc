#include "CC_Euler.h"
#include "CC_Primes.h"

int64 Euler_187() {
	int N = 100000000;
	int N2 = N >> 1;
	int* primes = primeListE(N2);
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
	return (int64) total;
}
