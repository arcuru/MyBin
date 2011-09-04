#include "Euler.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int64_t Euler_75()
{
    //Remove for doing the problem
    return 0;
    //
    int TOP = 2000000;
    int* list = (int*) calloc(TOP + 1, sizeof(int));
    //int64_t* sqlist = (int64_t*) malloc(sizeof(int64_t) * TOP >> 1);
    int n;
    //for (n = 0; n <= TOP >> 1; n++) {
    //	sqlist[n] = n * n;
    //}
    int64_t a, b, c;
    int T2 = (int) TOP >> 1;
    //long double sqrt2 = sqrt(2);
    for (a = 1; a < T2; a++) {
        b = a;
        int64_t a2 = a * a;
        c = (int) sqrt(2 * a * a);
        c--;
        int64_t b2 = a2, c2 = c * c;
        while ((a + b + c) <= TOP) {
            if (c2 < a2 + b2) {
                c2 += 2 * c + 1;
                c++;
            } else if (c2 > a2 + b2) {
                b2 += 2 * b + 1;
                b++;
            } else {
                list[c + a + b]++;
                b2 += 2 * b + 1;
                b++;
            }
        }
        printf("%jd\n", a);
    }
    int64_t count = 0;
    for (n = 1; n <= TOP; n++)
        if (list[n] == 1)
            count++;
    free(list);
    return count;
}
