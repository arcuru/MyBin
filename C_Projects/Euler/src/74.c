#include "Euler.h"
#include "NumberTheory.h"
#include <string.h>

static bool check(int n, int* list)
{
    int i;
    for (i = 0; i < 60 && list[i] > 0; i++)
        if (n == list[i])
            return true;
    return false;
}

int64_t Euler_74()
{
    int array[10];
    int list[60];
    int i;
    for (i = 0; i < 10; i++)
        array[i] = Factorial(i);
    int total = 0;
#pragma omp parallel for
    for (i = 1; i < 1000000; i++) {
        int dex;
        list[0] = i;
        for (dex = 1; dex < 60; dex++) {
            int a = 0;
            int tmp = list[dex - 1];
            while (tmp > 0) {
                a += array[tmp % 10];
                tmp /= 10;
            }
            if (check(a, list))
                break;
            list[dex] = a;
        }
        if (dex == 60)
            total++;
        memset(list, 0, 60*sizeof(int));
    }
    return (int64_t) total;
}

