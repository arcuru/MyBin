#include "Sudoku.h"
#include "Timer.h"
#include <iostream>
#include <cstring>
using namespace std;

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
	Sudoku s;
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
    float start=0, end=0, tmpstart=0, tmpend=0, max = 0;
    int maxprob = 0;
	Timer t1;
	t1.Start();
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
		Timer t;
		t.Start();
        puzzle = s.Solve(puzzle);
		t.End();
        if (t.get_Time() > max) {
            max = t.get_Time();
            maxprob = puzzleid;
        }
        //PrintSudoku(puzzle);
        if (s.Check(puzzle) == true) {
            //Puzzle solved correctly
            ++solved;
            if (verbose == 1) {
                fprintf(stdout, "Solved puzzle %d\n", puzzleid);
            }
            continue;
        } else {
            fprintf(stderr, "Problem solving puzzle %d\n", puzzleid);
            //PrintSudoku(puzzle);
            continue;
        }
    } while (((c = fgetc(source)) != EOF) && (++puzzleid <= endcount));
    //end = GetSecondClock();
	t1.End();
    double time = t1.get_Time();
    if (time < 0)
        time *= -1;
    fprintf(stdout, "Solved %d out of %d puzzles\nTotal Time: %.3f s\n", solved, puzzleid
            - 1, time);
    fprintf(stdout, "Average Time: %.3f s\n", time / (double)solved);
    fprintf(stdout, "Max Time: %.3f\nMax Problem: %d\n", max, maxprob);
    return 0;
}
