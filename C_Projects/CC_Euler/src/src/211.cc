#include "CC_Euler.h"
#include <stdlib.h>
#include <math.h>

int64 Euler_211() {
	uns64 N = 64000000;
	uns64* list = (uns64*) calloc(N, sizeof(uns64));
	if (!list)
		return 0;
	uns64 n, s, q;
	for (n = 1; n < N; n++) {
		s = n;
		q = n * n;
		while (s < N) {
			list[s] += q;
			s += n;
		}
	}
	uns64 total = 0;
	for (n = 1; n < N; n++) {
		if ((double) (int) sqrt(list[n]) == sqrt(list[n]))
			total += n;
	}
	return (int64) total;
}
