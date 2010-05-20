#include "Euler.h"

int64 Euler_14()
{
    int longest = 0;
    int longval = 0;
    int length;
    int count = 999999;
    while (count > 500000) {
        length = 0;
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
        count -= 2;
    }
    return longval;
}
