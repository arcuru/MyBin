#include "Euler.h"

static int works(uint64_t n)
{
    int64_t test = (n * n) / 100;
    bool out = true;
    int i;
    for (i = 8; i > 0 && out; i--) {
        out = (test % 10 == i);
        test /= 100;
    }
    return out;
}

int64_t Euler_206()
{
    uint64_t top = 138902662;
    uint64_t bot = 101010101;
    uint64_t ans = 0;
    while (top % 10)
        top--;
    uint64_t i;
    for (i = top - 10; i > bot; i -= 10) {
        if (works(i + 3)) {
            ans = i + 3;
            break;
        }
        if (works(i + 7)) {
            ans = i + 7;
            break;
        }
    }
    return (int64_t) ans * 10;
}
