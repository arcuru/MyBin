#ifndef SUDOKU_C_Old_H
#define SUDOKU_C_Old_H
/*
#include <stdio.h>
#include <stdlib.h>
#include "CC_Utils.h"
*/
#ifndef SUDOKU_INDEX
#define SUDOKU_INDEX(r,c)	((r)*(9)+(c))
#endif

//Solves an input puzzle defined by array of length 81
//placement is defined according to SUDOKU_INDEX(r,c)
int* SudokuSolver_Old(int*);

//Prints out sudoku puzzle defined by array of length 81
//placement is defined according to SUDOKU_INDEX(r,c)
void PrintSudoku_Old(int*);

//Checks if puzzle is finished
//according to basic rules
//returns 1 if correct, 0 if wrong
int CheckSudoku_Old(int*);

#endif
