#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>

// Uncomment to disable asserts
//#define NDEBUG 1

uint32_t total = 0; //!< Full count of possible paths
pthread_mutex_t tour_mutex = PTHREAD_MUTEX_INITIALIZER; //!< Mutex lock for updating count

typedef struct {
	uint32_t w;
	uint32_t h;
} coordinate; //!< Coordinate, with h being the index into 'board' and w being the bitwise representation of the current space

typedef struct {
	coordinate loc;
	int8_t dir;
} move; //!< Structure to hold a single turn in the path

typedef struct {
	size_t width; //!< Width of the board
	size_t height; //!< Height of the board
	uint32_t* board_rep; //!< Board in bitwise form. Each entry is a single row, '1's indicate free space
	uint32_t mask; //!< Mask for the correct width of the board
	move* move_list; //!< History of moves made on this board
	int32_t moves; //!< Number of moves made on the board
} board; //!< Total board representation

// Constants for directionality
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define FINISHED 4


/** Validate coordinates
 *  Takes in a coordinate and a valid board, and checks to see if it is
 *  a valid move
 *
 *  @arg here Coordinate to check
 *  @arg w Working board
 *  @return Boolean on whether or not the placement is valid
 */
bool validCoord ( coordinate here, board* w )
{
	if ( (here.w & w->mask) != 0 && here.h < w->height )
		if ( (w->board_rep[ here.h ] & here.w) != 0 )
			return true;
	return false;
}

/** Single Thread
 *  Performs a single thread of searching for a working path.
 *
 *  @arg input Structure with necesary inputs for thread
 */
static void* executeThread ( void* input )
{
	// Pull inputs (board, move history, etc)
	board* w = (board*) input;

	uint32_t local_total = 0;
	int32_t minimum_moves = w->moves;

	while ( w->moves >= minimum_moves ) {
		if ( w->moves >= (int32_t)(w->width * w->height - 1) ) {
			// Found a full working path
			// Add to total
			assert( w->move_list[w->moves].loc.w == 1 && w->move_list[w->moves].loc.h == 0 );
			local_total++;
			pthread_mutex_unlock( &tour_mutex );
			w->board_rep[ w->move_list[w->moves].loc.h ] |= w->move_list[w->moves].loc.w;
			w->moves--;
			continue;
		}
		coordinate next;
		coordinate here = w->move_list[w->moves].loc;
		// Finish if we are trying to pass through the finish line
		if ( here.w == 1 && here.h == 0 ) {
			w->moves--;
			continue;
		}
		// Mark board with the current location
		w->board_rep[ here.h ] ^= here.w;
		if (w->board_rep[ here.h ] & here.w)
			w->board_rep[ here.h ] ^= here.w;
		// Perform movements based on current location and valid moves	
		switch ( w->move_list[w->moves].dir ) {
			case UP:
				next.w = here.w; next.h = here.h + 1;
				if ( validCoord( next, w ) ) {
					w->move_list[w->moves].dir = DOWN;
					w->moves++;
					w->move_list[w->moves].loc = next;
					w->move_list[w->moves].dir = UP;
					continue;
				}
			case DOWN:
				next.w = here.w; next.h = here.h - 1;
				if ( validCoord( next, w ) ) {
					w->move_list[w->moves].dir = LEFT;
					w->moves++;
					w->move_list[w->moves].loc = next;
					w->move_list[w->moves].dir = UP;
					continue;
				}
			case LEFT:
				next.w = here.w >> 1; next.h = here.h;
				if ( validCoord( next, w ) ) {
					w->move_list[w->moves].dir = RIGHT;
					w->moves++;
					w->move_list[w->moves].loc = next;
					w->move_list[w->moves].dir = UP;
					continue;
				}
			case RIGHT:
				next.w = here.w << 1; next.h = here.h;
				if ( validCoord( next, w ) ) {
					w->move_list[w->moves].dir = FINISHED;
					w->moves++;
					w->move_list[w->moves].loc = next;
					w->move_list[w->moves].dir = UP;
					continue;
				}
			case FINISHED:
				w->board_rep[ here.h ] |= here.w;
				w->moves--;
				continue;
			default:
				// Fail out if reaching this area
				assert( false );
				return NULL;
		}
	}

	// Free allocated memory
	free( w->board_rep );
	free( w->move_list );
	free( w );

	// Update global totals
	pthread_mutex_lock( &tour_mutex );
	total += local_total;
	pthread_mutex_unlock( &tour_mutex );
	return NULL;
}

/** Thread Setup
 *  Performs initial two step search and kicks off threads.
 *
 *  @arg start Initial coordinates for searching
 *  @arg w Initial board with settings
 */
void setupThreads ( coordinate start, board* w )
{
	pthread_t thread[4];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	board* inputs[4];
	int in_counter = 0;
	pthread_mutex_init(&tour_mutex, NULL);

	w->moves = 0;
	w->move_list[w->moves].loc = start;
	w->move_list[w->moves].dir = UP;
	while ( w->moves >=  0 ) {
		if ( w->moves == 2 ) {
			// Reached the depth of the initial search
			// Start up thread on this path
			board* new_board = (board*) malloc( sizeof(board) );
			new_board->width = w->width;
			new_board->height = w->height;
			new_board->mask = w->mask;
			new_board->moves = w->moves;
			new_board->move_list = (move*) malloc(sizeof(move)*w->width*w->height);
			new_board->board_rep = (uint32_t*) calloc( sizeof(uint32_t), w->height );
			memcpy( new_board->move_list, w->move_list, sizeof(move)*w->width*w->height );
			memcpy( new_board->board_rep, w->board_rep, sizeof(uint32_t)*w->height );
			inputs[in_counter] = new_board;
			if ( pthread_create(&thread[in_counter], &attr, executeThread, (void*) inputs[in_counter]) ) {
				printf("Pthread create failed\n");
				exit(1);
			}

			in_counter++;
			w->board_rep[ w->move_list[w->moves].loc.h ] |= w->move_list[w->moves].loc.w;
			w->moves--;
			continue;
		}
		coordinate next;
		coordinate here = w->move_list[w->moves].loc;
		// Finish if we are trying to pass through the finish line
		if ( here.w == 1 && here.h == 0 ) {
			w->moves--;
			continue;
		}
		// Mark board with the current location
		w->board_rep[ here.h ] ^= here.w;
		if (w->board_rep[ here.h ] & here.w)
			w->board_rep[ here.h ] ^= here.w;
		// Perform movements based on current location and valid moves	
		switch ( w->move_list[w->moves].dir ) {
			case UP:
				next.w = here.w; next.h = here.h + 1;
				if ( validCoord( next, w ) ) {
					w->move_list[w->moves].dir = DOWN;
					w->moves++;
					w->move_list[w->moves].loc = next;
					w->move_list[w->moves].dir = UP;
					continue;
				}
			case DOWN:
				next.w = here.w; next.h = here.h - 1;
				if ( validCoord( next, w ) ) {
					w->move_list[w->moves].dir = LEFT;
					w->moves++;
					w->move_list[w->moves].loc = next;
					w->move_list[w->moves].dir = UP;
					continue;
				}
			case LEFT:
				next.w = here.w >> 1; next.h = here.h;
				if ( validCoord( next, w ) ) {
					w->move_list[w->moves].dir = RIGHT;
					w->moves++;
					w->move_list[w->moves].loc = next;
					w->move_list[w->moves].dir = UP;
					continue;
				}
			case RIGHT:
				next.w = here.w << 1; next.h = here.h;
				if ( validCoord( next, w ) ) {
					w->move_list[w->moves].dir = FINISHED;
					w->moves++;
					w->move_list[w->moves].loc = next;
					w->move_list[w->moves].dir = UP;
					continue;
				}
			case FINISHED:
				w->board_rep[ here.h ] |= here.w;
				w->moves--;
				continue;
			default:
				// Fail out if reaching this area
				assert( false );
				return;
		}
	}
	void* status;
	int t;
	for (t = 0; t < in_counter; t++) {
		pthread_join(thread[t], &status);
	}
	return;
}

int main ( int argc, char *argv[] )
{
	// Allocate space for the board
	board* w = (board*) malloc( sizeof(board) );

	// Allow inputting size of grid on command line
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
	w->board_rep = (uint32_t*)calloc( sizeof(uint32_t), w->height );
	w->move_list = (move*)calloc( sizeof(move), w->width * w->height );

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

	// Start creating the threads and running them
	setupThreads ( h, w );

	// Print out solution
	printf("Total possibilities for T(%zu,%zu) = %u\n", w->width, w->height, total);

	// Free allocated memory
	free( w->board_rep );
	free( w->move_list );
	free( w );

	return EXIT_SUCCESS;
}
