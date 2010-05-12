#include "C_Euler.h"
#include "C_Sudoku.h"
#include <stdlib.h>
#include <stdio.h>

int64 Euler_96()
{
    char filepath[100];
    snprintf(filepath, sizeof(filepath), "%s96.txt", C_EULER_DATA_PATH);
    FILE* data = fopen(filepath, "r");
    if (data == NULL)
        return 0;
    char line[16];
    int total = 0;
    char* abc;
    int i;
    for (i = 0; i < 50; i++) {
        abc = fgets(line, sizeof(line), data);
        int* puzzle = (int*) (malloc)(sizeof(int) * 81);
        int n;
        for (n = 0; n < 9; n++) {
            abc = fgets(line, sizeof(line), data);
            int s;
            for (s = 0; s < 9; s++)
                puzzle[SUDOKU_INDEX(n,s)] = (int) (line[s] - '0');
        }

        //PrintSudoku(puzzle);
        puzzle = SudokuSolver(puzzle);
        total += (puzzle[0] * 100) + (puzzle[1] * 10) + puzzle[2];
        //PrintSudoku(puzzle);
    }
    fclose(data);
    return (int64) total;
}
