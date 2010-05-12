#include "CC_Euler.h"

static uns64 last(int num,uns64 cut)
{
	uns64 n=1;
	int c;
	for (c=1;c<=num;c++)
		n=(n*num)%cut;
	return n;
}

int64 Euler_48()
{
	uns64 cut = 10000000000LL;
	uns64 total=0;
	int i;
	for (i=1;i<=1000;i++)
		total=(total+last(i,cut))%cut;
	return (int64)total;
}
