#include "CC_Euler.h"

static int isAbundant(int num) {
	int sum = 1;
	int f = 2;
	while (f * f <= num) {
		if (f * f == num)
			sum += f;
		else if (num % f == 0)
			sum += f + (num / f);
		if (num < sum)
			return 1;
		f++;
	}
	return 0;
}

int64 Euler_23() {
	int limit = 28123;
	int list[20000];
	int count;
	int place = 0;
	for (count = 1; count <= limit; count++) {
		if (isAbundant(count)) {
			list[place] = count;
			place++;
		}
	}
	int total[28123];
	int index = 0;
	while (list[index]) {
		int dex = index;
		while (list[index] + list[dex] <= limit) {
			total[list[index] + list[dex]]++;
			dex++;
		}
		index++;
	}
	int queen = 1;
	int sum = 0;
	while (queen <= limit) {
		if (total[queen] == 0) {
			sum += queen;
		}
		queen++;
	}
	return (int64) sum;
}
