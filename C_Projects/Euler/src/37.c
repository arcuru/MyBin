#include "Euler.h"
#include "Primes.h"
#include "Utils.h"
#include <math.h>

int64 Euler_37()
{
    unsigned char* prime = SieveEratosthenes(1000000);
    int candidate=11;
    int sum=0;
    int eleventy=0;
    while ( eleventy < 11 ) {
        if ( isPrimeE(candidate,prime) ) {
            int check=1;
            int truth=1;
            int digits=Length_int(candidate);
            int holdright=candidate;
            int holdleft=candidate;
            while ( check < digits ) {
                holdright=holdright/10;
                holdleft=holdleft%(int)pow(10,digits-check);
                if ( !isPrimeE(holdright,prime) || !isPrimeE(holdleft,prime) ) {
                    truth=0;
                    break;
                }
                check++;
            }
            if ( truth ) {
                eleventy++;
                sum+=candidate;
            }
        }
        candidate+=2;
    }
    return (int64)sum;
}
