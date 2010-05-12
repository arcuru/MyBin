#include "CC_Euler.h"
#include "CC_NumberTheory.h"

static double canceller(int c, int d) {
	int a = c;
	int b = d;
	if ((a % 10 == 0) && (b % 10 == 0)) {
		return 1;
	}
	double atens, asingles, btens, bsingles;
	atens = (a / 10) % 10;
	asingles = a % 10;
	btens = (b / 10) % 10;
	bsingles = b % 10;
	//printf("%f\n%f\n%f\n%f\n",atens,asingles,btens,bsingles);
	if ((atens != asingles) && (btens != bsingles)) {
		if (bsingles != 0) {
			if (atens == btens) {
				return asingles / bsingles;
			} else if (asingles == btens) {
				return atens / bsingles;
			}
		}
		if (btens != 0) {
			if (atens == bsingles) {
				return asingles / btens;
			} else if (asingles == bsingles) {
				return atens / btens;
			}
		}
	}
	return 1;
}

int64 Euler_33() {
	int num, den, prodnum, prodden;
	prodnum = 1;
	prodden = 1;
	for (num = 10; num < 50; num++) {
		for (den = 99; den > num; den--) {
			double a = num;
			double b = den;
			double val = a / b;
			//printf("%f\n",val);
			double g = canceller(num, den);
			//printf("%f\n",g);
			if (val == g) {
				prodnum *= num;
				prodden *= den;
			}
		}
	}
	return (int64) (prodden / GCD(prodnum, prodden));
}
