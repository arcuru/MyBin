#include "Euler.h"
#include <math.h>

int64_t Euler_94()
{
    int i;
    int64_t answer=0;
#pragma omp parallel for
    for (i=-1; i<=1; i+=2) {
        int a;
        for (a = 3 ;(a*3)+i<=1000000000; a += 2) {
            int c = a+i;
            int64_t p = ((a * 3) + i) / 2; //p is half the perimeters
            int64_t t = sqrt(p) * sqrt(p-c);
            if (t * t == p * (p-c))
                answer += (p * 2);
        }
    }
    return answer;
}
