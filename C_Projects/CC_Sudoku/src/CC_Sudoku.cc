#include "CC_Sudoku.h"
#include "CC_Utils.h"
#include <stdio.h>
#include <stdlib.h>

//Takes in a pointer to a length 81 array representing a sudoku puzzle
//0's at blank spaces
//Numbering going across then down
//Returns a pointer to a length 81 array with the solved puzzle


static int* Reduction(int*, int);
static int* LonelyNum(int*);
static int* Twos(int*);
static void Remove(int*, int, int);
static int* RemoveRow(int*, int, int);
static int* RemoveCol(int*, int, int);
static int* RemoveBox(int*, int, int, int);
static int RemoveSingle(int, int);
static int* NumFill(int*, int, int);
static bool Check(int*);
static int GetValue(int*);

static int guess = 0;
static int guesslimit = 1;

int* SudokuSolver(int* puzzle) {
	for (int r = 0; r < 9; r++)
		for (int c = 0; c < 9; c++)
			if (puzzle[SUDOKU_INDEX(r,c)] == 0)
				puzzle[SUDOKU_INDEX(r,c)] = 123456789;
	int puzzleValue = GetValue(puzzle);
	int oldValue = 9 * 81;
	while (oldValue > puzzleValue && puzzleValue > 81) {
		oldValue = puzzleValue;
		Reduction(puzzle, GetValue(puzzle));
		if (Check(puzzle))
			return puzzle;
		LonelyNum(puzzle);
		Reduction(puzzle, GetValue(puzzle));
		if (Check(puzzle))
			return puzzle;
		Twos(puzzle);
		puzzleValue = GetValue(puzzle);
	}
	if (Check(puzzle) || guess >= guesslimit)
		return puzzle;
	for (int s = 2; s < 10; s++) {
		for (int i = 0; i < 81; i++) {
			if (Length(puzzle[i]) != s)
				continue;
			int tmp = puzzle[i];
			int* guessing = (int*) (malloc)(sizeof(int) * 81);
			while (tmp) {
				for (int n = 0; n < 81; n++)
					guessing[n] = puzzle[n];
				guessing[i] = tmp % 10;
				guess++;
				guessing = SudokuSolver(guessing);
				guess--;
				if (Check(guessing)) {
					puzzle = guessing;
					return puzzle;
				}
				tmp /= 10;
			}
		}
	}
	if (guess == 0 && !Check(puzzle)) {
		guesslimit++;
		puzzle = SudokuSolver(puzzle);
		return puzzle;
	}
	if (!Check(puzzle))
		return NULL;
	return puzzle;
}

static int* Reduction(int* puzzle, int puzzleValue) {
	int oldValue = 9 * 81;
	while (oldValue > puzzleValue) {
		for (int r = 0; r < 9; r++)
			for (int c = 0; c < 9; c++)
				if (puzzle[SUDOKU_INDEX(r,c)] < 10)
					Remove(puzzle, r, c);
		oldValue = puzzleValue;
		puzzleValue = GetValue(puzzle);
	}
	return puzzle;
}

static int* LonelyNum(int* puzzle) {
	int* rowList = (int*) (malloc)(sizeof(int) * 20);
	int* colList = (int*) (malloc)(sizeof(int) * 20);
	for (int a = 0; a < 9; a++) {
		rowList = Clear(rowList, 20);
		colList = Clear(colList, 20);
		for (int b = 0; b < 9; b++) {
			rowList = NumFill(rowList, puzzle[SUDOKU_INDEX(a,b)], (a * 10) + b);
			colList = NumFill(colList, puzzle[SUDOKU_INDEX(b,a)], (b * 10) + a);
		}
		for (int i = 1; i < 10; i++) {
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
	for (int a = 0; a < 9; a += 3)
		for (int b = 0; b < 9; b += 3) {
			int* boxList = (int*) (malloc)(sizeof(int) * 20);
			for (int r = a; r < a + 3; r++)
				for (int c = b; c < b + 3; c++)
					if (puzzle[SUDOKU_INDEX(r,c)] / 10)
						NumFill(boxList, puzzle[SUDOKU_INDEX(r,c)], (r * 10)
								+ c);
			for (int i = 1; i < 10; i++)
				if (boxList[i] == 1)
					Remove(puzzle, boxList[i + 10] / 10, boxList[i + 10] % 10);
		}
	return puzzle;
}

static int* Twos(int* puzzle) {
	for (int a = 0; a < 9; a++) {
		int* rowList = (int*) (malloc)(sizeof(int) * 9);
		int* colList = (int*) (malloc)(sizeof(int) * 9);
		for (int b = 0; b < 9; b++) {
			rowList[b] = puzzle[SUDOKU_INDEX(a,b)];
			colList[b] = puzzle[SUDOKU_INDEX(b,a)];
		}
		for (int i = 0; i < 9; i++)
			for (int n = i + 1; n < 9; n++) {
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
	for (int a = 0; a < 9; a += 3)
		for (int b = 0; b < 9; b += 3) {
			int* boxList = (int*) (malloc)(sizeof(int) * 9);
			for (int r = a; r < a + 3; r++)
				for (int c = b; c < b + 3; c++)
					boxList[(r - a) * 3 + (c - b)] = puzzle[SUDOKU_INDEX(r,c)];
			for (int i = 0; i < 9; i++)
				for (int n = i + 1; n < 9; n++)
					if (boxList[i] == boxList[n] && boxList[i] < 100) {
						RemoveBox(puzzle, a, b, boxList[i] / 10);
						RemoveBox(puzzle, a, b, boxList[i] % 10);
						puzzle[SUDOKU_INDEX((i/3)+a,(i%3)+b)] = boxList[i];
						puzzle[SUDOKU_INDEX((n/3)+a,(n%3)+b)] = boxList[i];
					}
		}
	return puzzle;
}

static void Remove(int* puzzle, int r, int c) {
	int value = puzzle[SUDOKU_INDEX(r,c)];
	RemoveRow(puzzle, r, value);
	RemoveCol(puzzle, c, value);
	int rowbox = (r / 3) * 3;
	int colbox = (c / 3) * 3;
	RemoveBox(puzzle, rowbox, colbox, value);
	return;
}

static int* RemoveRow(int* puzzle, int r, int value) {
	for (int i = 0; i < 9; i++)
		puzzle[SUDOKU_INDEX(r,i)] = RemoveSingle(puzzle[SUDOKU_INDEX(r,i)],
				value);
	return puzzle;
}

static int* RemoveCol(int* puzzle, int c, int value) {
	for (int i = 0; i < 9; i++)
		puzzle[SUDOKU_INDEX(i,c)] = RemoveSingle(puzzle[SUDOKU_INDEX(i,c)],
				value);
	return puzzle;
}

static int* RemoveBox(int* puzzle, int rowbox, int colbox, int value) {
	for (int i = rowbox; i < rowbox + 3; i++)
		for (int n = colbox; n < colbox + 3; n++)
			puzzle[SUDOKU_INDEX(i,n)] = RemoveSingle(puzzle[SUDOKU_INDEX(i,n)],
					value);
	return puzzle;
}

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

static int* NumFill(int* list, int num, int pos) {
	while (num) {
		list[num % 10]++;
		list[(num % 10) + 10] = pos;
		num /= 10;
	}
	return list;
}

static bool Check(int* puzzle) {
	if (GetValue(puzzle) != 81)
		return false;
	for (int a = 0; a < 9; a++)
		for (int b = 0; b < 9; b++)
			for (int i = b + 1; i < 9; i++) {
				if (puzzle[SUDOKU_INDEX(b,a)] == puzzle[SUDOKU_INDEX(i,a)])
					return false;
				if (puzzle[SUDOKU_INDEX(a,b)] == puzzle[SUDOKU_INDEX(a,i)])
					return false;
			}
	for (int a = 0; a < 9; a += 3)
		for (int b = 0; b < 9; b += 3)
			for (int r = a; r < a + 3; r++)
				for (int c = b; c < b + 3; c++)
					for (int i = a; i < a + 3; i++)
						for (int n = b; n < b + 3; n++)
							if (puzzle[SUDOKU_INDEX(r,c)]
									== puzzle[SUDOKU_INDEX(i,n)] && r != i && c
									!= n)
								return false;
	return true;
}

//Count of numbers left in the puzzle
//81 indicates completion
static int GetValue(int* puzzle) {
	int total = 0;
	for (int i = 0; i < 81; i++)
		total += Length(puzzle[i]);
	return total;
}

void PrintSudoku(int* puzzle) {
	int value = GetValue(puzzle);
	printf("-------------------------");
	for (int r = 0; r < 9; r++) {
		printf("\n| ");
		for (int c = 0; c < 9; c++) {
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
