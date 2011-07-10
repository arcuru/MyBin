#include "Euler.h"

int64_t Euler_9()
{
    int a, b, c;
    a = 1;
    while (a < 1000)
    {
        b=a;
        while ((c = 1000 - b - a) > b)
        {
            if (a * a + b * b == c * c)
            {
                return (int64_t) (a*b*c);
            }
            b++;
        }
        a++;
    }
    return 0;
}
