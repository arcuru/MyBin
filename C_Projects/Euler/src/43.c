#include "Euler.h"
#include <stdio.h>

static uint64_t total = 0;
static int array[11];
static uint64_t number = 0;

static void check(uint64_t n)
{
    int primes[7];
    primes[0] = 2;
    primes[1] = 3;
    primes[2] = 5;
    primes[3] = 7;
    primes[4] = 11;
    primes[5] = 13;
    primes[6] = 17;
    int i;
    for (i = 6; i >= 0; i--) {
        if ((n % 1000) % primes[i] != 0)
            return;
        n /= 10;
    }
    total += number;
}

static void doit(int n)
{
    int count = 1;
    while (count <= n) {
        int place = 0;
        int hold = 0;
        int dex;
        for (dex = 0; place < count; dex++) {
            if (array[dex] == 0) {
                place++;
                hold = dex;
            }
        }
        array[hold] = 1;
        number *= 10;
        number += hold;
        if (n == 1) {
            check(number);
        }
        doit(n - 1);
        array[hold] = 0;
        number /= 10;
        count++;
    }
    return;
}



int64_t Euler_43()
{
    doit(10);
    return total;
}




