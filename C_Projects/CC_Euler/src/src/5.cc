#include "CC_Euler.h"

int64 Euler_5() {
	int count = 0;
	while (1) {
		count += 20;
		int num = 2;
		while (num <= 20) {
			if (count % num) {
				break;
			}
			if (num == 20) {
				return (int64) count;
			}
			num++;
		}
	}
}
