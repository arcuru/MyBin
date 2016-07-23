#include "Euler.h"
#include "Utils.h"
#include <stdlib.h>

static int64_t Sum(int64_t num)
{
    int ans = 0;
    while (num) {
        ans += num % 10;
        num /= 10;
    }
    return ans;
}

static int compare_int64(const void* lhs, const void* rhs)
{
    return ((int64_t)lhs > (int64_t)rhs);
}

int64_t Euler_119()
{
    int64_t n;
    int index = 0;
    int64_t* list = (int64_t*) calloc(sizeof (int64_t), 50);
    int64_t top = 1;
    for (n = 1; n < 55; n++) {
        top *= 2;
    }
    for (n = 2; n < (Length_s64(top)*9); n++) {
        int64_t current = (int64_t) n;
        while (current * n > current) {
            current *= n;
            if (n == Sum(current)) {
                list[index++] = current;
            }
        }
    }
    qsort(list, index, sizeof(list[0]), &compare_int64);
    int count = 0;
    int64_t tmp = 0;
    for (n = 0; n < 50; n++) {
        //printf("%lld\n",list[n]);
        if (list[n] > 0)
            count++;
        if (count == 30) {
            tmp = (int64_t) list[n];
            count++;
        }
    }
    free(list);
    return tmp;
}
