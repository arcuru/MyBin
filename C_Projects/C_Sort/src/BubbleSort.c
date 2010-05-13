//Implementation of Several Sorting Algorithms
#include "C_Sort.h"
#include <stdio.h>
#include <pthread.h>

/*
 * Sorts inputed array using BubbleSort Technique
 */
int* BubbleSort(int* d, int size)
{
    int k, tmp;
    int i = 1;
    while (i < size) {
        k = i;
        while ((k > 0) && (d[k] < d[k - 1])) {
            tmp = d[k];
            d[k] = d[k - 1];
            d[k - 1] = tmp;
            k--;
        }
        i++;
    }
    return d;
}

int64* BubbleSort_int64(int64* d, int size)
{
    int64 tmp;
    int k;
    int i = 1;
    while (i < size) {
        k = i;
        while ((k > 0) && (d[k] < d[k - 1])) {
            tmp = d[k];
            d[k] = d[k - 1];
            d[k - 1] = tmp;
            k--;
        }
        i++;
    }
    return d;
}

typedef struct {
    int* Array;
    int length;
    int threadid;
} BSortStruct;


static void *BubbleSort_P(void* input)
{
    BSortStruct* BStruct = (BSortStruct*) input;
    int* d = (*BStruct).Array;
    int size = (*BStruct).length;
    int k, tmp;
    int i = 1;
    while (i < size) {
        k = i;
        while ((k > 0) && (d[k] < d[k - 1])) {
            tmp = d[k];
            d[k] = d[k - 1];
            d[k - 1] = tmp;
            k--;
        }
        i++;
    }
    pthread_exit(NULL);
}

// Here is the main sorting function.
// Array d is the input array to be sorted,
// n is the size of d
int* ParallelBubbleSort(int* d, int n, int* e)
{
    int nthreads = 8;
    int length = n / nthreads;
    int i,index;//index variable

    pthread_t thread[nthreads];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    BSortStruct BSort[nthreads];

    for (i = 0; i < nthreads; ++i) {
        BSort[i].Array = &d[i * length];
        if (i == nthreads - 1)
            BSort[i].length = n - (i * length);
        else
            BSort[i].length = length;
        BSort[i].threadid = i;
        pthread_create(&thread[i], &attr, BubbleSort_P, (void*) &BSort[i]);
    }
    void* status;
    for (i = 0; i < nthreads; i++) {
        pthread_join(thread[i], &status);
    }

    int dex[nthreads];
    for (i = 0; i < nthreads; i++) {
        dex[i] = 0;
    }

    for (i = 0; i < n; i++) {
        int min = 1 << 30;
        int smallestthread=-1;
        for (index = 0; index < nthreads; index++) {
            if (dex[index] == length) {
                continue;
            }
            if (d[index * length + dex[index]] < min) {
                min = d[index * length + dex[index]];
                smallestthread = index;
            }
        }
        e[i] = min;
        dex[smallestthread]++;
    }
    return e;
}
