#include "CC_Euler.h"

static uns64 flip(uns64 n) {
	uns64 out = 0;
	while (n > 0) {
		out *= 10;
		out += n % 10;
		n /= 10;
	}
	return out;
}

int64 Euler_55() {
	int i, dex;
	int count = 0;
	for (i = 1; i < 10000; i++) {
		uns64 n = i;
		int g = 0;
		for (dex = 0; dex < 50; dex++) {

			n += flip(n);
			if (n == flip(n)) {
				g = 1;
				break;
			}
		}
		if (!g)
			count++;
	}
	return (int64) count;
}

