#include "Euler.h"
#include <stdlib.h>

int64 Euler_39()
{
    int a, b, c, check, csq, val, maxval = 0, maxcount = 0;
    int* plist = (int*) malloc(sizeof(int) * 1000);
    for (check = 0; check <= 1000; check++) {
        plist[check] = 0;
    }
    for (c = 1; c < 500; c++) {
        csq = c * c;
        for (a = 1; a < c; a++) {
            for (b = 1; b < (1000 - c - a); b++) {
                val = (a * a) + (b * b);
                if (a + b + c > 999) {
                    break;
                } else if (val < csq) {
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

    for (check = 0; check <= 1000; check++) {
        if (plist[check] > maxcount) {
            maxval = check;
            maxcount = plist[check];
        }
    }
    free(plist);
    return (int64) maxval;
}
