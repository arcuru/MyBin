#include "CC_Euler.h"
#include <stdlib.h>
#include <stdio.h>

int64 Euler_69()
{
	int N=1000000L;

	int* list;
	list=(int*)(malloc)(sizeof(int)*(N));
	if (list == NULL)
	{
		printf("Not enough memory\n");
		return 1;
	}
	int n,s;
	for (n = 0; n <= N; n++) list[n] = n;

	for (n = 2; n <= N; n++)
		if (list[n] == n)
			for (s = 1; s*n <= N; s++)
			{
				list[s*n] = list[s*n] - list[s*n]/n;
			}
	double max=0;
	int maxN=0;
	for (n=2;n<=N;n++)
	{
		double tmp = ((double)n)/list[n];
		if (tmp > max)
		{
			maxN=n;
			max=tmp;
		}
	}
	free(list);
	return (int64)maxN;
}
