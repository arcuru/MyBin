#include "CC_Euler.h"

int64 Euler_9() {
	int a, b, c;
	a = 1;
	b = 1;
	while (a < 500) {
		while (b < 500) {
			c = 1000 - a - b;
			if (a * a + b * b == c * c) {
				return (int64) (a * b * c);
			}
			b++;
		}
		a++;
		b = 1;
	}
	return 0;
}
