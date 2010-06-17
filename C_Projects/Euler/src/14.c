#include "Euler.h"

int64 Euler_14()
{
	int maxval = 10000000;
    int longest = 0, longval = 0;
    int count;
#pragma omp parallel for
	for (count = maxval-1; count > maxval/2; count-=2) {
        int length = 0;
        uns64 series = count;
        while (series != 1) {
            if (series % 2 == 0) {
                series = series / 2;
            } else {
                series = 3 * series + 1;
            }
            ++length;
        }
        if (length > longest) {
            longest = length;
            longval = count;
        }
    }
    return longval;
}
