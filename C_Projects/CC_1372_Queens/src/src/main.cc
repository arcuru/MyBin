// Implementation of the eight queens problem
// Patrick Jackson

//#include "cs1372.h"
#include <stdio.h>
#include <time.h>

const int nRows = 14;
const int nCols = nRows;
int currentCol = 0;
int Board[nRows][nCols];
int queenRow[nCols]; //Each place in the array denotes a column, 
//the value stored is the row of the Queen

// isLegal - Return true if a queen can legally be placed on a row, column
bool isLegal(int row, int col) {
	if (Board[row][col] == 0) {
		return true;
	}
	return false;
}

// PrintBoard - Print the board (presumably a solution) in the format
//              given in the assignment description.
void PrintBoard() {
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

// Queen - Adds/Subtracts stuff to all the places the Queen at row, col can attack
void Queen(int row, int col, bool in) {
	int plus;
	if (in) {
		plus = 1;
	}
	if (!in) {
		plus = -1;
	}

	//Diags
	//Up Left
	int r = row - 1;
	int c = col - 1;
	while ((r >= 0) && (c >= 0)) {
		Board[r][c] += plus;
		r--;
		c--;
	}
	//Up Right
	r = row - 1;
	c = col + 1;
	while ((r >= 0) && (c < nCols)) {
		Board[r][c] += plus;
		r--;
		c++;
	}
	//Down Left
	r = row + 1;
	c = col - 1;
	while ((r < nRows) && (c >= 0)) {
		Board[r][c] += plus;
		r++;
		c--;
	}
	//Down Right
	r = row + 1;
	c = col + 1;
	while ((r < nRows) && (c < nCols)) {
		Board[r][c] += plus;
		r++;
		c++;
	}

	//Cross
	//Up
	r = row - 1;
	while (r >= 0) {
		Board[r][col] += plus;
		r--;
	}
	//Down
	r = row + 1;
	while (r < nRows) {
		Board[r][col] += plus;
		r++;
	}
	//Left
	c = col - 1;
	while (c >= 0) {
		Board[row][c] += plus;
		c--;
	}
	//Right
	c = col + 1;
	while (c < nCols) {
		Board[row][c] += plus;
		c++;
	}
}

// Place - Place a queen on a given row,column
void Place(int row) {
	Board[row][currentCol] = -1;
	queenRow[currentCol] = row;
	Queen(row, currentCol, true);
	currentCol++;
}

// Remove - Remove the queen from currentCol
void Remove() {
	int row = queenRow[currentCol];
	int col = currentCol;
	Board[row][col] = 0;
	Queen(row, col, false);
	queenRow[currentCol] = -1;
}

// ProcessColumn - Find next legal location in the specified column, place
//                 queen there, and advance to next column.
bool ProcessColumn() {
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
    int hours , mins, intsecs;

    //printf("End: \t%s", ctime(pt2));
    secs = difftime(*pt2, *pt1);
    intsecs = (int)secs;
    printf("Calculations took %d second%s.\n", intsecs, (intsecs == 1 ? "" : "s"));

    /* Print hours, minutes, seconds */
    hours = intsecs/3600;
    intsecs -= hours * 3600;
    mins = intsecs/60;
    intsecs -= mins * 60;
    if (hours > 0 || mins > 0)
    {
        printf("Equals ");
        if (hours > 0)
        {
            printf("%d hour%s, ", hours, (hours == 1) ? "" : "s");
        }
        if (mins > 0)
        {
            printf("%d minute%s and ", mins, (mins == 1) ? "" : "s");
        }
        printf("%d second%s.\n", intsecs, (intsecs == 1 ? "" : "s"));

    }
}


// Main program here.
int main() {
	time_t t1,t2;
	time(&t1);
	int i;
	static int solution = 0;
	for (i = 0; i < nCols; i++) {
		queenRow[i] = -1;
	}
	while (currentCol >= 0) {
		bool cow = ProcessColumn();
		if (!cow) {
			--currentCol;
		}
		if (currentCol == nCols) {
			++solution;
			//PrintBoard();
			--currentCol;
		}
	}
	time(&t2);
	printResults(&t1,&t2);
	printf("Found %d distinct solutions", solution);
}
