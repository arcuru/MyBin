#include "Euler.h"

static uint64_t last(int num,uint64_t cut)
{
    uint64_t n=1;
    int c;
    for (c=1; c<=num; c++)
        n=(n*num)%cut;
    return n;
}

int64_t Euler_48()
{
    uint64_t cut = 10000000000LL;
    uint64_t total=0;
    int i;
    for (i=1; i<=1000; i++)
        total=(total+last(i,cut))%cut;
    return (int64_t)total;
}
