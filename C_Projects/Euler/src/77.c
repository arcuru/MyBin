#include "Euler.h"
#include "Primes.h"

static int count;

static void rec(int currentTotal, int smallestIndex, int* primes, int n)
{
    int tmpIndex;
    for (tmpIndex = smallestIndex; currentTotal + primes[tmpIndex] < n; tmpIndex++) {
        rec(currentTotal + primes[tmpIndex], tmpIndex, primes, n);
    }
    if (currentTotal + primes[tmpIndex] == n)
        count++;
    return;
}

int64 Euler_77()
{
    int* primes = primeListE(1000000);
    int n;
    for (n = 2; n < 1000000; n++) {
        count = 0;
        rec(0, 0, primes, n);
        if (count > 5000)
            break;
    }

    return (int64) n;
}
