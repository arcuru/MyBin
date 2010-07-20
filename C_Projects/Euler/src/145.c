#include "Euler.h"

static int check(uns64 n)
{
    while (n > 0) {
        if ((n % 10) % 2 == 0)
            return 0;
        n /= 10;
    }
    return 1;
}

static int flip(int n)
{
    int out = 0;
    while (n > 0) {
        out *= 10;
        out += n % 10;
        n /= 10;
    }
    return out;
}

int64 Euler_145()
{
    int i;
    int count = 0;
#pragma omp parallel for
    for (i = 1; i < 100000000; i++) {
        int h = flip(i);
        if (h >= i)
        	if (check(h + i))
		    count++;
    }
    return (int64) (count << 1);
}

