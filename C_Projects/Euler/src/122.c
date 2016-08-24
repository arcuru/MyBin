#include "Euler.h"
#include <stdlib.h>

static int min;

static void rec(int currentIndex, int k, int* list)
{
    if (currentIndex >= min) {
        list[currentIndex] = 0;
        return;
    }
    int tmpIndex;
    for (tmpIndex = currentIndex; tmpIndex >= 0 && list[currentIndex]
            + list[tmpIndex] != k; tmpIndex--) {
        if (list[currentIndex] + list[tmpIndex] > k)
            continue;
        list[currentIndex + 1] = list[tmpIndex] + list[currentIndex];
        rec(currentIndex + 1, k, list);
    }
    if (list[currentIndex] + list[tmpIndex] == k) {
        min = currentIndex;
    }
    list[currentIndex] = 0;
    return;
}

int64_t Euler_122()
{
    int* list = (int*) calloc(sizeof(int), 200);
    list[0] = 0;
    list[1] = 1;
    list[2] = 2;
    int total = 1;//by presaving 2, the time is nearly halved (allows you to start at index 2
    int k;
    for (k = 3; k <= 200; k++) {
        //printf("%d\t", k);
        min = 200;
        rec(2, k, list);
        total += min;
        list[2] = 2;
        //printf("%d\n", min);
    }

    free(list);
    return (int64_t) total;
}
