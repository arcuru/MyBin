#include "C_Euler.h"
#include <stdlib.h>

int64 Euler_95()
{
    int N = 1000000;
    int* sums = (int*) calloc(N + 1, sizeof(int));
    long n, s;

    for (n = 1; n <= N>>1; n++)
        for (s = 2; s * n <= N; s++)
            sums[n * s] += n;

    int longest = 0;
    int min = 0;
    for (n = 2; n <= N; n++) {
        if (sums[n] > N)
            continue;
        int len = 1;
        int tmp = n;
        while (sums[tmp] > n && len < 30) {
            tmp = sums[tmp];
            len++;
            if (tmp > N)// || tmp < 1)
                break;
        }
        if (tmp > N)// || tmp < 1)
            continue;
        if (len > longest && sums[tmp] == n) {
            longest = len;
            min = n;
        }
    }
    free(sums);
    return (int64) min;
}

