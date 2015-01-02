#include "Euler.h"
#include <gmp.h>

int64_t Euler_53()
{
	int64_t count=0;
	int n,r;
	for (n=23;n<=100;n++) {
		for (r=1;r<n;r++) {
			mpz_t top,bottom;
			mpz_init (top);
			mpz_init (bottom);
			mpz_fac_ui(top,n-r);
			mpz_fac_ui(bottom,r);
			mpz_mul(bottom,top,bottom);
			mpz_mul_ui(bottom,bottom,1000000);
			mpz_fac_ui(top,n);
			if (mpz_cmp(top,bottom) > 0)
				count++;
		}
	}
	return (int64_t) count;
}
