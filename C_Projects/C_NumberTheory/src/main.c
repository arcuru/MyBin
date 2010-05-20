#include "C_NumberTheory.h"
//#include "CC_Primes.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

//Creates array of totient values
//Each value at Index is the totient of Index

int* EulersTotient(int N)
{
    int* list = (int*) (malloc)(sizeof(int) * (N + 1));
    if (!list)
    {
        printf("Not enough memory\n");
        return NULL;
    }
    int n, s;
    for (n = 1; n <= N; n += 2) //Fill odds in array
        list[n] = n - 1;
    for (n = 2; n <= N; n += 2) //Fill evens in array (pre calculating with 2's)
        list[n] = (n >> 1);
    for (n = 3; n <= N; n += 2)
        if (list[n] == n - 1) //Checks for primality
            for (s = 2 * n; s <= N; s += n)
                list[s] = list[s] - list[s] / n;

    return list;
}

//Euclid's formula for GCD
int GCD(int m, int n)
{
    int r;
    while (1)
    {
        r = m % n;
        if (r==0)
        {
            return n;
        }
        m = n;
        n = r;
    }
    return 0;
}

//Returns a^b
int64_t Power(int64_t a, int64_t b)
{
    if (b < 0)
        return -1;
    if (!b)
        return 1;
    if (!a)
        return 0;
    if (!(b & 1))
        return Power(a * a, b >> 1);
    else
        return a * Power(a * a, b >> 1);
    return 0;
}

double intpow(double a, int b)
{
    if (b < 0)
    {
        a = 1.0 / a;
        b = -b;
    }
    double result = 1.0;
    while (b)
    {
        if (b & 1)
            result *= a;
        a *= a;
        b >>= 1;
    }
    return result;
}

int Factorial(int n)
{
    int out = 1;
    while (n)
    {
        out *= n;
        --n;
    }
    return out;
}
