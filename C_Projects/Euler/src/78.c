#include "Euler.h"
#include <stdio.h>

static int64_t count;
static int current;

static void rec(int n, int step)
{
    int num;
    for (num = n + step; num + step <= current; num++, step++) {
        rec(num, step);
    }
    if (n == 0)
        return;
    count++;
    return;
}

int64_t Euler_78()
{
    return 0;
    count = 1;
    for (current = 10; count % 1000000 != 0; current++) {
        count = 1;
        rec(0, 1);
        printf("%d\t%lld\n", current, count);
    }

    return (int64_t) current;
}
