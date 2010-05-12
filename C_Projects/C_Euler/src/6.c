#include "C_Euler.h"

int64 Euler_6()
{
    int sumsq=0;
    int sqsum=0;
    int count;
    for (count =1; count<= 100; count++) {
        sumsq=sumsq+(count*count);
        sqsum=sqsum+count;
    }
    sqsum=sqsum*sqsum;
    return (int64)(sqsum-sumsq);
}
