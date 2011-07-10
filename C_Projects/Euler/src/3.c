#include "Euler.h"
#include "Primes.h"

int64_t Euler_3()
{
    uint64_t num = 600851475143LL;
    uint64_t* list = primeFactorsE_u64(num);
    int n;
    for (n = 0; list[n]; n++)
        if (!list[n + 1])
            return (int64_t) list[n];
    return 0;
}
