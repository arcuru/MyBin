#include "CC_Euler.h"

static const int top = 1000000;
static char binary[32];
static int g1 = 0;

static bool isPal(int n) {
	int count = 0;
	short array[6];
	while (n > 0) {
		array[count] = n % 10;
		n /= 10;
		count++;
	}
	int end = count - 1;
	int i;
	for (i = 0; end - i > 0; i++) {
		if (array[i] != array[end])
			return false;
		end--;
	}
	return true;
}

static bool isPal2() {
	g1--;
	for (int i = 0; g1 - i > 0; i++) {
		if (*(binary + i) != *(binary + g1))
			return false;
		g1--;
	}
	return true;
}

static void base2(int n) {
	int count;
	for (count = 0; n > 0; count++) {
		if (n % 2) {
			*(binary + count) = '1';
		} else {
			*(binary + count) = '0';
		}
		g1++;
		n /= 2;
	}
}

int64 Euler_36() {
	int sum = 0;
	int i;
	for (i = 1; i < top; i += 2) {
		base2(i);
		if (isPal(i) && isPal2()) {
			sum += i;
		}
		g1 = 0;
	}
	return (int64) sum;
}
