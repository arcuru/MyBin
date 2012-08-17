#ifndef SUDOKU_H
#define SUDOKU_H

#define SUDOKU_INDEX(r,c)	((r)*(9)+(c))

// Define only if we are not debugging
//#define NDEBUG

//Solves an input puzzle defined by array of length 81
//placement is defined according to SUDOKU_INDEX(r,c)
int* SudokuSolver(int*);

//Prints out sudoku puzzle defined by array of length 81
//placement is defined according to SUDOKU_INDEX(r,c)
void PrintSudoku(int*);

//Checks if puzzle is finished
//according to basic rules
//returns 1 if correct, 0 if wrong
int CheckSudoku(int*);

#endif
