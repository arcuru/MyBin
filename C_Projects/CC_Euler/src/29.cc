#include "CC_Euler.h"
#include <math.h>

static int factorarray[101][101];

static int factor(int n) {
	int fac = 0;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			if (fac != 0 && fac != i)
				return 0;
			fac = i;
			n = n / i;
			i--;
		}
	}
	if (fac == n)
		return fac;
	return 0;
}

static void makeArray() {
	for (int a = 2; a <= 100; a++) {
		int fac = factor(a);
		if (fac == 0) {
			factorarray[a][0] = 0;
			continue;
		}
		factorarray[a][0] = fac;
		int n = a;
		int count = 0;
		while (n > 1) {
			n /= fac;
			count++;
		}
		for (int b = 2; b <= 100; b++) {
			factorarray[a][b] = b * count;
		}
	}
}

static bool PrimeFactorCheck(int a, int b) //true if it matches something else
{
	if (factorarray[a][0] == 0)
		return false;
	int base = factorarray[a][0];
	int num = factorarray[a][b];
	for (int i = 2; i < a; i++) {
		if (factorarray[i][0] != base)
			continue;
		for (int dex = 2; factorarray[i][dex] <= num && dex <= 100; dex++) {
			if (factorarray[i][dex] == num) {
				return true;
			}
		}
	}
	return false;
}

int64 Euler_29() {
	makeArray();
	int count = 0;
	bool breaking = false;
	for (int a = 2; a <= 100; a++) {
		for (int b = 2; b <= 100; b++) {
			count++;
			for (int i = 2; i * i <= a; i++) {
				for (int dex = 2; pow(i, dex) <= a; dex++) {
					if (pow(i, dex) == a) {
						if (b * dex <= 100) {
							count--;
							breaking = true;
							break;
						}
					}
				}
				if (breaking) {
					break;
				}
			}
			if (breaking) {
				breaking = false;
				continue;
			}
			if (PrimeFactorCheck(a, b)) {
				count--;
			}
		}
	}
	return (int64) count;
}
