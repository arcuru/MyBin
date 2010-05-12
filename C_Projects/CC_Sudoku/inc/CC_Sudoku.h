#ifndef SUDOKU_CC_H
#define SUDOKU_CC_H
/*
#include <stdio.h>
#include <stdlib.h>
#include "CC_Utils.h"
*/
#define SUDOKU_INDEX(r,c)	((r)*(9)+(c))
int* SudokuSolver(int*);
void PrintSudoku(int*);

#endif
