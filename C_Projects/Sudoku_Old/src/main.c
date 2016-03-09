#include "Sudoku.h"
#include "Utils.h"
#include <stdio.h>
#include <stdlib.h>

//Takes in a pointer to a length 81 array representing a sudoku puzzle
//0's at blank spaces
//Numbering going across then down
//Returns a pointer to a length 81 array with the solved puzzle

static int* SolvingIt(int*);
static int* Reduction(int*, int);
static int* LonelyNum(int*);
static int* Twos(int*);
static void Remove(int*, int, int);
static int* RemoveRow(int*, int, int);
static int* RemoveCol(int*, int, int);
static int* RemoveBox(int*, int, int, int);
static int RemoveSingle(int, int);
static int* NumFill(int*, int, int);
static int GetValue(int*);

static int guess;
static int guesslimit;

int* SudokuSolver(int* puzzle) {
	//do init stuff, fixes issue with running multiple times
	guess = 0;
	guesslimit = 1;
	return SolvingIt(puzzle);
}

static int* SolvingIt(int* puzzle) {
	int r, c;
	for (r = 0; r < 9; r++)
		for (c = 0; c < 9; c++)
			if (puzzle[SUDOKU_INDEX(r,c)] == 0)
				puzzle[SUDOKU_INDEX(r,c)] = 123456789;
	int puzzleValue = GetValue(puzzle);
	int oldValue = 9 * 81;
	while (oldValue > puzzleValue && puzzleValue > 81) {
		oldValue = puzzleValue;
		//printf("1: %d\n", GetValue(puzzle));
		Reduction(puzzle, GetValue(puzzle));
		//printf("2: %d\n", GetValue(puzzle));
		if (CheckSudoku(puzzle))
			return puzzle;

		//PrintSudoku(puzzle);
		puzzleValue=GetValue(puzzle);
		while(true){
			LonelyNum(puzzle);
			if (GetValue(puzzle)==puzzleValue)
				break;
			else
				puzzleValue=GetValue(puzzle);
		}
		//printf("3: %d\n", GetValue(puzzle));
		//PrintSudoku(puzzle);
		//return NULL;
		Reduction(puzzle, GetValue(puzzle));
		if (CheckSudoku(puzzle))
			return puzzle;
		Twos(puzzle);
		puzzleValue = GetValue(puzzle);
	}
	if (CheckSudoku(puzzle) || guess >= guesslimit)
		return puzzle;
	int s, i;
	for (s = 2; s < 10; s++) {
		for (i = 0; i < 81; i++) {
			if (Length_int(puzzle[i]) != s)
				continue;
			int tmp = puzzle[i];
			int* guessing = (int*) (malloc)(sizeof(int) * 81);
			while (tmp) {
				int n;
				for (n = 0; n < 81; n++)
					guessing[n] = puzzle[n];
				guessing[i] = tmp % 10;
				guess++;
				guessing = SolvingIt(guessing);
				guess--;
				if (CheckSudoku(guessing)) {
					puzzle = guessing;
					return puzzle;
				}
				tmp /= 10;
			}
			free(guessing);
		}
	}
	if (guess == 0 && !CheckSudoku(puzzle)) {
		guesslimit++;
		puzzle = SolvingIt(puzzle);
		return puzzle;
	}
	if (!CheckSudoku(puzzle))
		return NULL;
	return puzzle;
}

//Finds all positions where 1 # is left
//Take out that number from all other positions
static int* Reduction(int* puzzle, int puzzleValue) {
	int oldValue = 9 * 81;
	while (oldValue > puzzleValue) {
		int r, c;
		for (r = 0; r < 9; r++)
			for (c = 0; c < 9; c++)
				if (puzzle[SUDOKU_INDEX(r,c)] < 10)
					Remove(puzzle, r, c);
		oldValue = puzzleValue;
		puzzleValue = GetValue(puzzle);
	}
	return puzzle;
}

//Checks for a number that is alone in a column, row, or box
//Simplifies the case where multiple #'s are left at a single
//place, but one of them is the only of its kind in the area
static int* LonelyNum(int* puzzle) {
	int* rowList = (int*) (malloc)(sizeof(int) * 20);
	int* colList = (int*) (malloc)(sizeof(int) * 20);
	int a, b, i;
	for (a = 0; a < 9; a++) {
		Clear(rowList, 20);
		Clear(colList, 20);
		for (b = 0; b < 9; b++) {
			rowList = NumFill(rowList, puzzle[SUDOKU_INDEX(a,b)], (a * 10) + b);
			colList = NumFill(colList, puzzle[SUDOKU_INDEX(b,a)], (b * 10) + a);
		}
		for (i = 1; i < 10; i++) {
			if (rowList[i] == 1) {
				puzzle[SUDOKU_INDEX(rowList[i+10]/10,rowList[i+10]%10)] = i;
				Remove(puzzle, rowList[i + 10] / 10, rowList[i + 10] % 10);
			}
			if (colList[i] == 1) {
				puzzle[SUDOKU_INDEX(colList[i+10]/10,colList[i+10]%10)] = i;
				Remove(puzzle, colList[i + 10] / 10, colList[i + 10] % 10);
			}
		}
	}
	int r, c;
	int* boxList = (int*) (malloc)(sizeof(int) * 20);
	for (a = 0; a < 9; a += 3)
		for (b = 0; b < 9; b += 3) {
			for (r = a; r < a + 3; r++)
				for (c = b; c < b + 3; c++)
					if (puzzle[SUDOKU_INDEX(r,c)] / 10)
						NumFill(boxList, puzzle[SUDOKU_INDEX(r,c)], (r * 10)
								+ c);
			for (i = 1; i < 10; i++)
				if (boxList[i] == 1)
					Remove(puzzle, boxList[i + 10] / 10, boxList[i + 10] % 10);
		}
	free(rowList);
	free(colList);
	free(boxList);
	return puzzle;
}

static int* Twos(int* puzzle) {
	int a, b, i, n;
	int* rowList = (int*) (malloc)(sizeof(int) * 9);
	int* colList = (int*) (malloc)(sizeof(int) * 9);
	for (a = 0; a < 9; a++) {
		for (b = 0; b < 9; b++) {
			rowList[b] = puzzle[SUDOKU_INDEX(a,b)];
			colList[b] = puzzle[SUDOKU_INDEX(b,a)];
		}
		for (i = 0; i < 9; i++)
			for (n = i + 1; n < 9; n++) {
				if (rowList[i] == rowList[n] && rowList[i] < 100) {
					RemoveRow(puzzle, a, rowList[i] / 10);
					RemoveRow(puzzle, a, rowList[i] % 10);
					puzzle[SUDOKU_INDEX(a,i)] = rowList[i];
					puzzle[SUDOKU_INDEX(a,n)] = rowList[i];
				}
				if (colList[i] == colList[n] && colList[i] < 100) {
					RemoveCol(puzzle, a, colList[i] / 10);
					RemoveCol(puzzle, a, colList[i] % 10);
					puzzle[SUDOKU_INDEX(i,a)] = colList[i];
					puzzle[SUDOKU_INDEX(n,a)] = colList[i];
				}
			}
	}
	int r, c;
	int* boxList = (int*) (malloc)(sizeof(int) * 9);
	for (a = 0; a < 9; a += 3)
		for (b = 0; b < 9; b += 3) {
			for (r = a; r < a + 3; r++)
				for (c = b; c < b + 3; c++)
					boxList[(r - a) * 3 + (c - b)] = puzzle[SUDOKU_INDEX(r,c)];
			for (i = 0; i < 9; i++)
				for (n = i + 1; n < 9; n++)
					if (boxList[i] == boxList[n] && boxList[i] < 100) {
						RemoveBox(puzzle, a, b, boxList[i] / 10);
						RemoveBox(puzzle, a, b, boxList[i] % 10);
						puzzle[SUDOKU_INDEX((i/3)+a,(i%3)+b)] = boxList[i];
						puzzle[SUDOKU_INDEX((n/3)+a,(n%3)+b)] = boxList[i];
					}
		}
	free(rowList);
	free(colList);
	free(boxList);
	return puzzle;
}

//Removes a number from a row/col/box once it is found
static void Remove(int* puzzle, int r, int c) {
	int value = puzzle[SUDOKU_INDEX(r,c)];
	RemoveRow(puzzle, r, value);
	RemoveCol(puzzle, c, value);
	int rowbox = (r / 3) * 3;
	int colbox = (c / 3) * 3;
	RemoveBox(puzzle, rowbox, colbox, value);
	return;
}

//Removes a number from the specified row
static int* RemoveRow(int* puzzle, int r, int value) {
	int i;
	for (i = 0; i < 9; i++)
		puzzle[SUDOKU_INDEX(r,i)] = RemoveSingle(puzzle[SUDOKU_INDEX(r,i)],
				value);
	return puzzle;
}

//Removes a number from the specified column
static int* RemoveCol(int* puzzle, int c, int value) {
	int i;
	for (i = 0; i < 9; i++)
		puzzle[SUDOKU_INDEX(i,c)] = RemoveSingle(puzzle[SUDOKU_INDEX(i,c)],
				value);
	return puzzle;
}

//Removes a number from the specified box
//box is defined by lowest value row & column
//i.e. middle box is 3,3
static int* RemoveBox(int* puzzle, int rowbox, int colbox, int value) {
	int i, n;
	for (i = rowbox; i < rowbox + 3; i++)
		for (n = colbox; n < colbox + 3; n++)
			puzzle[SUDOKU_INDEX(i,n)] = RemoveSingle(puzzle[SUDOKU_INDEX(i,n)],
					value);
	return puzzle;
}

//Removes a number from the possible list at a single place
//Takes in the value at that place and the value to remove
static int RemoveSingle(int big, int single) {
	if (big < 10)
		return big;
	int tmp = big;
	int place = 1;
	while (tmp) {
		if (tmp % 10 == single)
			break;
		place *= 10;
		tmp /= 10;
	}
	if (tmp % 10 != single)
		return big;
	tmp = big % place;
	big -= (single * place) + tmp;
	big /= 10;
	big += tmp;
	return big;
}

//Fills in a list with all the numbers in an int
//with the number storage format
//not sure the exact usage
static int* NumFill(int* list, int num, int pos) {
	while (num) {
		list[num % 10]++;
		list[(num % 10) + 10] = pos;
		num /= 10;
	}
	return list;
}

//Checks if puzzle is finished
//according to basic rules
int CheckSudoku(int* puzzle) {
	if (puzzle==NULL)
		return false;
	if (GetValue(puzzle) != 81)
		return false;
	int a, b, i, r, c, n;
	for (a = 0; a < 9; a++)
		for (b = 0; b < 9; b++)
			for (i = b + 1; i < 9; i++) {
				if (puzzle[SUDOKU_INDEX(b,a)] == puzzle[SUDOKU_INDEX(i,a)])
					return false;
				if (puzzle[SUDOKU_INDEX(a,b)] == puzzle[SUDOKU_INDEX(a,i)])
					return false;
			}
	for (a = 0; a < 9; a += 3)
		for (b = 0; b < 9; b += 3)
			for (r = a; r < a + 3; r++)
				for (c = b; c < b + 3; c++)
					for (i = a; i < a + 3; i++)
						for (n = b; n < b + 3; n++)
							if (puzzle[SUDOKU_INDEX(r,c)]
									== puzzle[SUDOKU_INDEX(i,n)] && r != i && c
									!= n)
								return false;
	for (a = 0; a < 81; ++a)
		if (puzzle[a] == 0)
			return false;
	return true;
}

//Count of numbers left in the puzzle
//81 indicates completion
static int GetValue(int* puzzle) {
	int total = 0;
	int i;
	for (i = 0; i < 81; i++)
		total += Length_int(puzzle[i]);
	return total;
}

//Prints the puzzle
void PrintSudoku(int* puzzle) {
	int value = GetValue(puzzle);
	printf("Old Solver\n");
	int r, c;
	printf("-------------------------");
	for (r = 0; r < 9; r++) {
		printf("\n| ");
		for (c = 0; c < 9; c++) {
			if (value <= 81)
				printf("%d ", puzzle[SUDOKU_INDEX(r,c)]);
			else
				printf("%9d ", puzzle[SUDOKU_INDEX(r,c)]);
			if (c == 2 || c == 5)
				printf("| ");
		}
		printf("|");
		if (r == 2 || r == 5)
			printf("\n|-------|-------|-------|");

	}
	printf("\n-------------------------\n");
}
