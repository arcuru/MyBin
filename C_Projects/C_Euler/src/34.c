#include "C_Euler.h"
#include "C_Utils.h"

static int sumFac(int n)
{
    int sum = 0;
    while (n > 0) {
        int k = n % 10;
        n /= 10;
        int fac = 1;
        while (k > 1) {
            fac *= k;
            k--;
        }
        sum += fac;
    }
    return sum;
}

int64 Euler_34()
{
    int p = 3;
    int total = 0;
    while (p < Length_int(p) * sumFac(9)) {
        if (sumFac(p) == p)
            total += p;
        p++;
    }
    return (int64) total;
}
