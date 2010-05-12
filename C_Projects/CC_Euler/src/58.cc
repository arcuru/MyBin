#include "CC_Euler.h"
#include "CC_Primes.h"

int64 Euler_58() {
	double primenum = 3;
	double totalnum = 5;
	int sidelength = 3;
	int diff = 8;
	int rtop = 3;
	int ltop = 5;
	int lbot = 7;
	int rbot = 9;
	while (primenum / totalnum > 0.1) {
		totalnum += 4;
		diff += 8;
		sidelength += 2;
		rtop += (diff - 6);
		ltop += (diff - 4);
		lbot += (diff - 2);
		rbot += diff;
		if (isPrime(rtop)) {
			primenum++;
		}
		if (isPrime(ltop)) {
			primenum++;
		}
		if (isPrime(lbot)) {
			primenum++;
		}
		if (isPrime(rbot)) {
			primenum++;
		}
	}
	return (int64) sidelength;
}
