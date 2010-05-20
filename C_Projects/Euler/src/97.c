#include "Euler.h"

int64 Euler_97()
{
    uns64 cut = 10000000000LL;
    uns64 num = 1;
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
    return (int64) num;
}
