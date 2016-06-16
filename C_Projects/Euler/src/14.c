#include "Euler.h"
#include <stdlib.h>

int64_t Euler_14()
{
	const int maxval = 1000000;
	int longest = 0, longval = 0;
	int count;
	int16_t* cache = (int16_t*) calloc(sizeof(int16_t), maxval + 1);
	for (count = 1; count <= maxval; ++count) {
		// Caching results yields a lot of speedup
		int length = cache[count];
		if (length == 0) {
			int64_t series = count;
			while (series != 1) {
				if ( series < count ) {
					length += cache[series];
					break;
				}
				if (series % 2 == 0) {
					series = series / 2;
					++length;
				} else {
					series = 3 * series + 1;
					series /= 2;
					length += 2;
				}
			}
			cache[count] = length;
			int tmp = count;
			int tmplen = length;
			while (tmp < maxval / 2) {
				tmp *= 2;
				cache[tmp] = ++tmplen;
			}
		}
		if (length > longest) {
			longest = length;
			longval = count;
		}
	}
	// Longest is 524 for <1,000,000
	free( cache );
	return longval;
}
