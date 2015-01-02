#include "Euler.h"
#include <stdio.h>
#include <gmp.h>

// Returns true if the inputs have no common factors greater than 1
static bool GCF(int n, int d)
{
	mpz_t x;
	mpz_init (x);
	mpz_set_ui(x,n);
	if (mpz_gcd_ui(NULL,x,d) > 1) return false;
	return true;
}

int64_t Euler_73()
{
	const int end = 12000;
	int max=0;
	int den;
	for (den=1; den<=end; den++)
	{
		int lower=den/3+1;
		int upper=den/2;
		if ( den%2 == 0 )
			upper-=1;
		int dex;
		for (dex=lower; dex<=upper; dex++)
			if (GCF(dex,den))
				max++;
	}
	return (int64_t) max;
}
