#include "CC_Euler.h"
#include "CC_NumberTheory.h"

int64 Euler_243() {
	//250 Mil is not high enough
	return 0;
	int N = 250000000;
	int* phi = EulersTotient(N);
	int n;
	for (n = 2; n < N; n++) {
		if ((int64) phi[n] * 94744 < (int64) (n - 1) * 15499) {
			return (int64) n;
		}
	}
	return 1;
}
