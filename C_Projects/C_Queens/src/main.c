// Implementation of the eight queens problem
// Patrick Jackson

//#include "cs1372.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define true 1
#define false 0
#define nRows 13
#define nCols nRows

int currentCol = 0;
int Board[nRows][nCols];
int queenRow[nCols]; //Each place in the array denotes a column,
//the value stored is the row of the Queen

// isLegal - Return true if a queen can legally be placed on a row, column
int isLegal(int row, int col)
{
//	if (Board[row][col] == 0) {
//		return true;
//	}
//	return false;
    return Board[row][col]==0 ? true : false;
}

// PrintBoard - Print the board (presumably a solution) in the format
//              given in the assignment description.
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

// Place - Place a queen on a given row,column
void Place(int row)
{
    queenRow[currentCol] = row;
    Queen(row, currentCol, true);
    currentCol++;
}

// Remove - Remove the queen from currentCol
void Remove()
{
    int row = queenRow[currentCol];
    int col = currentCol;
    Queen(row, col, false);
    queenRow[currentCol] = -1;
}

// ProcessColumn - Find next legal location in the specified column, place
//                 queen there, and advance to next column.
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

void printResults(time_t* pt1, time_t* pt2)
{
    double secs;
    int hours, mins, intsecs;

    //printf("End: \t%s", ctime(pt2));
    secs = difftime(*pt2, *pt1);
    intsecs = (int) secs;
    printf("Calculations took %d second%s.\n", intsecs, (intsecs == 1 ? ""
            : "s"));

    /* Print hours, minutes, seconds */
    hours = intsecs / 3600;
    intsecs -= hours * 3600;
    mins = intsecs / 60;
    intsecs -= mins * 60;
    if (hours > 0 || mins > 0) {
        printf("Equals ");
        if (hours > 0) {
            printf("%d hour%s, ", hours, (hours == 1) ? "" : "s");
        }
        if (mins > 0) {
            printf("%d minute%s and ", mins, (mins == 1) ? "" : "s");
        }
        printf("%d second%s.\n", intsecs, (intsecs == 1 ? "" : "s"));

    }
}

//Faster Version
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

// Main program here.
int main()
{
    time_t t1, t2;
    time(&t1);
    int solution = 0;
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
    solution=N_Queens(15);
    time(&t2);
    printResults(&t1, &t2);
    printf("Found %d distinct solutions", solution);
    return 0;
}

