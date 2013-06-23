#include "Euler.h"
#include "Sudoku.h"
#include <stdlib.h>
#include <stdio.h>

int64_t Euler_96()
{
    char filepath[100];
    snprintf(filepath, sizeof(filepath), "%s96.txt", EULER_DATA_PATH);
    FILE* data = fopen(filepath, "r");
    if (data == NULL)
        return 0;
    char line[16];
    int total = 0;
    int i;
    int* puzzle = (int*) (malloc)(sizeof(int) * 81);
    for (i = 0; i < 50; i++) {
        if (nullptr == fgets(line, sizeof(line), data)) {
			printf("Error reading from file.\n");
			return -1;
		}
        int n;
        for (n = 0; n < 9; n++) {
			if (nullptr == fgets(line, sizeof(line), data)) {
				printf("Error reading from file.\n");
				return -1;
			}
            int s;
            for (s = 0; s < 9; s++)
                puzzle[SUDOKU_INDEX(n,s)] = (int) (line[s] - '0');
        }

        //PrintSudoku(puzzle);
        puzzle = SudokuSolver(puzzle);
        total += (puzzle[0] * 100) + (puzzle[1] * 10) + puzzle[2];
        //PrintSudoku(puzzle);
    }
    free(puzzle);
    fclose(data);
    return (int64_t) total;
}
