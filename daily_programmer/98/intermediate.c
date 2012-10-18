#include <stdint.h>
#include <stdio.h>

/** Multiple Cycle
 *
 *  @arg lim Number to count up to
 *  @arg array Array of numbers to use in counting
 *  @arg len Length of array
 *  @return Number of cycles necessary to reach or exceed lim
 */
uint32_t multiple_cycle(uint32_t lim, uint32_t* array, size_t len)
{
	uint32_t count = 0;
	uint32_t current = 0;
	size_t index = 0;
	for (;current < lim; ++index) {
		index %= len;
		current = array[index] * (1 + (current / array[index]));
		++count;
	}
	return count;
}

int main()
{
	uint32_t array[] = {5395, 7168, 2367, 9999, 3};
	printf("%d\n", multiple_cycle(1000000000, array, 5));
	return 0;
}

