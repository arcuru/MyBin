#include "Euler.h"
#include "Primes.h"
#include <stdlib.h>
#include <math.h>

int64_t Euler_87()
{
	int a, b, bb, c, cc;
	int N = 50000000;
	int count = 0;
	char* list = (char*) (calloc)(sizeof(char), N + 1);
	uint32_t* prime = primeListE((int) sqrt(N));
	for (a=0; prime[a]!=0; a++) {
		int total = pow(prime[a], 2);
		if (total >= N)
			break;
		for (b=0; prime[b]!=0; b++) {
			bb = pow(prime[b], 3);
			total += bb;
			if (total >= N) {
				total -= bb;
				break;
			}
			for (c=0; prime[c]!=0; c++) {
				cc = pow(prime[c], 4);
				total += cc;
				if (total >= N) {
					total -= cc;
					break;
				}
				if (0 == list[total]) {
					count++;
					list[total] = 1;
				}
				total -= cc;
			}
			total -= bb;
		}
	}
	free(prime);
	free(list);
	return (int64_t) count;
}

