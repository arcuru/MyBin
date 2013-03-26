#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Code and comments (with respect to Win/Loss) are written from the perspective of the AI

typedef int status_t;

const status_t WIN = 0;
const status_t LOSS = 1;
const status_t TIE = 2;
const status_t ONGOING = 3; 

typedef char board_t ;

const board_t EMPTY = ' ';
const board_t AI = 'O';
const board_t USER = 'X';

typedef struct {
	int x; //!< X location
	int y; //!< Y location
	double odds; //!< Odds of a win
} move_t; //!< Holds the move and the odds of a win

/** Print Board Plain
 *  prints out a text representation of the board, with blanks.
 *
 *  @args board TTT board to print
 */
void printBoardPlain ( board_t board[3][3] )
{
	printf("+-+-+-+\n");
	printf("|%c|%c|%c|\n", board[0][0], board[0][1], board[0][2]);
	printf("+-+-+-+\n");
	printf("|%c|%c|%c|\n", board[1][0], board[1][1], board[1][2]);
	printf("+-+-+-+\n");
	printf("|%c|%c|%c|\n", board[2][0], board[2][1], board[2][2]);
	printf("+-+-+-+\n");
}

/** Print Board User
 *  prints out a text representation of the board, with numbers for user
 *  input.
 *
 *  @args board TTT board to print
 */
void printBoardUser ( board_t board[3][3] )
{
	board_t tmp[3][3];
	memcpy( tmp, board, sizeof(board_t)*9);
	int i,j;
	for ( i = 0; i < 3; ++i ) {
		for ( j = 0; j < 3; ++j ) {
			if ( EMPTY == tmp[i][j] )
				tmp[i][j] = '1' + i*3 + j;
		}
	}
	printf("+-+-+-+\n");
	printf("|%c|%c|%c|\n", tmp[0][0], tmp[0][1], tmp[0][2]);
	printf("+-+-+-+\n");
	printf("|%c|%c|%c|\n", tmp[1][0], tmp[1][1], tmp[1][2]);
	printf("+-+-+-+\n");
	printf("|%c|%c|%c|\n", tmp[2][0], tmp[2][1], tmp[2][2]);
	printf("+-+-+-+\n");
}

/** Board Status
 *  returns the current status of the board. 
 *  Makes the assumption that only one winner exists.
 *
 *  @arg board TTT board to be analyzed
 *  @returns Status of the input board
 */
status_t boardStatus ( board_t board[3][3] )
{
	// Temp variables
	int i, j;

	// Check for a winner, double up rows & cols
	for ( i = 0; i < 3; ++i ) {
		const board_t shared = board[i][i];
		// Skip if shared location is empty
		if ( EMPTY == shared )
			continue;
		status_t retval = (shared == AI) ? WIN : LOSS;
		// Faster to hardcode
		if ( shared == board[i][0] && shared == board[i][1] && shared == board[i][2] )
			return retval;
		if ( shared == board[0][i] && shared == board[1][i] && shared == board[2][i] )
			return retval;
	}
	
	// Check diags
	if ( EMPTY != board[1][1] ) {
		status_t retval = (board[1][1] == AI) ? WIN : LOSS;
		if ( board[0][0] == board[1][1] && board[1][1] == board[2][2] )
			return retval;
		if ( board[0][2] == board[1][1] && board[1][1] == board[2][0] )
			return retval;
	}

	// Check if we are still ongoing.
	bool finished = true;
	for ( i = 0; i < 3; ++i ) {
		for ( j = 0; j < 3; ++j ) {
			if ( EMPTY == board[i][j] )
				return ONGOING;
		}
	}
	return TIE;
}

status_t recursiveCheck ( board_t board[3][3] , board_t current_user )
{
	int i, j;
	status_t result;
	int wins=0, count=0, losses=0;
	board_t next_user = (current_user == AI) ? USER : AI;
	assert( next_user != current_user );

	if ( ONGOING != boardStatus(board) )
		return boardStatus(board);

	for ( i = 0; i < 3; ++i ) {
		for ( j = 0; j < 3; ++j ) {
			// Do stuff at each location
			if ( EMPTY != board[i][j] )
				continue;
			board[i][j] = current_user;
			//result = tmp( board, ...);
			result = recursiveCheck( board, next_user );
			if ( WIN == result )
				++wins;
			else if ( LOSS == result )
				++losses;
			board[i][j] = EMPTY;
			++count;
		}
	}
	assert( 0 != count );

	if ( USER == current_user ) {
		if ( 0 != losses )
			return LOSS;
		if ( wins == count )
			return WIN;
		return ONGOING;
	}

	if ( 0 != wins )
		return WIN;
	if ( count == losses )
		return LOSS;
	return ONGOING;
}

/** Pick Move
 *  Selects the best move for the AI given the current difficulty
 *
 *  @args 
 */
move_t pickMove ( board_t board[3][3], uint32_t difficulty, uint32_t current_depth )
{
	// We need the current progress of the board before doing anythin
	//status_t progress = boardStatus( board );
	move_t m;
	m.x = -1;
	m.y = -1;
	int i, j;
	for ( i = 0; i < 3; ++i ) {
		for ( j = 0; j < 3; ++j ) {
			// Do stuff at each location
			if ( EMPTY != board[i][j] )
				continue;
			board[i][j] = AI;
			status_t results = recursiveCheck( board, USER );
			if ( WIN == results ) {
				board[i][j] = EMPTY;
				m.x = i;
				m.y = j;
				printf("picking a winner\n");
				return m;
			}
			else if ( ONGOING == results ) {
				m.x = i;
				m.y = j;
			}
			else if ( LOSS == results ) {
				printf("%d\t%d\n",i,j);
			}
			board[i][j] = EMPTY;
		}
	}
	if ( -1 == m.x ) {
		// Losses or ties everywhere, pick at random
		int g = rand() % 9;
		while ( EMPTY != board[g/3][g%3] )
			g = rand() % 9;
		m.x = g/3;
		m.y = g%3;
		printf("Random Guessing!\n");
		return m;
	}
	printf("Meh!\n");
	return m;
}


uint8_t getUserInput ( )
{
	printf("Select your move: ");
	uint8_t g = (uint8_t)getc( stdin );
	printf("\n"); // Reallign after input
	g -= '1'; // Get address out of user
	return g;
}

int main ( int argc, char** argv )
{
	srand(time(NULL));
	board_t board[3][3];
	int i, j, k;
	for ( i = 0; i < 3; ++i ) {
		for ( j = 0; j < 3; ++j ) {
			board[i][j] = EMPTY;
		}
	}

	for ( i = 0; i < 2; ++i ) {
		if ( i == 1 ) {
			move_t m = pickMove( board, 0, 0);
			
			assert( m.x >=0 && m.x <= 3 );
			assert( m.y >=0 && m.y <= 3 );
			assert( EMPTY == board[m.x][m.y] );
			board[m.x][m.y] = AI;
		}
		while ( true ) {
			// Show the user the current board
			printBoardUser( board );

			// Get user input, account for incorrect inputs
			uint8_t g = 9;
			while ( g > 8 ) {
				g = getUserInput();
				if ( g > 8 || board[g/3][g%3] != EMPTY)
					printf("Please select a valid move.\n");
			}
			board[g/3][g%3] = USER;

			if ( LOSS == boardStatus( board ) ) {
				printf("Congratulations! You win!\n");
				break;
			}
			else if ( TIE == boardStatus( board ) ) {
				printf("Cat game fool!\n");
				break;
			}

			// AI needs to make a move now
			move_t m = pickMove( board, 0, 0);
			
			assert( m.x >=0 && m.x <= 3 );
			assert( m.y >=0 && m.y <= 3 );
			assert( EMPTY == board[m.x][m.y] );
			board[m.x][m.y] = AI;

			status_t s = boardStatus( board );
			if ( WIN == s ) {
				printf("Haha! You lost!\n");
				break;
			}
			else if ( LOSS == s )
				assert(false);
			else if ( TIE == s ) {
				printf("Cat game fool!\n");
				break;
			}
		}
		for ( k = 0; k < 3; ++k ) {
			for ( j = 0; j < 3; ++j ) {
				board[k][j] = EMPTY;
			}
		}
	}

	return 0;
}

