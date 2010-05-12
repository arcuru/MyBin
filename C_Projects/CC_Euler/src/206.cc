#include "CC_Euler.h"

static bool works(uns64 n) {
	int64 test = (n * n) / 100;
	bool out = true;
	for (int i = 8; i > 0 && out; i--) {
		out = (test % 10 == i);
		test /= 100;
	}
	return out;
}

int64 Euler_206() {
	uns64 top = 138902662;
	uns64 bot = 101010101;
	uns64 ans = 0;
	while (top % 10)
		top--;

	for (uns64 i = top - 10; i > bot; i -= 10) {
		if (works(i + 3)) {
			ans = i + 3;
			break;
		}
		if (works(i + 7)) {
			ans = i + 7;
			break;
		}
	}
	return (int64) ans * 10;
}
