#include "Euler.h"
#include "Primes.h"

int64 Euler_3()
{
    uns64 num = 600851475143LL;
    uns64* list = primeFactorsE_uns64(num);
    int n;
    for (n = 0; list[n]; n++)
        if (!list[n + 1])
            return (int64) list[n];
    return 0;
}
