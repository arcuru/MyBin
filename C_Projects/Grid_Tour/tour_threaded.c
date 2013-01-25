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
size_t width; //!< Width of working board
size_t height; //!< Height of working board

typedef struct {
	int32_t w;
	int32_t h;
} coordinate; //!< Coordinate, with h being the index into 'board' and w being the bitwise representation of the current space

uint32_t* board; //!< Board in bitwise form. Each entry is a single row, '1's indicate free space
uint32_t mask; //!< Mask for the correct width of the board

// Constants for directionality
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define FINISHED 4

// Structure to hold a single turn in the path
typedef struct {
	coordinate loc;
	int8_t dir;
} move;

move* move_list;
pthread_mutex_t tour_mutex = PTHREAD_MUTEX_INITIALIZER;

/** Validate coordinates
 *  Takes in a coordinate and a valid board, and checks to see if it is
 *  a valid move
 *
 *  @arg here Coordinate to check
 *  @arg board Working board
 *  @return Boolean on whether or not the placement is valid
 */
inline bool validCoord_opt ( coordinate here, uint32_t* board )
{

	if ( (here.w & mask) != 0 && here.h >= 0 && here.h < height )
		if ( (board[ here.h ] & here.w) != 0 )
			return true;
	return false;
}

// Structure for the input info necessary for individual threads
typedef struct {
	int moves;
	move* move_list;
	uint32_t* board;
} thread_info;

/** Single Thread
 *  Performs a single thread of searching for a working path.
 *
 *  @arg input Structure with necesary inputs for thread
 */
static void* executeThread ( void* input )
{
	// Pull inputs (board, move history, etc)
	thread_info* tmp = (thread_info*) input;
	int moves = tmp->moves;
	move* move_list = tmp->move_list;
	uint32_t* board = tmp->board;

	while ( moves >= tmp->moves ) {
		if ( moves >= width * height - 1 ) {
			// Found a full working path
			// Add to total
			assert( move_list[moves].loc.w == 1 && move_list[moves].loc.h == 0 );
			pthread_mutex_lock( &tour_mutex );
			total++;
			pthread_mutex_unlock( &tour_mutex );
			board[ move_list[moves].loc.h ] |= move_list[moves].loc.w;
			moves--;
			continue;
		}
		coordinate next;
		coordinate here = move_list[moves].loc;
		// Finish if we are trying to pass through the finish line
		if ( here.w == 1 && here.h == 0 ) {
			moves--;
			continue;
		}
		// Mark board with the current location
		board[ here.h ] ^= here.w;
		if (board[ here.h ] & here.w)
			board[ here.h ] ^= here.w;
		// Perform movements based on current location and valid moves	
		switch ( move_list[moves].dir ) {
			case UP:
				next.w = here.w; next.h = here.h + 1;
				if ( validCoord_opt( next, board ) ) {
					move_list[moves].dir = DOWN;
					moves++;
					move_list[moves].loc = next;
					move_list[moves].dir = UP;
					continue;
				}
			case DOWN:
				next.w = here.w; next.h = here.h - 1;
				if ( validCoord_opt( next, board ) ) {
					move_list[moves].dir = LEFT;
					moves++;
					move_list[moves].loc = next;
					move_list[moves].dir = UP;
					continue;
				}
			case LEFT:
				next.w = here.w >> 1; next.h = here.h;
				if ( validCoord_opt( next, board ) ) {
					move_list[moves].dir = RIGHT;
					moves++;
					move_list[moves].loc = next;
					move_list[moves].dir = UP;
					continue;
				}
			case RIGHT:
				next.w = here.w << 1; next.h = here.h;
				if ( validCoord_opt( next, board ) ) {
					move_list[moves].dir = FINISHED;
					moves++;
					move_list[moves].loc = next;
					move_list[moves].dir = UP;
					continue;
				}
			case FINISHED:
				board[ here.h ] |= here.w;
				moves--;
				continue;
			default:
				// Fail out if reaching this area
				assert( false );
				return NULL;
		}
	}
	free( board );
	free( move_list );
	return NULL;
}

/** Thread Setup
 *  Performs initial two step search and kicks off threads.
 *
 *  @arg start Initial coordinates for searching
 */
void setupThreads ( coordinate start )
{
	pthread_t thread[4];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	thread_info inputs[4];
	int in_counter = 0;
	pthread_mutex_init(&tour_mutex, NULL);

	int moves = 0;
	move_list[moves].loc = start;
	move_list[moves].dir = UP;
	while ( moves >= 0 ) {
		if ( moves == 2 ) {
			// Reached the depth of the initial search
			// Start up thread on this path
			move* new_move_list = (move*)malloc(sizeof(move)*width*height);
			uint32_t* new_board = (uint32_t*)calloc( sizeof(uint32_t), height );
			memcpy( new_move_list, move_list, sizeof(move)*width*height );
			memcpy( new_board, board, sizeof(uint32_t)*height );
			inputs[in_counter].moves = moves;
			inputs[in_counter].move_list = new_move_list;
			inputs[in_counter].board = new_board;
			if ( pthread_create(&thread[in_counter], &attr, executeThread, (void*) &inputs[in_counter]) ) {
				printf("Pthread create failed\n");
				exit(1);
			}

			in_counter++;
			board[ move_list[moves].loc.h ] |= move_list[moves].loc.w;
			moves--;
			continue;
		}
		coordinate next;
		coordinate here = move_list[moves].loc;
		// Finish if we are trying to pass through the finish line
		if ( here.w == 1 && here.h == 0 ) {
			moves--;
			continue;
		}
		// Mark board with the current location
		board[ here.h ] ^= here.w;
		if (board[ here.h ] & here.w)
			board[ here.h ] ^= here.w;
		// Perform movements based on current location and valid moves	
		switch ( move_list[moves].dir ) {
			case UP:
				next.w = here.w; next.h = here.h + 1;
				if ( validCoord_opt( next, board ) ) {
					move_list[moves].dir = DOWN;
					moves++;
					move_list[moves].loc = next;
					move_list[moves].dir = UP;
					continue;
				}
			case DOWN:
				next.w = here.w; next.h = here.h - 1;
				if ( validCoord_opt( next, board ) ) {
					move_list[moves].dir = LEFT;
					moves++;
					move_list[moves].loc = next;
					move_list[moves].dir = UP;
					continue;
				}
			case LEFT:
				next.w = here.w >> 1; next.h = here.h;
				if ( validCoord_opt( next, board ) ) {
					move_list[moves].dir = RIGHT;
					moves++;
					move_list[moves].loc = next;
					move_list[moves].dir = UP;
					continue;
				}
			case RIGHT:
				next.w = here.w << 1; next.h = here.h;
				if ( validCoord_opt( next, board ) ) {
					move_list[moves].dir = FINISHED;
					moves++;
					move_list[moves].loc = next;
					move_list[moves].dir = UP;
					continue;
				}
			case FINISHED:
				board[ here.h ] |= here.w;
				moves--;
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
	// Allow inputting size of grid on command line
	if ( argc == 3 ) {
		width = atoi( argv[1] );
		height = atoi( argv[2] );
	}
	else {
		// Default to problem specifics
		width = 10;
		height = 4;
	}
	// Create initial board and move list for thread setup
	board = (uint32_t*)calloc( sizeof(uint32_t), height );
	move_list = (move*)calloc( sizeof(move), width * height );

	// Set up the mask with the low bits equal to the width of the grid set to '1's
	mask = 0;
	uint32_t i;
	uint32_t bit = 1;
	for (i = 0; i < width; i++) {
		mask |= bit;
		bit <<= 1;
	}

	// Initialize board using the mask
	for (i = 0; i < height; i++) {
		board[i] = mask;
	}

	// Set up initial entry into the grid
	coordinate h;
	h.w = 1;
	h.h = height - 1;

	// Start creating the threads and running them
	setupThreads ( h );

	// Free allocated memory
	free( board );
	free( move_list );

	// Print out solution
	printf("Total possibilities for T(%zu,%zu) = %u\n", width, height, total);

	return EXIT_SUCCESS;
}
