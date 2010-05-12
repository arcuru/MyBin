#include "CC_Euler.h"
#include <stdlib.h>
#include <math.h>

static bool isPal(int* num,int size) {
	int n;
	for (n = 0; n <= (size >> 1); n++) {
		if (num[n] != num[size - n])
			return false;
	}
	return true;
}

static int incrNum(int* num,int size) {
	int n;
	for (n=0;1;n++) {
		if (num[n]==9) {
			num[n]=0;
			continue;
		}
		num[n]++;
		if (n>size)
			size++;
		break;
	}
	return size;
}

int64 Euler_125() {
	int N = 100000000;
	int SQRTN = (int)sqrt(N);
	int* SQarray = (int*)malloc(sizeof(int)*SQRTN);
	int* num = (int*)calloc(12,sizeof(int));
	int64 total=0;
	int n;
	for (n = 0; n <= SQRTN; n++) {
		SQarray[n] = n * n;
	}
	int size=0;
	for (n = 1; n <= N; n++) {
		size=incrNum(num,size);
		if (!isPal(num,size))
			continue;
		int sum=0;
		int first=1;
		int q;
		for (q=1;q<=SQRTN && SQarray[q]<n;q++) {
			sum+=SQarray[q];
			while (sum>n) {
				sum-=SQarray[first];
				first++;
			}
			if (sum==n) {
				total+=n;
				break;
			}
		}
	}
	free(SQarray);
	free(num);
	return total;
}
