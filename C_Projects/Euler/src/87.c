#include "Euler.h"
#include "Primes.h"
#include <stdlib.h>
#include <math.h>

static int count = 0;

static void rec(int current, int exp, int* prime, char* list)
{
    if (exp > 4)
        return;
    int i;
    for (i = 0; (current + pow(prime[i], exp)) < 50000000 && prime[i]; i++) {
        if (exp == 4 && !list[(int) (current + pow(prime[i], exp))]) {
            count++;
            list[(int) (current + pow(prime[i], exp))] = 1;
            continue;
        }
        rec(current + pow(prime[i], exp), exp + 1, prime, list);
    }
}

int64 Euler_87()
{
    char* list = (char*) (malloc)(sizeof(char) * 50000001);
    int N = 50000000;
    int* prime = primeListE((int) sqrt(N));
    rec(0, 2, prime, list);
    free(prime);
    return (int64) count;
}

