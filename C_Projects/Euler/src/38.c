#include "Euler.h"
#include "Utils.h"
#include <math.h>

// 0 - Multiple at 1 place
// 1 - Works
// 2 - Keep going
static int helper(int64_t n)
{
    int i, ans = 1;
    int array[10];
    Clear(array, 10);
    while (n > 0) {
        array[n % 10]++;
        n /= 10;
    }
    if (array[0])
        return 0;
    for (i = 1; i < 10; i++) {
        if (array[i] > 1)
            return 0;
        if (array[i] == 0)
            ans = 2;
    }
    return ans;
}

int64_t Euler_38()
{
    int i;
    int64_t max = 0;//918273645;
    for (i = 1; i <= 9876; i++) {
        int64_t total = 0;
        int q;
        for (q = 1; helper(total) == 2; q++) {
            int n = q * i;
            total *= pow(10, Length_int(n));
            total += n;
        }
        if (helper(total) == 1) {
            if (total > max)
                max = total;
        }
    }
    return (int64_t) max;
}
