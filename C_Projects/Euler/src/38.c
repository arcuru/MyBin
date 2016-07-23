#include "Euler.h"
#include <stdlib.h>
#include <string.h>

// 0 - Multiple at 1 place
// 1 - Works
// 2 - Keep going
static int check(int* arr)
{
    int i, ans=1;
    if (arr[0])
        return 0;
    for (i = 1; i < 10; i++) {
        if (arr[i] > 1)
            return 0;
        if (arr[i] == 0)
            ans = 2;
    }
    return ans;
}

int64_t Euler_38()
{
    int i;
    int64_t max = 0;//918273645;
    int* arr = calloc(10, sizeof(int));
    for (i = 1; i <= 9876; i++) {
        int64_t total = 0;
        int q;
        for (q = 1; check(arr) == 2; q++) {
            int n = q * i;
            while (n > 0) {
                arr[n % 10]++;
                total *= 10;
                n /= 10;
            }
            total += q * i;
        }
        if (check(arr) == 1) {
            if (total > max)
                max = total;
        }
        memset(arr, 0, 10*sizeof(int));
    }
    free(arr);
    return (int64_t) max;
}
