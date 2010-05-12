#include "CC_Euler.h"

static int next(int n) {
	int out = 0;
	while (n > 0) {
		out += (n % 10) * (n % 10);
		n /= 10;
	}
	return out;
}

int64 Euler_92() {
	int top = 10000000;
	int array[568];
	int i;
	for (i = 0; i < 568; i++) {
		array[i] = 0;
	}
	int count = 0;
	for (i = 1; i < 568; i++) {
		int n = i;
		while (n != 1 && n != 89) {
			n = next(n);
		}
		if (n == 89) {
			array[i] = 1;
			count++;
		}
	}
	for (i = 568; i < top; i++) {
		if (array[next(i)] == 1) {
			count++;
		}
	}
	return (int64) count;
}
