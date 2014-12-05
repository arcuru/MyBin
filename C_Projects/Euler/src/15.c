#include "Euler.h"
#include <stdlib.h>

int64_t Euler_15()
{
	size_t side = 20; // Size of grid
	side++; // Grid has side + 1 vertexes in each direction

	// Create a grid of values for the number of paths to each vertex
	// Each point corresponds to a vertex in the grid
	uint64_t grid[ side ][ side ];
	
	// Initialize starting position
	grid[0][0] = 1;

	// Iterate and combine
	size_t x;
	size_t y;
	for (x = 0; x < side; x++) {
		for (y = 0; y < side; y++) {
			// Need to initialize values to 0 (skipping first vertex)
			if (x > 0 || y > 0)
				grid[x][y] = 0;

			// Add # of paths to the vertes to the left if it exists
			if (x > 0)
				grid[x][y] += grid[x-1][y];
			// Add # of paths to the vertex above if it exists
			if (y > 0)
				grid[x][y] += grid[x][y-1];
		}
	}
	return (int64_t) grid[side-1][side-1];
}
