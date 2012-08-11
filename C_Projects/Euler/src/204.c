#include "Euler.h"
#include "Primes.h"
#include "stdlib.h"

static uint32_t* list;
static int total = 1;

static void rec(int64_t current, int n, int N)
{
    int i;
    for (i = n; list[i]; i++) {
        if (current * list[i] < N) {
            rec(current * list[i], i, N);
            continue;
        }
        break;
    }
    total++;
}

int64_t Euler_204()
{
    int N = 1000000000;
    int type = 100;
    list = primeListE(type);
    rec(1, 0, N);
    free(list);
	return (int64_t) total;
}

