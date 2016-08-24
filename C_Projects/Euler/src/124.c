#include "Euler.h"
#include "Primes.h"
#include <stdlib.h>

static void BubbleSort(int* d, int n, int* thek)
{
    int tmp;
    int i = 1;
    while (i < n) {
        int k;
        k = i;
        while ((k > 0) && (d[k] < d[k - 1])) {
            tmp = d[k];
            d[k] = d[k - 1];
            d[k - 1] = tmp;

            tmp = thek[k];
            thek[k] = thek[k - 1];
            thek[k - 1] = tmp;
            k--;
        }
        i++;
    }
}

int64_t Euler_124()
{
    int N = 100000;
    int* rad = (int*) (malloc) (sizeof (int) * (N + 1));
    int* k = (int*) (malloc) (sizeof (int) * (N + 1));
    uint32_t* primes = primeListE(N);
    rad[0] = 0;
    int i, n;
    for (i = 1; i <= N; i++) {
        int* list = primeFactorsE_inc(i, primes);
        int radval = 1;
        for (n = 0; list[n]; n++) {
            radval *= list[n];
            int s = 0;
            while (list[n + s + 1] == list[n])
                s++;
            n += s;
        }
        rad[i] = radval;
    }
    for (i = 0; i <= N; i++)
        k[i] = i;
    BubbleSort(rad, N + 1, k);
    int64_t ret = k[10000];
    free(rad);
    free(k);
    free(primes);
    return (int64_t) ret;
}


