#include "Euler.h"
#include "NumberTheory.h"
#include "Primes.h"

int64_t Euler_214()
{
    int N = 40000000;
    int* list = EulersTotient(N);
    uint64_t count = 0;
    int n,s;
    for (n = 3; n <= N; n+=2) {
        if (list[n] != n-1) continue;
        int tmp=n;
        for (s=2; s<26; s++) {
            tmp=list[tmp];
            if (tmp==1) {
                if (s==25) count+=n;
                break;
            }
        }
    }
    return (int64_t)count;
}
