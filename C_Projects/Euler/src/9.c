#include "Euler.h"

int64_t Euler_9()
{
    int a, b, c;
	for ( a = 1; a < 1000; a++ )
		for ( b = a; (c = 1000 - b - a) > b; b++ )
            if (a * a + b * b == c * c)
                return (int64_t) (a*b*c);
    return 0;
}
