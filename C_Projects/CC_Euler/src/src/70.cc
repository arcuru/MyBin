#include "CC_Euler.h"
#include "CC_NumberTheory.h"
#include <stdlib.h>

static int isPerm(int n, int p) {
	int numN[10], numP[10];
	int i;
	for (i = 0; i < 10; i++) {
		numN[i] = 0;
		numP[i] = 0;
	}
	while (n > 0) {
		numN[n % 10]++;
		numP[p % 10]++;
		n /= 10;
		p /= 10;
	}

	if (p)
		return 0;
	for (i = 0; i < 10; i++) {
		if (numN[i] != numP[i])
			return 0;
	}
	return 1;
}

int64 Euler_70() {
	int N = 10000000;
	int* list = EulersTotient(N);
	int n;
	double min = 2;
	int minN = 0;
	for (n = 2; n <= N; n++) {
		double tmp = ((double) n) / list[n];
		if (tmp < min) {
			if (isPerm(n, list[n])) {
				minN = n;
				min = tmp;
			}
		}
	}
	free(list);
	return (int64) minN;
}

