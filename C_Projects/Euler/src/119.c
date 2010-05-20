#include "Euler.h"
#include "Sort.h"
#include "Utils.h"
#include <stdlib.h>

static int64 Sum(int64 num)
{
    int ans = 0;
    while (num) {
        ans += num % 10;
        num /= 10;
    }
    return ans;
}

int64 Euler_119()
{
    int64 n;
    int index = 0;
    int64* list = (int64*) calloc(sizeof (int64), 50);
    int64 top = 1;
    for (n = 1; n < 55; n++) {
        top *= 2;
    }
    for (n = 2; n < (Length_int(top)*9); n++) {
        int64 current = (int64) n;
        while (current * n > current) {
            current *= n;
            if (n == Sum(current)) {
                list[index++] = current;
            }
        }
    }
    BubbleSort_int64(list, index);
    int count = 0;
    int64 tmp = 0;
    for (n = 0; n < 50; n++) {
        //printf("%lld\n",list[n]);
        if (list[n] > 0)
            count++;
        if (count == 30) {
            tmp = (int64) list[n];
            count++;
        }
    }
    return tmp;
}
