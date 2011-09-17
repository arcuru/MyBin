#include "Euler.h"
#include "Primes.h"
#include <stdlib.h>

int64_t Euler_3()
{
	uint64_t num = 600851475143LL;
	uint64_t* list = primeFactorsE_u64(num);
	int n, ret;
	for (n = 0; list[n]; n++)
		if (!list[n + 1]) {
			ret = list[n];
			break;
		}
	free(list);
	return (int64_t) ret;
}
