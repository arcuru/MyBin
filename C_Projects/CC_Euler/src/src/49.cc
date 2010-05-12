#include "CC_Euler.h"
#include "CC_Primes.h"
#include <stdlib.h>

bool isPerm(int a, int b) {
	int* lista = (int*)calloc(10,sizeof(int));
	int* listb = (int*)calloc(10,sizeof(int));
	while ((a!=0) && (b!=0)) {
		lista[a%10]++;
		a/=10;
		listb[b%10]++;
		b/=10;
	}
	int n;
	for (n=0;n<10;n++){
		if (lista[n]!=listb[n]) {
			return false;
		}
	}
	free(lista);
	free(listb);
	return true;
}

int64 Euler_49() {
	unsigned char* primelist = SieveEratosthenes(10000);
	int a,b;
	for (a=1000;a<10000;a++){
		if (!isPrimeE(a,primelist) || (a==1487))
			continue;
		for (b=a+1;(b+(b-a))<10000;b++) {
			if (!isPrimeE(b,primelist))
				continue;
			if (isPerm(a,b) && isPrimeE(b+b-a,primelist) && isPerm(a,b+b-a)) {
				int64 ans=a;
				ans*=10000;
				ans+=b;
				ans*=10000;
				ans+=b+b-a;
				return (int64)ans;
			}
		}
	}
	return (int64) 0;
}
