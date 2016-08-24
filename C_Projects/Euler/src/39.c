#include "Euler.h"
#include <stdlib.h>

int64_t Euler_39()
{
    int N = 1001;
    int a, b, c, check, val, maxval = 0, maxcount = 0;
    int* plist = (int*) calloc(sizeof(int), N);
    for (c = 1; 2 * c < N; c++) {
        int csq = c * c;
        for (a = 1; a < c; a++) {
            for (b = 1; b < (N - c - a); b++) {
                val = (a * a) + (b * b);
                if (val < csq) {
                    continue;
                } else if (val > csq) {
                    break;
                } else if (val == csq) {
                    plist[a + b + c]++;
                    break;
                }
            }
        }
    }

    for (check = 0; check < N; check++) {
        if (plist[check] > maxcount) {
            maxval = check;
            maxcount = plist[check];
        }
    }
    free(plist);
    return (int64_t) maxval;
}
