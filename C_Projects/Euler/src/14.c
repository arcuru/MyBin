#include "Euler.h"

int64_t Euler_14()
{
	const int maxval = 1000000;
	int longest = 0, longval = 0;
	int count;
	int16_t cache[maxval];
	//#pragma omp parallel for
	for (count = 1; count <= maxval; ++count) {
		int length = 0;
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
		if (length > longest) {
			longest = length;
			longval = count;
		}
	}
	// Longest is 524
	return longval;
}
