#include "Euler.h"

static void arrayVal(int n, int d[])
{
    int i;
    for (i = 0; i < 10; i++) {
        d[i] = 0;
    }
    while (n > 0) {
        d[n % 10]++;
        n /= 10;
    }
}

static int isEq(int* a, int* d)
{
    int dex;
    for (dex = 0; dex < 10; dex++) {
        if (a[dex] != d[dex]) {
            return 1;
        }
    }
    return 0;
}

int64_t Euler_52()
{
    int d[10];
    int num = 1000;
    int bignum = 10000;
    while (1 == 1) {
        while (num <= bignum / 6) {
            num++;
            int a[10];
            arrayVal(num, a);
            arrayVal(num * 2, d);
            if (isEq(a, d))
                continue;

            arrayVal(num * 3, d);
            if (isEq(a, d))
                continue;

            arrayVal(num * 4, d);
            if (isEq(a, d))
                continue;

            arrayVal(num * 5, d);
            if (isEq(a, d))
                continue;

            arrayVal(num * 6, d);
            if (isEq(a, d))
                continue;

            return (int64_t) num;
        }
        num = bignum;
        bignum *= 10;
    }
}
