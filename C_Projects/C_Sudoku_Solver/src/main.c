#include "C_Sudoku.h"
#include "C_Utils.h"
//#include "C_Sudoku_old.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc < 2 || argc > 4) {
        fprintf(stderr, "USAGE: %s [-v] filename [count]\n", argv[0]);
        exit(1);
    }
    int fileint = 1;
    int verbose = 0;
    if (argc >= 3) {
        if (strcmp("-v", argv[1]) == 0) {
            verbose = 1;
            ++fileint;
        }
    }
    int endcount;
    if (argc <= fileint + 1)
        endcount = 100000; //set to current max solvable (using Skip())
    else
        endcount = atoi(argv[fileint + 1]);
    FILE* source = fopen(argv[fileint], "r");
    if (source == NULL) {
        fprintf(stderr, "Error reading file %s\n", argv[fileint]);
        exit(1);
    }
    int c = 0;
    int i, solved = 0, puzzleid = 1; //puzzleid=linenumber=id for debugging
    int* puzzle = (int*) malloc(81 * sizeof (int));
    //int* puzzle2 = (int*) malloc(81 * sizeof(int));
    float start, end, tmpstart, tmpend, max = 0;
    int maxprob = 0;
    start = GetSecondClock();
    do {
        for (i = 0; (i < 81) && ((c = fgetc(source)) != '\n') && (c != EOF); ++i) {
            puzzle[i] = c - '0';
            if (puzzle[i] > 9 || puzzle[i] < 0)
                puzzle[i] = 0;
        }
        if (c == EOF && i != 81)
            break;
        if (i < 81) {
            fprintf(stderr, "Wrong file format in %s", argv
                    [1]);
            exit(1);
        }
        //PrintSudoku(puzzle);
        //memcpy(puzzle2, puzzle, 81 * sizeof(int));
        tmpstart = GetSecondClock();
        puzzle = SudokuSolver(puzzle);
        tmpend = GetSecondClock();
        if (tmpend - tmpstart > max) {
            max = tmpend - tmpstart;
            maxprob = puzzleid;
        }
        //PrintSudoku(puzzle);
        //printf("Old\n");
        //puzzle2=SudokuSolver_Old(puzzle2);
        //PrintSudoku_Old(puzzle2);
        //printf("separate\n");
        if (CheckSudoku(puzzle) == TRUE) {
            //Puzzle solved correctly
            ++solved;
            if (verbose == 1) {
                fprintf(stdout, "Solved puzzle %d\n", puzzleid);
            }
            continue;
        } else {
            fprintf(stderr, "Problem solving puzzle %d\n", puzzleid);
            PrintSudoku(puzzle);
            continue;
        }
    } while (((c = fgetc(source)) != EOF) && (++puzzleid <= endcount));
    end = GetSecondClock();
    float time = end - start;
    if (time < 0)
        time *= -1;
    fprintf(stdout, "Solved %d out of %d puzzles\nTotal Time: %.3f s\n", solved, puzzleid
            - 1, time);
    fprintf(stdout, "Average Time: %.3f s\n", time / solved);
    fprintf(stdout, "Max Time: %.3f\nMax Problem: %d\n", max, maxprob);
    return 0;
}
