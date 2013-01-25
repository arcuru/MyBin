#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// Uncomment to disable asserts
#define NDEBUG 1

typedef struct {
	uint32_t w;
	uint32_t h;
} coordinate; //!< Coordinate, with h being the index into 'board' and w being the bitwise representation of the current space

typedef struct {
	uint32_t total; //!< Total count of possible solutions
	size_t width; //!< Width of the board
	size_t height; //!< Height of the board
	uint32_t* board_rep; //!< Board in bitwise form. Each entry is a single row, '1's indicate free space
	uint32_t mask; //!< Mask for the correct width of the board
} board; //!< Total board representation

/** Validate coordinates
 *  Takes in a coordinate and checks to see if it is a valid move
 *  on the board
 *
 *  @arg here Coordinate to check
 *  @arg w Current board to check
 *  @return Boolean on whether or not the placement is valid
 */
inline bool validCoord ( coordinate here, board* w )
{
	if ( (here.w & w->mask) != 0 && here.h < w->height )
		if ( (w->board_rep[ here.h ] & here.w) != 0 )
			return true;
	return false;
}

/** Recursive Search
 *  Search for a solution recursively
 *
 *  @arg moves Current number of moves executed
 *  @arg here Current location
 *  @arg w Current board to test against
 */
void countTours ( uint32_t moves, coordinate here, board* w )
{
	// Check to see if we have finished the search
	if ( moves >= w->width * w->height ) {
		// Based on other criteria, we shouldn't have to do any more checking
		// Run checks only during debug
		assert( moves == w->width * w->height );
		assert( here.w == 1 && here.h == 0 );
		w->total++;
		return ;
	}

	// Optimize out the situation in which we are passing through the final point
	if ( here.w == 1 && here.h == 0 )
		return ;
	
	// Mark the board with the current position
	w->board_rep[ here.h ] ^= here.w;

	// Move in each direction recursively if it's a valid direction
	coordinate next;

	// Up
	next.w = here.w; next.h = here.h + 1;
	if ( validCoord( next, w ) )
		countTours ( moves + 1, next, w );

	// Down
	next.w = here.w; next.h = here.h - 1;
	if ( validCoord( next, w ) )
		countTours ( moves + 1, next, w );

	// Right
	next.w = here.w << 1; next.h = here.h;
	if ( validCoord( next, w ) )
		countTours ( moves + 1, next, w );

	// Left
	next.w = here.w >> 1; next.h = here.h;
	if ( validCoord( next, w ) )
		countTours ( moves + 1, next, w );
	
	// Unmark the current place on the board and backtrace
	w->board_rep[ here.h ] |= here.w;
	return ;
}

int main ( int argc, char *argv[] )
{
	// Allocate space for the board
	board* w = (board*) malloc( sizeof(board) );
	if ( NULL == w ) {
		printf("Memory allocation failed.");
		exit(1);
	}

	if ( argc == 3 ) {
		w->width = atoi( argv[1] );
		w->height = atoi( argv[2] );
	}
	else {
		// Default to problem specifics
		w->width = 10;
		w->height = 4;
	}

	// Allocate space for the board
	w->total = 0;
	w->board_rep = (uint32_t*)calloc( sizeof(uint32_t), w->height );
	if ( NULL == w->board_rep ) {
		printf("Memory allocation failed.");
		exit(1);
	}

	// Set up the mask with the low bits equal to the width of the grid set to '1's
	w->mask = 0;
	uint32_t i;
	uint32_t bit = 1;
	for (i = 0; i < w->width; i++) {
		w->mask |= bit;
		bit <<= 1;
	}

	// Initialize board using the mask
	for (i = 0; i < w->height; i++) {
		w->board_rep[i] = w->mask;
	}

	// Set up initial entry into the grid
	coordinate h;
	h.w = 1;
	h.h = w->height - 1;

	// Call recursive function
	countTours ( 1, h, w );

	// Print solution
	printf("Total Possibilities for T(%zu,%zu) = %u\n", w->width, w->height, w->total);

	// Free allocated memory
	free( w->board_rep );
	free( w );

	return EXIT_SUCCESS;
}
