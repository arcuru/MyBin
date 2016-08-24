#include "Euler.h"
#include "Primes.h"
#include <stdlib.h>

int64_t Euler_47()
{
	int num = 2000000;
	uint8_t* factors = (uint8_t*) calloc(num, sizeof(uint8_t));

	// Count all the prime factors for each number up to 'num'
	int i, s;
	for ( i = 2; i*i < num; i++ )
		if ( 0 == factors[i] )
			for ( s = i*2; s < num; s += i )
				factors[s]++;

	// Find 4 4's in a row
	int count = 0;
	for ( i = 2; i < num; i++ ) {
		if ( 4 == factors[i] ) {
			count++;
			if ( 4 == count )
				break;
		}
		else
			count = 0;
	}
    free(factors);
	return (int64_t) (i - 3);
}
