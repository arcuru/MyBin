#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>

// Uncomment to disable asserts
#define NDEBUG 1

// Define threading defaults
uint32_t MAX_THREAD_COUNT = 4;
int32_t THREAD_DEPTH = 2;

uint32_t total = 0; //!< Full count of possible paths
pthread_mutex_t tour_mutex = PTHREAD_MUTEX_INITIALIZER; //!< Mutex lock for updating count

typedef struct {
	uint64_t w;
	uint32_t h;
} coordinate; //!< Coordinate, with h being the index into 'board' and w being the bitwise representation of the current space

typedef struct {
	coordinate loc;
	int8_t dir;
} move; //!< Structure to hold a single turn in the path

typedef struct {
	size_t width; //!< Width of the board
	size_t height; //!< Height of the board
	uint64_t* board_rep; //!< Board in bitwise form. Each entry is a single row, '1's indicate free space
	uint64_t mask; //!< Mask for the correct width of the board
	move* move_list; //!< History of moves made on this board
	int32_t moves; //!< Number of moves made on the board
} board; //!< Total board representation

// Constants for directionality
// Would prefer these to be of 'const' type, but this way is necessary for use within switch statement
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define FINISHED 4

/** Validate Allocation
 *  short function to validate if a memory allocation was successful.
 *  Exits program on failure
 *
 *  @arg p Pointer to allocated space
 */
void validateAlloc ( void* p )
{
	if ( NULL == p ) {
		printf("Memory allocation failed.");
		exit(1);
	}
	return ;
}

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

/** Grid Traverse
 *  Move to the next location on the board, backtraciing if necessary
 *
 *  @arg w Board to work on
 */
void gridTraverse ( board* w )
{
	coordinate next;
	coordinate here = w->move_list[w->moves].loc;
	// Finish if we are trying to pass through the finish line
	if ( here.w == 1 && here.h == 0 ) {
		w->moves--;
		return ;
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
				return ;
			}
		case DOWN:
			next.w = here.w; next.h = here.h - 1;
			if ( validCoord( next, w ) ) {
				w->move_list[w->moves].dir = LEFT;
				w->moves++;
				w->move_list[w->moves].loc = next;
				w->move_list[w->moves].dir = DOWN;
				return ;
			}
		case LEFT:
			next.w = here.w >> 1; next.h = here.h;
			if ( validCoord( next, w ) ) {
				w->move_list[w->moves].dir = RIGHT;
				w->moves++;
				w->move_list[w->moves].loc = next;
				w->move_list[w->moves].dir = UP;
				return ;
			}
		case RIGHT:
			next.w = here.w << 1; next.h = here.h;
			if ( validCoord( next, w ) ) {
				w->move_list[w->moves].dir = FINISHED;
				w->moves++;
				w->move_list[w->moves].loc = next;
				w->move_list[w->moves].dir = UP;
				return ;
			}
		case FINISHED:
			w->board_rep[ here.h ] |= here.w;
			w->moves--;
			return ;
		default:
			// Fail out if reaching this area
			assert( false );
			exit(1);
	}
	return ;
}

/** Single Thread
 *  Performs a single thread of searching for a working path.
 *
 *  @arg input Structure with necesary inputs for thread
 */
void* executeThread ( void* input )
{
	// Pull inputs (board, move history, etc)
	board* w = (board*) input;

	// We'll update a local variable with the total to save time on trying to lock the mutex
	uint32_t local_total = 0;
	int32_t minimum_moves = w->moves;

	while ( w->moves >= minimum_moves ) {
		if ( w->moves >= (int32_t)(w->width * w->height - 1) ) {
			// Found a full working path

			// No other checking should be necessary
			assert( w->move_list[w->moves].loc.w == 1 && w->move_list[w->moves].loc.h == 0 );

			// Add to local total
			local_total++;

			// Remove marker from this position
			w->board_rep[ w->move_list[w->moves].loc.h ] |= w->move_list[w->moves].loc.w;
			w->moves--;
			continue;
		}
		// Traverse to the next position or back up if done searching this position
		gridTraverse ( w );
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
	// Initialize threading defaults
	pthread_t thread[MAX_THREAD_COUNT];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	board* inputs[MAX_THREAD_COUNT];

	// Counter for the number of threads
	uint32_t thread_counter = 0;

	pthread_mutex_init(&tour_mutex, NULL);

	w->moves = 0;
	w->move_list[w->moves].loc = start;
	w->move_list[w->moves].dir = UP;
	while ( w->moves >=  0 ) {
		if ( w->moves == THREAD_DEPTH ) {
			// Reached the depth of the initial search
			// Start up thread on this path

			// Allocate space for a new board
			board* new_board = (board*) malloc( sizeof(board) );
			validateAlloc ( new_board );

			// Copy over all non-pointer stuff
			memcpy( new_board, w, sizeof(board) );

			// Allocate space for the necessary copied arrays
			new_board->move_list = (move*) malloc(sizeof(move)*w->width*w->height);
			validateAlloc ( new_board->move_list );
			new_board->board_rep = (uint64_t*) calloc( sizeof(uint64_t), w->height );
			validateAlloc ( new_board->board_rep );

			// Copy over existing movements and grid
			memcpy( new_board->move_list, w->move_list, sizeof(move)*w->width*w->height );
			memcpy( new_board->board_rep, w->board_rep, sizeof(uint64_t)*w->height );

			// Kick off new thread
			inputs[thread_counter] = new_board;
			if ( pthread_create(&thread[thread_counter], &attr, executeThread, (void*) inputs[thread_counter]) ) {
				printf("Pthread create failed\n");
				exit(1);
			}

			thread_counter++;

			// Remove marker from current position
			w->board_rep[ w->move_list[w->moves].loc.h ] |= w->move_list[w->moves].loc.w;
			w->moves--;
			continue;
		}
		// Traverse to the next position or back up if done searching this position
		gridTraverse ( w );
	}
	// Wait for all threads to finish before returning
	void* status;
	uint32_t t;
	for (t = 0; t < thread_counter; t++) {
		pthread_join(thread[t], &status);
	}
	return;
}

int main ( int argc, char *argv[] )
{
	// Allocate space for the board
	board* w = (board*) malloc( sizeof(board) );
	validateAlloc ( w );

	// Allow inputting size of grid on command line
	if ( argc == 4 ) {
		w->width = atoi( argv[1] );
		w->height = atoi( argv[2] );
		int cores = atoi( argv[3] );
		if ( cores <= 4 ) {
			// Keep defaults
			MAX_THREAD_COUNT = 4;
			THREAD_DEPTH = 2;
		}
		else if ( cores <= 10 ) {
			// Keep defaults
			MAX_THREAD_COUNT = 10;
			THREAD_DEPTH = 3;
		}
		else {
			THREAD_DEPTH = 3;
			MAX_THREAD_COUNT = 10;
			int i;
			for (i = 10; i <= cores; i*=3)
				THREAD_DEPTH++;
			MAX_THREAD_COUNT = i;
		}
	}
	else if ( argc == 3 ) {
		w->width = atoi( argv[1] );
		w->height = atoi( argv[2] );
	}
	else if ( argc != 1 ) {
		printf("Usage: %s <width=10> <height=4> [<max threads=4>]\n", argv[0]);
		printf("Executing with default inputs.");
		// Default to problem specifics
		w->width = 10;
		w->height = 4;
	}
	else {
		// Default to problem specifics
		w->width = 10;
		w->height = 4;
	}

	// Allocate space for the board
	w->board_rep = (uint64_t*)calloc( sizeof(uint64_t), w->height );
	validateAlloc ( w->board_rep );
	w->move_list = (move*)calloc( sizeof(move), w->width * w->height );
	validateAlloc ( w->move_list );

	// Set up the mask with the low bits equal to the width of the grid set to '1's
	w->mask = 0;
	uint32_t i;
	uint64_t bit = 1;
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
