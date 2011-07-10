#include "Euler.h"
#include <stdlib.h>
#include <math.h>

int64_t Euler_211()
{
    uint64_t N = 64000000;
    uint64_t* list = (uint64_t*) calloc(N, sizeof (uint64_t));
    if (!list)
        return 0;
    uint64_t n, s, q;
    for (n = 1; n < N; n++) {
        s = n;
        q = n * n;
        while (s < N) {
            list[s] += q;
            s += n;
        }
    }
    uint64_t total = 0;
    for (n = 1; n < N; n++) {
        if ((double) (int) sqrt(list[n]) == sqrt(list[n]))
            total += n;
    }
    free(list);
    return (int64_t) total;
}
