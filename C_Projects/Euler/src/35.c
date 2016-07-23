#include "Euler.h"
#include "Primes.h"

static int rotate(int n, int len)
{
    int end = n % 10;
    n /= 10;
    n += end * len;
    return n;
}

int64_t Euler_35()
{
    int N = 1000000;
    unsigned char* prime = SieveEratosthenes(N);
    int count = 0;
    int i;
    for (i = 0; i < N; i++) {
        if (!isPrimeE(i, prime))
            continue;
        
        int len = 10;
        while (len < i)
            len *= 10;
        len /= 10;

        int n = rotate(i, len);
        while (n != i) {
            if (!isPrimeE(n, prime)) {
                break;
            }
            n = rotate(n, len);
        }
        if (n != i) {
            continue;
        }
        count++;
    }
    return (int64_t) count;
}

