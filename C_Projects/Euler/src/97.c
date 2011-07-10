#include "Euler.h"

int64_t Euler_97()
{
    uint64_t cut = 10000000000LL;
    uint64_t num = 1;
    int top = 7830457;
    int count = 0;
    int maxshift = 30;
    while (count < top) {
        if (top - count < maxshift) {
            num <<= (top - count);
            count += top - count;
        } else {
            num <<= maxshift;
            count += maxshift;
        }
        num %= cut;
    }
    num *= 28433;
    num %= cut;
    num++;
    return (int64_t) num;
}
