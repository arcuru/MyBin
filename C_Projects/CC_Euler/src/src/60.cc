#include "CC_Euler.h"
#include "CC_Primes.h"
#include "CC_Utils.h"
#include <math.h>

static int min = 1000000000;
static int minlist[6];
static int N = 10000;
static unsigned char* PIndex;

static bool Concatenate(int n, int h) {
	int num1 = n * pow(10, Length(h)) + h;
	int num2 = h * pow(10, Length(n)) + n;
	if (!PIndex[num1])
		return false;
	else if (!PIndex[num2])
		return false;
	return true;
}

static void rec(int* list, int place, int* primelist, int index) {
	if (place == 6) {
		int total = 0;
		for (int i = 1; i < 6; i++)
			total += list[i];
		if (total < min) {
			min = total;
			for (int n = 1; n < 6; n++) {
				minlist[n] = list[n];
			}
		}
		return;
	}
	for (int i = index; primelist[i]; i++) {
		list[place] = primelist[i];
		bool works = true;
		for (int n = 1; n < place; n++) {
			if (!Concatenate(list[n], list[place])) {
				works = false;
				break;
			}
		}
		if (works)
			rec(list, place + 1, primelist, i + 1);
	}
	return;
}

int64 Euler_60() {
	unsigned char* primes = SieveEratosthenes(N * N);
	int* primelist = primeListE(N, primes);
	PIndex = primeIndexListE(N * N, primes);
	int list[6];
	rec(list, 1, primelist, 0);
	return (int64) min; //13	5197	5701	6733	8389
}
