#include "C_Euler.h"
#include <stdlib.h>
#include <stdio.h>

int64 Euler_179()
{
    int N = 10000000;
    short* list = (short*) malloc(sizeof(short) * (N+1));//chars don't work
    if (list == NULL) {
        printf("Too Much Memory\n");
        return 1;
    }
    int n, s, i;
    int count = 0;
    list[1]=1;
    for (n = 2; n <= N; n++)
        list[n] = 2;
    //int SQRTN = sqrt(N);
    for (n = 2; n*n <= N; n++) {
        list[n*n]++;
        for (s = n*n+n; s <= N; s += n)
            list[s]+=2;
    }
    i = 1;
    while (i < N) {
        if (list[i] == list[i+1])
            count++;
        i++;
    }
    free(list);
    return (int64) count;
}
