#include "Euler.h"
#include "Primes.h"
#include <stdlib.h>

static int Number[8];
static int64_t g_min = 1000000;
static unsigned char* Primes;
static int Array[8];

static void Check()
{
    int tmp[7];
    int n, ind = 1;
    for (n = 0; n < 7; n++) {
        tmp[n] = Array[n];
    }
    int var[7];
    for (n = 0; n < 7; n++)
        if (Array[n] > 9) {
            var[ind] = n;
            ind++;
        }
    if (ind == 1)
        return;
    int val = 0;
    int min = 1000000;
    int count = 0;
    //printf("hihi\n");
    while (1) {
        int ind2 = 1;
        //printf("%d\n",val);
        while (ind2 < ind) {
            tmp[var[ind2]] = val;
            ind2++;
        }
        int num = 0;
        //printf("val\n");
        for (n = 6; n; n--) {
            num *= 10;
            num += tmp[n];
        }
        //printf("%d\n",num);

        if (!Primes[num])
            count++;
        else if (num < min)
            min = num;
        else if (num > min * 10)
            break;
        val++;
        if (count > 2)
            return;
        if (val == 10) {
            if (count == 2) {
                if (min < g_min)
                    g_min = (int64_t) min;
                return;
            } else {
                //printf("more than 8\n");
                return;
            }
        }
    }
}

static void Filter()
{
    int n;
    for (n = 0; n < 7; n++) {
        Array[n] = Number[n];
    }
    int end = FALSE;
    while (1) {
        for (n = 1; n <= 7; n++) {
            if (n == 7) {
                end = TRUE;
                break;
            }
            if (Array[n] > 9)
                continue;
            Array[n]++;
            if (Array[n] > 9) {
                Array[n] = 0;
                continue;
            } else
                break;
        }
        if (end)
            break;
        //printf("hi\n");
        Check();
    }
}

static void Rec(int index)
{
    if (index == 7)
        return;
    Filter();
    Rec(index + 1);
    Number[index] = 100;
    Filter();
    Rec(index + 1);
    Number[index] = 0;
}

int64_t Euler_51()
{
    int n;
    for (n = 0; n < 8; n++)
        Number[n] = 0;
    Primes = primeIndexListE(1000000);
    Rec(2);
	free(Primes);
    return g_min;
}
