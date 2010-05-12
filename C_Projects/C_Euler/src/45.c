#include "C_Euler.h"
#include <math.h>

int64 Euler_45()
{
    int i;
    for ( i=1; i<50000; i++) {
        unsigned long long int hex;
        hex=i*(2*i-1);
        double pent;
        pent=sqrt(24*hex+1)+1;
        pent/=6;
        if (pent == (double)(int)pent && hex>40755)
            return (int64)hex;
    }
    return 0;
}
