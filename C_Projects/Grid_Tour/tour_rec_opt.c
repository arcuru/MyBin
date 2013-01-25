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
 *  @return Boolean on whether or not the placement is valid
 */
inline bool validCoord ( coordinate here, board* working )
{
	if ( (here.w & working->mask) != 0 && here.h < working->height )
		if ( (working->board_rep[ here.h ] & here.w) != 0 )
			return true;
	return false;
}

/** Recursive Search
 *  Search for a solution recursively
 *
 *  @arg moves Current number of moves executed
 *  @arg here Current location
 */
void countTours ( uint32_t moves, coordinate here, board* working )
{
	// Check to see if we have finished the search
	if ( moves >= working->width * working->height ) {
		// Based on other criteria, we shouldn't have to do any more checking
		// Run checks only during debug
		assert( moves == working->width * working->height );
		assert( here.w == 1 && here.h == 0 );
		working->total++;
		return ;
	}

	// Optimize out the situation in which we are passing through the final point
	if ( here.w == 1 && here.h == 0 )
		return ;
	
	// Mark the board with the current position
	working->board_rep[ here.h ] ^= here.w;

	// Move in each direction recursively if it's a valid direction
	coordinate next;

	// Up
	next.w = here.w; next.h = here.h + 1;
	if ( validCoord( next, working ) )
		countTours ( moves + 1, next, working );

	// Down
	next.w = here.w; next.h = here.h - 1;
	if ( validCoord( next, working ) )
		countTours ( moves + 1, next, working );

	// Right
	next.w = here.w << 1; next.h = here.h;
	if ( validCoord( next, working ) )
		countTours ( moves + 1, next, working );

	// Left
	next.w = here.w >> 1; next.h = here.h;
	if ( validCoord( next, working ) )
		countTours ( moves + 1, next, working );
	
	// Unmark the current place on the board and backtrace
	working->board_rep[ here.h ] |= here.w;
	return ;
}

int main ( int argc, char *argv[] )
{
	// Allocate space for the board
	board* working = (board*) malloc( sizeof(board) );
	if ( argc == 3 ) {
		working->width = atoi( argv[1] );
		working->height = atoi( argv[2] );
	}
	else {
		// Default to problem specifics
		working->width = 10;
		working->height = 4;
	}

	// Allocate space for the board
	working->total = 0;
	working->board_rep = (uint32_t*)calloc( sizeof(uint32_t), working->height );

	// Set up the mask with the low bits equal to the width of the grid set to '1's
	working->mask = 0;
	uint32_t i;
	uint32_t bit = 1;
	for (i = 0; i < working->width; i++) {
		working->mask |= bit;
		bit <<= 1;
	}

	// Initialize board using the mask
	for (i = 0; i < working->height; i++) {
		working->board_rep[i] = working->mask;
	}

	// Set up initial entry into the grid
	coordinate h;
	h.w = 1;
	h.h = working->height - 1;

	// Call recursive function
	countTours ( 1, h, working );

	// Print solution
	printf("Total Possibilities for T(%zu,%zu) = %u\n", working->width, working->height, working->total);

	// Free allocated memory
	free( working->board_rep );
	free( working );

	return EXIT_SUCCESS;
}
