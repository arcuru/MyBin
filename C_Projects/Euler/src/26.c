#include "Euler.h"

int64_t Euler_26()
{
    int n, i, maxlen = 0, maxn = 0;
    for (n = 2; n <= 1000; n++) {
        int rest = 1;
        int r0;
        for (i = 0; i < n; i++)
            rest = (rest * 10) % n;
        r0 = rest;
        int len = 0;
        do {
            rest = (rest * 10) % n;
            len++;
        } while (rest != r0);
        if (len > maxlen) {
            maxn = n;
            maxlen = len;
        }
    }
    return (int64_t) maxn;
}
