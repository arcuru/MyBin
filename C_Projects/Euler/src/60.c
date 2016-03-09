#include "Euler.h"
#include "Primes.h"
#include "Utils.h"
#include <math.h>
#include <stdlib.h>

static int min = 1000000000;
static int minlist[6];
static int N = 10000;
static unsigned char* PIndex;

static int Concatenate(int n, int h)
{
    int num1 = n * pow(10, Length_int(h)) + h;
    int num2 = h * pow(10, Length_int(n)) + n;
    if (!PIndex[num1])
        return false;
    else if (!PIndex[num2])
        return false;
    return true;
}

static void rec(int* list, int place, uint32_t* primelist, int index)
{
    if (place == 6) {
        int total = 0;
        int i;
        for (i = 1; i < 6; i++)
            total += list[i];
        if (total < min) {
            min = total;
            int n;
            for (n = 1; n < 6; n++) {
                minlist[n] = list[n];
            }
        }
        return;
    }
    int i;
    for (i = index; primelist[i]; i++) {
        list[place] = primelist[i];
        int works = true;
        int n;
        for (n = 1; n < place; n++) {
            if (!Concatenate(list[n], list[place])) {
                works = false;
                break;
            }
        }
        if (works)
            rec(list, place + 1, primelist, i + 1);
    }
    return;
}

int64_t Euler_60()
{
    unsigned char* primes = SieveEratosthenes(N * N);
    uint32_t* primelist = primeListE_inc(N, primes);
    PIndex = primeIndexListE_inc(N * N, primes);
    int list[6];
    rec(list, 1, primelist, 0);
	free(PIndex);
    return (int64_t) min; //13	5197	5701	6733	8389
}
