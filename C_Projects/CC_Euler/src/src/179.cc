#include "CC_Euler.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int64 Euler_179() {
	int N = 10000000;
	short* list = (short*) malloc(sizeof(short) * N+1);
	if (list == NULL) {
		printf("Too Much Memory\n");
		return 1;
	}
	long n, s, i;
	int count = 0;
	list[1]=1;
	for (n = 2; n <= N; n++)
		list[n] = 2;
	int SQRTN = sqrt(N);
	for (n = 2; n <= SQRTN; n++){
		//list[n]++;
		list[n*n]++;
		for (s = n*n+n; s <= N; s += n)
			list[s]+=2;
	}
	i = 1;
	while (i < N) {
		if (list[i] == list[i+1])
			count++;
		i++;
	}
	free(list);
	return (int64) count;
}
