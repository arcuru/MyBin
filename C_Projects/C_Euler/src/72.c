#include "C_Euler.h"
#include "C_NumberTheory.h"

int64 Euler_72()
{
    int d = 1000000;
    int* philist = EulersTotient(d);
    int64 total = 0;
    int i;
    for (i = 0; i <= d; i++) {
        total += philist[i];
    }
    return total;
}
