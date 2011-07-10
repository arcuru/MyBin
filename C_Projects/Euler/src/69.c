#include "Euler.h"
#include "NumberTheory.h"
#include <stdlib.h>
#include <stdio.h>

int64_t Euler_69()
{
    int N = 1000000;
    int* list = EulersTotient(N);
    double max = 0;
    int maxN = 0, n;
    double tmp;
    for (n = 2; n <= N; n++) {
        tmp = ((double) n) / list[n];
        if (tmp > max) {
            maxN = n;
            max = tmp;
        }
    }
    free(list);
    return (int64_t) maxN;
}
