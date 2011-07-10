#include "Euler.h"

int64_t Euler_1()
{
    int count;
    int sum = 0;
    for (count = 1; count < 1000; count++) {
        if ((count % 3 == 0) || (count % 5 == 0))
            sum += count;
    }
    return (int64_t) sum;
}
