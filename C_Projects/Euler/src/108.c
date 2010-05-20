#include "Euler.h"

int64 Euler_108()
{
    int size = 0;
    double y, n;
    n = 1000;
    while (size <= 995) {
        n += 10;
        size = 0;
        double num = n * n + n;
        int den = 1;
        while (den <= n) {
            y = num / den;
            if (y == (int) y) {
                size++;
            }
            num += n;
            den++;
        }
    }
    return (int64) n;
}
