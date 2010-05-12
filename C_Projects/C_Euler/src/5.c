#include "C_Euler.h"

int64 Euler_5() {
	int count = 0;
	while (1) {
		count += 2 * 2 * 2 * 2 * 3 * 3 * 5 * 7 * 11 * 13 * 17 * 19;
		int num = 2;
		while (num <= 20) {
			if (count % num != 0) {
				break;
			}
			++num;
		}
		if (num == 21) {
			return (int64) count;
		}
	}
}
