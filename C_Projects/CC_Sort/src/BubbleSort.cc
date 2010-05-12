//Implementation of Several Sorting Algorithms
#include "CC_Sort.h"

/*
 * Sorts inputed array using BubbleSort Technique
 */
int* BubbleSort(int* d, int size) {
	int k, tmp;
	int i = 1;
	while (i < size) {
		k = i;
		while ((k > 0) && (d[k] < d[k - 1])) {
			tmp = d[k];
			d[k] = d[k - 1];
			d[k - 1] = tmp;
			k--;
		}
		i++;
	}
	return d;
}

int64* BubbleSort(int64* d, int size) {
	int64 tmp;
	int k;
	int i = 1;
	while (i < size) {
		k = i;
		while ((k > 0) && (d[k] < d[k - 1])) {
			tmp = d[k];
			d[k] = d[k - 1];
			d[k - 1] = tmp;
			k--;
		}
		i++;
	}
	return d;
}
