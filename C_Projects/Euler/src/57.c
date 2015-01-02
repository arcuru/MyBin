#include "Euler.h"
#include <gmp.h>
#include <string.h>

int64_t Euler_57()
{
	mpz_t num1,num2,den1,den2;
	mpz_init_set_ui(num1,3);
	mpz_init_set_ui(num2,7);
	mpz_init_set_ui(den1,2);
	mpz_init_set_ui(den2,5);
	int count=0;
	int i;
	for (i=2; i<=1000; i++) {
		char num[1000];
		char den[1000];
		mpz_get_str(num,10,num2);
		mpz_get_str(den,10,den2);

		if ( strlen(num)>strlen(den) )
			count++;

		mpz_t tmp1,tmp2;
		mpz_init_set(tmp1,num1);
		mpz_init_set(tmp2,den1);
		mpz_set(num1,num2);
		mpz_set(den1,den2);
		mpz_mul_2exp(den2,den1,1);
		mpz_mul_2exp(num2,num1,1);
		mpz_add(den2,den2,tmp2);
		mpz_add(num2,num2,tmp1);
	}
	return (int64_t) count;
}
