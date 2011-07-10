#include "Euler.h"
#include <math.h>

static int isPent(int n)
{
    double pent;
    pent = sqrt(24* n + 1) + 1;
    pent /= 6;
    if (pent == (double) (int) pent)
        return 1;
    return 0;
}

int64_t Euler_44()
{
    int pent1 = 1;
    int limit = 10000;
    while (pent1 <= limit) {
        int pent2 = pent1;
        while (pent2 <= limit) {
            int p1 = pent1 * (3* pent1 - 1) / 2;
            int p2 = pent2 * (3* pent2 - 1) / 2;
            int diff = fabs(p1 - p2);
            int sum = p1 + p2;
            if (isPent(diff) && isPent(sum))
                return (int64_t) diff;
            pent2++;
        }
        pent1++;
    }
    return 0;
}
