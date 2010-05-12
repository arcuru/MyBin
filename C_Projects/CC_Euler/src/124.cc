#include "CC_Euler.h"
#include "CC_Primes.h"
#include <stdlib.h>

static void BubbleSort(int* d, int n, int* thek) {
	int k, tmp;
	int i = 1;
	while (i < n) {
		k = i;
		while ((k > 0) && (d[k] < d[k - 1])) {
			tmp = d[k];
			d[k] = d[k - 1];
			d[k - 1] = tmp;

			tmp = thek[k];
			thek[k] = thek[k - 1];
			thek[k - 1] = tmp;
			k--;
		}
		i++;
	}
}

int64 Euler_124() {
	int N = 100000;
	int* rad = (int*) (malloc)(sizeof(int) * (N + 1));
	int* k = (int*) (malloc)(sizeof(int) * (N + 1));
	int* primes = primeListE(N);
	rad[0] = 0;
	for (int i = 1; i <= N; i++) {
		int* list = primeFactorsE(i, primes);
		int radval = 1;
		for (int n = 0; list[n]; n++) {
			radval *= list[n];
			int s = 0;
			while (list[n + s + 1] == list[n])
				s++;
			n += s;
		}
		rad[i] = radval;
	}
	for (int i = 0; i <= N; i++)
		k[i] = i;
	BubbleSort(rad, N + 1, k);
	return (int64) k[10000];
}


