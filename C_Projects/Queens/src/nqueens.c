/*!	\file main.c
 * 	\brief NQueens solution
 *
 * 	A command line solution to the NQueens problem.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define nRows 13
#define nCols nRows

int currentCol = 0;
int Board[nRows][nCols];
int queenRow[nCols]; //Each place in the array denotes a column,
//the value stored is the row of the Queen

/*!	
 *	\brief		Is legal
 *
 *	Checks if a queen can legally be placed on the board
 *
 *	\param row	Row of the potential place
 *	\param col	Column of the potential place
 *	\return		Whether or not this is a legal move
 *
 */
int isLegal(int row, int col)
{
    return Board[row][col]==0 ? true : false;
}

/*!	
 *	\brief		Print Board
 *
 * 	Print the board out to the console
 *
 */
void PrintBoard()
{
    static int solution = 0;
    printf("Found solution number %d\n", ++solution);
    int r, c;
    for (r = 0; r < nRows; r++) {
        for (c = 0; c < nCols; c++) {
            if (Board[r][c] == -1) {
                printf(" Q ");
            } else {
                printf(" - ");
            }
        }
        printf("\n");
    }
}

// Queen - Places/Removes Queen
// Marks each place on the board like spokes from the queen
// Looks long but is more efficient doing each continuos line
/*!
 * 	\brief		N Queens
 *
 * 	Recursively solves the N Queens problem by creating each solution 
 * 	using #Board
 *
 * 	\param row	Row to place the queen
 * 	\param col	Column to place the queen
 * 	\param in	Something else
 *
 */
void Queen(int row, int col, int in)
{
    int plus = -1;
    if (in == true) {
        plus = 1;
    }
    int r, c;
    //Up Right
    r = row - 1;
    c = col + 1;
    while ((r >= 0) && (c < nCols)) {
        Board[r][c] += plus;
        r--;
        c++;
    }
    //Down Right
    r = row + 1;
    c = col + 1;
    while ((r < nRows) && (c < nCols)) {
        Board[r][c] += plus;
        r++;
        c++;
    }
    //Right
    c = col + 1;
    while (c < nCols) {
        Board[row][c] += plus;
        c++;
    }

    if (in == true)
        Board[row][col] = -1;
    else
        Board[row][col] = 0;
}

/*!
 * 	\brief		Place queen
 *
 * 	Places the queen in the current column
 *
 * 	\param row	Row to place the queen
 *
 */
void Place(int row)
{
    queenRow[currentCol] = row;
    Queen(row, currentCol, true);
    currentCol++;
}

/*!
 * 	\brief		Remove queen
 *
 * 	Removes the queen from the current column
 *
 */
void Remove()
{
    int row = queenRow[currentCol];
    int col = currentCol;
    Queen(row, col, false);
    queenRow[currentCol] = -1;
}

/*!
 * 	\brief		Process Column
 *
 * 	Find the next legal location in the specified column, place a queen
 * 	there, and advance to the next column
 *
 */
int ProcessColumn()
{
    int row = queenRow[currentCol] + 1;
    if (queenRow[currentCol] >= 0) {
        Remove();
    }
    while (row < nRows) {
        if (isLegal(row, currentCol)) {
            Place(row);
            return true;
        }
        row++;
    }
    return false;
}

/*!
 * 	\brief		Print Results
 *
 * 	Prints the timing results to the console
 *
 * 	\param pt1	Time struct from the start of calculations
 * 	\param pt2	Time struct from the end of calculations
 *
 */
void printResults(time_t* pt1, time_t* pt2)
{
    double secs;
    int hours, mins, intsecs;

    secs = difftime(*pt2, *pt1);
    intsecs = (int) secs;

    /* Print hours, minutes, seconds */
    hours = intsecs / 3600;
    intsecs -= hours * 3600;
    mins = intsecs / 60;
    intsecs -= mins * 60;
    printf("Calculations took ");
    if (hours > 0)
	printf("%d hour%s, ", hours, (hours == 1) ? "" : "s");
    if (mins > 0 || hours > 0)
	printf("%d minute%s and ", mins, (mins == 1) ? "" : "s");
    printf("%d second%s.\n", intsecs, (intsecs == 1 ? "" : "s"));
}

/*!
 * 	\brief		N Queens
 *
 * 	Self contained solution to the N Queens problem
 *
 * 	\param n	Side length of the board to solve
 * 	\return		Number of solutions to the input board
 *
 */
int N_Queens(int n)
{
    int bit, maxbit = 1 << n;
    int pos[n], diagr[n], diagl[n], col[n];
    for (bit = 0; bit < n; bit++) {
        pos[bit] = 0;
        diagr[bit] = 0;
        diagl[bit] = 0;
        col[bit] = 0;
    }
    int count = 0;
    int lvl = 0;
    int tmpcol, tmpdiagl, tmpdiagr;
    while (lvl>=0) {
        if (lvl==0 && pos[lvl]==(n/2)) {
            count*=2;
            if (n%2==0)
                break;
        }
        if (lvl==0 && pos[lvl]==(n/2)+1) {
            break;
        }
        for (bit = 1 << pos[lvl]; bit < maxbit; bit <<= 1, ++pos[lvl]) {
            if (((col[lvl] | diagl[lvl] | diagr[lvl]) & bit) == 0) {
                tmpcol = col[lvl] | bit;
                tmpdiagl = diagl[lvl] | bit;
                tmpdiagr = diagr[lvl] | bit;
                break;
            }
        }
        if (bit == maxbit) {
            pos[lvl] = 0;
            --lvl;
        } else if (lvl == n-1) {
            count++;
            pos[lvl] = 0;
            --lvl;
        } else {
            pos[lvl]++;
            ++lvl;
            col[lvl] = tmpcol;
            diagl[lvl] = tmpdiagl << 1;
            diagr[lvl] = tmpdiagr >> 1;
        }
    }
    return count;
}

/*!
 * 	\brief		Main
 *
 * 	Read input, times the calculation, and prints to console
 *
 * 	\param argc	Number of command line arguments
 * 	\param argv	List of command line arguments
 * 	\return		Program success
 */
int main(int argc, char *argv[])
{
    if (argc == 0)
	return 0;
    int i;
    for (i=1; i<argc; i++)
    {
	time_t t1, t2;
	time(&t1);
	int solution = N_Queens(atoi(argv[i]));
	time(&t2);
	printf("\n%d sided board\n", atoi(argv[i]));
	printResults(&t1, &t2);
	printf("Found %d distinct solutions\n", solution);
    }
//	int i;
//	for (i = 0; i < nCols; i++) {
//		queenRow[i] = -1;
//	}
//	while (currentCol >= 0) {
//		int cow = ProcessColumn();
//		if (!cow) {
//			--currentCol;
//		}
//		if (currentCol == nCols) {
//			++solution;
////			PrintBoard();
//			--currentCol;
//		}
//	}
    return 0;
}

