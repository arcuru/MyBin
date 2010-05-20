#include "Euler.h"

static int count = 0;

void rec(int n, int step)
{
    int num;
    for (num = n + step; num + step <= 100; num++, step++) {
        rec(num, step);
    }
    if (n == 0)
        return;
    count++;
    return;
}

int64 Euler_76()
{
    rec(0, 1);
    return (int64) count;
}
