#include "Euler.h"

int64_t Euler_2()
{
    int sum = 0;
    int a = 1;
    int b = 2;
    while (b < 4000000) {
        if (b % 2 == 0) {
            sum += b;
        }
        int tmp = a;
        a = b;
        b = tmp + b;
    }
    return (int64_t) sum;
}
