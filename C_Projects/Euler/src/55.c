#include "Euler.h"

static uint64_t flip(uint64_t n)
{
    uint64_t out = 0;
    while (n > 0) {
        out *= 10;
        out += n % 10;
        n /= 10;
    }
    return out;
}

int64_t Euler_55()
{
    int i, dex;
    int count = 0;
    for (i = 1; i < 10000; i++) {
        uint64_t n = i;
        int g = 0;
        for (dex = 0; dex < 50; dex++) {

            n += flip(n);
            if (n == flip(n)) {
                g = 1;
                break;
            }
        }
        if (!g)
            count++;
    }
    return (int64_t) count;
}

