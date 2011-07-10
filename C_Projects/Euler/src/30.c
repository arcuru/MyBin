#include "Euler.h"
#include <math.h>

int64_t Euler_30()
{
    int count = 2;
    int totalcount = 0;
    while (count <= 300000) {
        int sum = 0;
        int n=count;
        while (n!=0) {
            sum+=pow(n%10,5);
            n/=10;
        }
        if (sum == count) {
            totalcount += count;
        }
        count++;
    }
    return (int64_t) totalcount;
}
