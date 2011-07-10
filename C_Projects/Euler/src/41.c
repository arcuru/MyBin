#include "Euler.h"
#include "Primes.h"

static int number = 0;
static int array[10];
static int length;

static int doit(int n)
{
    int count = 1;
    while (count <= n) {
        int place = 1;
        int hold = 0;
        int dex;
        for (dex = length; place <= count; dex--) {
            if (array[dex] == 0) {
                place++;
                hold = dex;
            }
        }
        array[hold] = 1;
        number *= 10;
        number += hold;
        if (n == 1) {
            if (isPrime(number)) {
                return number;
            }
        }
        int tmp;
        tmp = doit(n - 1);
        if (isPrime(tmp))
            return tmp;
        array[hold] = 0;
        number /= 10;
        count++;
    }
    return 0;
}

int64_t Euler_41()
{
    for (length = 7; length > 1; length--) {
        int tmp;
        tmp = doit(length);
        if (isPrime(tmp))
            return (int64_t) tmp;
    }
    return 0;
}
