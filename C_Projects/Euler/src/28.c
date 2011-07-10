#include "Euler.h"

int64_t Euler_28()
{
    const int size = 1001;
    int total=1;
    int n;
    for (n=3; n<=size; n+=2) {
        total+=(4*n*n)-(6*n)+6;
    }
    return (int64_t)total;
}

