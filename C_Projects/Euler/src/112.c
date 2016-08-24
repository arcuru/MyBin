#include "Euler.h"

static int isBouncy(int n)
{
    int status = 0;
    int a = n % 10;
    n /= 10;
    while (n != 0) {
        int b;
        b = n % 10;
        if (status == 0) {
            if (b > a)
                status = 1;
            else if (b < a)
                status = 2;
        } else if (status == 1) {
            if (b < a)
                return 1;
        } else if (status == 2) {
            if (b > a)
                return 1;
        }
        n /= 10;
        a = b;
    }
    return 0;
}

int64_t Euler_112()
{
    int i, total = 0;
    for (i = 1; 1; i++) {
        if (isBouncy(i)) {
            total++;
        }
        if (i % 100 == 0) {
            if ((i / 100) * 99 == total) {
                return (int64_t) i;
            }
        }
    }
}

