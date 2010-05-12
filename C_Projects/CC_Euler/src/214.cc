#include "CC_Euler.h"
#include "CC_NumberTheory.h"
#include "CC_Primes.h"

int64 Euler_214()
{
	int N = 40000000;
	int* list = EulersTotient(N);
	uns64 count = 0;
	int n,s;
	for (n = 3; n <= N; n+=2)
	{
		if (list[n] != n-1) continue;
		int tmp=n;
		for (s=2;s<26;s++)
		{
			tmp=list[tmp];
			if (tmp==1)
			{
				if (s==25) count+=n;
				break;
			}
		}
	}
	return (int64)count;
}
