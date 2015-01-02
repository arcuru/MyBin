#include "Euler.h"
#include "Primes.h"
#include <math.h>

// Returns true if the inputs have no common factors greater than 1
static bool GCF(int n, int d, uint32_t* list)
{
	int i;
	uint32_t tmp = n;
	for (i = 0; list[i]*list[i] <= tmp; i++) {
		if ( 0 == tmp % list[i]) {
			// Found another prime factor of n
			if ( 0 == d % list[i] )
				return false; // n & d share a factor, return false
			while ( 0 == tmp % list[i] )
				tmp /= list[i];
		}
	}
	if ( 1 != tmp )
		if ( 0 == d % tmp )
			return false;
	return true;
}

int64_t Euler_73()
{
	const int end = 12000;
	uint32_t* list = primeListE(sqrt(end) + 1);
	int max=0;
	int den;
	for (den=1; den<=end; den++)
	{
		int lower = den/3+1;
		int upper = den/2;
		if ( den%2 == 0 )
			upper -= 1;
		int dex;
		for (dex = lower; dex <= upper; dex++)
			if (GCF(dex, den, list))
				max++;
	}
	return (int64_t) max;
}
