#include "Euler.h"
#include "NumberTheory.h"

int64_t Euler_72()
{
    int d = 1000000;
    int* philist = EulersTotient(d);
    int64_t total = 0;
    int i;
    for (i = 0; i <= d; i++) {
        total += philist[i];
    }
    return total;
}
