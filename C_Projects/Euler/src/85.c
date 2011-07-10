#include "Euler.h"
#include <stdlib.h>

int64_t Euler_85()
{
    int lowarea = 2000000;
    int lowtotal = 1000000000;
    int top = 2000000;
    int limit = 1000;
    int w, h;
    for (w = 1; w <= limit; w++) {
        for (h = w; h <= limit; h++) {
            int total = 0;
            (!(w & 1)) ? (total = (w >> 1) * (w + 1)) : (total = ((w >> 1) + 1)
                    * w);
            int sum = 0;
            if (!(h & 1))
                sum = (h >> 1) * (h + 1);
            else
                sum = ((h >> 1) + 1) * h;
            total *= sum;
            if (abs(total - top) < lowtotal) {
                lowarea = w * h;
                lowtotal = abs(total - top);
            }
        }
    }
    return (int64_t) lowarea;
}
