#include "Sudoku.h"
#include "Utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//Converted to using bits to store values in reductions

//Takes in a pointer to a length 81 array representing a sudoku puzzle
//0's at blank spaces
//Numbering going across then down
//Returns a pointer to a length 81 array with the solved puzzle

typedef struct {
    int16_t* body;
    int value;
} puzzle_struct;

static puzzle_struct* SolvingIt(puzzle_struct*);
static puzzle_struct* Reduction(puzzle_struct*);
static puzzle_struct* LonelyNum(puzzle_struct*);
static puzzle_struct* LonelyBox(puzzle_struct*);
static puzzle_struct* Twos(puzzle_struct*);
static puzzle_struct* Remove(puzzle_struct*, int, int);
static puzzle_struct* RemoveSingle(puzzle_struct*, int, int, int);
static puzzle_struct* RemoveRow(puzzle_struct*, int, int, int*);
static puzzle_struct* RemoveCol(puzzle_struct*, int, int, int*);
static puzzle_struct* RemoveBox(puzzle_struct*, int, int, int, int*);
static int CheckSudoku_Bits(puzzle_struct*);
static int BitCount(int);
static int GetValue(puzzle_struct*);

#ifndef NDEBUG
void PrintSudoku_Bits(puzzle_struct*);
#endif

static int guess;
static int guesslimit;
static const int mask = 0x3FE;


//#define CHEAT	if (puz==nullptr){printf("%d\n",__LINE__);return puz;}

#define ISALONE(x)	(((x)&(x-1))==0)
#define ISOLATE_1(x)	((x)&(-(x)))
#define REMOVE_1(x)	((x)&((x)-1))

//Converts special bitwise thing to decimal
//returns 0 if more than one bit is flipped

static int ConverttoDec(int bit)
{
    if (!ISALONE(bit))
        return 0;
    int count = 0;
    while (bit >>= 1)
        ++count;
    return count;
}

int* SudokuSolver(int* puzzle)
{
    //do init stuff, fixes issue with running multiple times
    guess = 0;
    guesslimit = 1;
    int16_t* bitpuzzle = (int16_t*) malloc(sizeof (int16_t) * 81);
    int r, c;
    for (r = 0; r < 9; r++)
        for (c = 0; c < 9; c++) {
            if (puzzle[SUDOKU_INDEX(r, c)] == 0)
                bitpuzzle[SUDOKU_INDEX(r, c)] = mask;
            else
                bitpuzzle[SUDOKU_INDEX(r, c)] = 1 << puzzle[SUDOKU_INDEX(r, c)];
        }
    puzzle_struct *puz = (puzzle_struct*) malloc(sizeof (puzzle_struct));
    //puz->body=(int*) malloc(sizeof(int)*81);
    puz->body = bitpuzzle;
    puz->value = GetValue(puz);
    puz = SolvingIt(puz);
    //PrintSudoku_Bits(puz);
    if ((puz == nullptr) || (puz->body == nullptr))
        return nullptr;
    for (r = 0; r < 9; ++r)
        for (c = 0; c < 9; ++c) {
            puzzle[SUDOKU_INDEX(r, c)] = ConverttoDec(
                                             puz->body[SUDOKU_INDEX(r, c)]);
        }
    free(puz->body);
    free(puz);
    return puzzle;
}

static puzzle_struct* SolvingIt(puzzle_struct* puz)
{
    int oldValue = 9 * 81;
    puz = Reduction(puz);
    //PrintSudoku_Bits(puz);
    //Main solving loop
    while (oldValue > puz->value && puz->value > 81) {
        oldValue = puz->value;
		puz = LonelyNum(puz);
		if ((puz == nullptr) || (puz->value == 81))
			return puz;
		else if (puz->value < 81) {
			free(puz);
			return nullptr;
		}
		puz = LonelyBox(puz);
		if ((puz == nullptr) || (puz->value == 81))
			return puz;
		else if (puz->value < 81) {
			free(puz);
			return nullptr;
		}
        puz = Twos(puz);
    }
    if (puz->value == 81)
        return puz;
    else if (puz->value < 81) {
		//free(puz);
        return nullptr;
	}
    if (CheckSudoku_Bits(puz) || guess >= guesslimit)
        return puz;
    int s, i, n;
    //PrintSudoku_Bits(puz);
    for (s = 2; s < 10; ++s) {
        for (i = 0; i < 81; ++i) {
            if (BitCount(puz->body[i]) != s)
                continue;
            int tmp = puz->body[i];
            while (tmp) {
                puzzle_struct* guessing = (puzzle_struct*) (malloc) (
                                              sizeof (puzzle_struct));
                guessing->body = (int16_t*) malloc(sizeof (int16_t) * 81);
                for (n = 0; n < 81; ++n)
                    guessing->body[n] = puz->body[n];
                guessing->body[i] = ISOLATE_1(tmp);
                guessing->value = puz->value - s + 1;
                ++guess;
                //PrintSudoku_Bits(guessing);
                guessing = SolvingIt(guessing);
                //puz->value = GetValue(guessing);
                --guess;
                if (CheckSudoku_Bits(guessing)) {
                    puz = guessing;
                    return puz;
                }
                tmp = REMOVE_1(tmp);
                free(guessing);
            }
        }
    }
    if ((guess == 0) && !CheckSudoku_Bits(puz)) {
        guesslimit++;
        puz = SolvingIt(puz);
        return puz;
    }
    if (!CheckSudoku_Bits(puz))
    {
        free(puz);
        return nullptr;
    }
    return puz;
}

//Finds all positions where 1 # is left
//Take out that number from all other positions
//Due implementation of RemoveSingle, this should only
//need to be called at beginning

static puzzle_struct* Reduction(puzzle_struct* puz)
{
    int oldValue = 9 * 81;
    while ((oldValue > puz->value) && (puz->value > 81)) {
        oldValue = puz->value;
        int r, c;
        for (r = 0; r < 9; ++r)
            for (c = 0; c < 9; ++c)
                if (ISALONE(puz->body[SUDOKU_INDEX(r, c)]))
                    puz = Remove(puz, r, c);
    }
    return puz;
}

//Checks for a number in a row/column that is unique within a box
//i.e. - The only 4's in col 5 are in the lowest box, so remove
//all other 4s from that box
//TODO: Reverse of this (search boxes for numbers unique to a row/col)

static puzzle_struct* LonelyBox(puzzle_struct* puz)
{
	uint_fast16_t oldValue = 9 * 81;
	uint_fast16_t boxa[3];
	uint_fast16_t boxb[3];
	uint_fast8_t a, b, i;
    while ((oldValue > puz->value) && (puz->value > 81)) {
        oldValue = puz->value;
		boxa[0] = boxa[1] = boxa[2] = 0;
		boxb[0] = boxb[1] = boxb[2] = 0;
        for (a = 0; a < 9; ++a) {
			for (i = 0; i < 3; ++i) {
				for (b = 0; b < 3; ++b) {
					boxa[i] |= puz->body[SUDOKU_INDEX(a, b+(i*3))];
					boxb[i] |= puz->body[SUDOKU_INDEX(b+(i*3), a)];
				}
			}
			uint_fast16_t xor;
			xor = boxa[0] ^ boxa[1] ^ boxa[2];
			xor ^= (boxa[0] & boxa[1] & boxa[2]);
			// At this point, the only bits in xor that are set are in only one box
			if (0 != xor) {
				for (b = 0; b < 3; ++b) {
					boxa[i];
				}
			}



			boxb_xor = boxb[0] ^ boxb[1] ^ boxb[2];
		}
	}
	return puz;
}

//Checks for a number that is alone in a column, row, or box
//Simplifies the case where multiple #'s are left at a single
//place, but one of them is the only of its kind in the area

static puzzle_struct* LonelyNum(puzzle_struct* puz)
{
    int oldValue = 9 * 81;
    int oncea, onceb, twicea, twiceb;
    int a, b, r, c;
    while ((oldValue > puz->value) && (puz->value > 81)) {
        oldValue = puz->value;
        oncea = 0;
        twicea = 0;
        onceb = 0;
        twiceb = 0;
        //printf("1\n");
        //PrintSudoku_Bits(puzzle);
        for (a = 0; a < 9; ++a) {
            for (b = 0; b < 9; ++b) {
                twicea |= puz->body[SUDOKU_INDEX(a, b)] & oncea;
                oncea |= puz->body[SUDOKU_INDEX(a, b)];
                twiceb |= puz->body[SUDOKU_INDEX(b, a)] & onceb;
                onceb |= puz->body[SUDOKU_INDEX(b, a)];
            }
            if (oncea != mask) // At least one number is missing, return null
                return nullptr;
            if (twicea != oncea) {
                //found one so go back and find and set it
                twicea ^= oncea; //isolate them (reusing variable here)
                //This implementation allows multiples to be found and used
                for (b = 0; b < 9; ++b) {
                    if ((BitCount(puz->body[SUDOKU_INDEX(a, b)]) != 1)
                            && ((puz->body[SUDOKU_INDEX(a, b)] & twicea) != 0)) {
                        puz->value -= BitCount(puz->body[SUDOKU_INDEX(a, b)]);
                        ++puz->value;
                        puz->body[SUDOKU_INDEX(a, b)] &= twicea;
                        if (BitCount(puz->body[SUDOKU_INDEX(a, b)]) != 1)
                            return nullptr;
                        puz = Remove(puz, a, b);
                    }
                }
            }
            twicea = 0;
            oncea = 0;

            if (onceb != mask) // At least one number is missing, return null
                return nullptr;
            if (twiceb != onceb) {
                //found one so go back and find and set it
                twiceb ^= onceb; //isolate them (reusing variable here)
                //This implementation allows multiples to be found and used
                for (b = 0; b < 9; ++b) {
                    if ((BitCount(puz->body[SUDOKU_INDEX(b, a)]) != 1)
                            && ((puz->body[SUDOKU_INDEX(b, a)] & twiceb) != 0)) {
                        puz->value -= BitCount(puz->body[SUDOKU_INDEX(b, a)]);
                        ++puz->value;
                        puz->body[SUDOKU_INDEX(b, a)] &= twiceb;
                        if (BitCount(puz->body[SUDOKU_INDEX(b, a)]) != 1)
                            return nullptr;
                        puz = Remove(puz, b, a);
                    }
                }
            }
            twiceb = 0;
            onceb = 0;

        }
        //Done with rows and columns
        for (a = 0; a < 9; a += 3)
            for (b = 0; b < 9; b += 3) {
                for (r = a; r < a + 3; ++r)
                    for (c = b; c < b + 3; ++c) {
                        twicea |= puz->body[SUDOKU_INDEX(r, c)] & oncea;
                        oncea |= puz->body[SUDOKU_INDEX(r, c)];
                    }
                if (oncea != mask)
                    return nullptr;
                if (twicea != oncea) {
                    //found one so go back and find and set it
                    twicea ^= oncea; //isolate them (reusing variable here)
                    //This implementation allows multiples to be found and used
                    for (r = a; r < a + 3; ++r)
                        for (c = b; c < b + 3; ++c) {
                            if ((BitCount(puz->body[SUDOKU_INDEX(r, c)]) != 1)
                                    && ((puz->body[SUDOKU_INDEX(r, c)] & twicea)
                                        != 0)) {
                                puz->value -= BitCount(
                                                  puz->body[SUDOKU_INDEX(r, c)]);
                                ++puz->value;
                                puz->body[SUDOKU_INDEX(r, c)] &= twicea;
                                if (BitCount(puz->body[SUDOKU_INDEX(r, c)]) != 1)
                                    return nullptr;
                                puz = Remove(puz, r, c);
                            }
                        }
                }
                twicea = 0;
                oncea = 0;
            }
    }
    return puz;
}

//Looks through r,c,b to find two places containing only the same 2 #s
//Removes both those numbers from the given area

static puzzle_struct* Twos(puzzle_struct* puz)
{
    int oldValue = 9 * 81;
    int a, b, n, r, c, i;
    int value;
    int* skip = (int*) calloc(sizeof (int), 9);
    while ((oldValue > puz->value) && (puz->value > 81)) {
        oldValue = puz->value;
        for (a = 0; a < 9; ++a) {
            for (b = 0; b < 9; ++b) {
                if (BitCount(puz->body[SUDOKU_INDEX(a, b)]) == 2)
                    for (n = b + 1; n < 9; ++n) {
                        if (puz->body[SUDOKU_INDEX(a, b)]
                                == puz->body[SUDOKU_INDEX(a, n)]) {
                            value = puz->body[SUDOKU_INDEX(a, b)];
                            skip[b] = 1;
                            skip[n] = 1;
                            puz = RemoveRow(puz, a, ISOLATE_1(value), skip);
                            puz = RemoveRow(puz, a, REMOVE_1(value), skip);
                            skip[b] = 0;
                            skip[n] = 0;
                            break;
                        }
                    }
                if (BitCount(puz->body[SUDOKU_INDEX(b, a)]) == 2)
                    for (n = b + 1; n < 9; ++n) {
                        if (puz->body[SUDOKU_INDEX(b, a)]
                                == puz->body[SUDOKU_INDEX(n, a)]) {
                            value = puz->body[SUDOKU_INDEX(b, a)];
                            skip[b] = 1;
                            skip[n] = 1;
                            puz = RemoveCol(puz, a, ISOLATE_1(value), skip);
                            puz = RemoveCol(puz, a, REMOVE_1(value), skip);
                            skip[b] = 0;
                            skip[n] = 0;
                            break;
                        }
                    }
            }
        }
        //PrintSudoku_Bits(puzzle);

        for (a = 0; a < 9; a += 3)
            for (b = 0; b < 9; b += 3)
                for (r = a; r < a + 3; r++)
                    for (c = b; c < b + 3; c++)
                        if (BitCount(puz->body[SUDOKU_INDEX(r, c)]) == 2)
                            for (i = (r - a) * 3 + (c - b) + 1; i < 9; ++i) {
                                int newr = i / 3 + a;
                                int newc = i % 3 + b;
                                if (puz->body[SUDOKU_INDEX(r, c)]
                                        == puz->body[SUDOKU_INDEX(newr, newc)]) {
                                    value = puz->body[SUDOKU_INDEX(r, c)];
                                    skip[(r - a) * 3 + c - b] = 1;
                                    skip[(newr - a) * 3 + newc - b] = 1;
                                    puz = RemoveBox(puz, a, b,
                                                    ISOLATE_1(value), skip);
                                    puz = RemoveBox(puz, a, b, REMOVE_1(value),
                                                    skip);
                                    skip[(r - a) * 3 + c - b] = 0;
                                    skip[(newr - a) * 3 + newc - b] = 0;
                                    break;
                                }

                            }
    }
    free(skip);
    return puz;
}

//Removes a number from a row/col/box once it is found

static puzzle_struct* Remove(puzzle_struct* puz, int r, int c)
{
    int value = puz->body[SUDOKU_INDEX(r, c)];
    int* skip = (int*) calloc(sizeof (int), 9);
    skip[c] = 1;
    puz = RemoveRow(puz, r, value, skip);
    skip[c] = 0;
    skip[r] = 1;
    puz = RemoveCol(puz, c, value, skip);
    skip[r] = 0;
    int rowbox = (r / 3) * 3;
    int colbox = (c / 3) * 3;
    skip[(r - rowbox) * 3 + c - colbox] = 1;
    puz = RemoveBox(puz, rowbox, colbox, value, skip);
    //puz->body[SUDOKU_INDEX(r,c)] = value;
    free(skip);
    return puz;
}

//Removes value from input row/column
//If this reduced it to a single answer, reduce
//Allows value to be multiple #s

static puzzle_struct* RemoveSingle(puzzle_struct* puz, int r, int c, int value)
{
    int big = puz->body[SUDOKU_INDEX(r, c)];
    if (ISALONE(big))
        return puz;
    //printf("%d\t%d\t",GetValue(puz),puz->value);
    do {
        if ((ISOLATE_1(value) & big) != 0) {
            big ^= ISOLATE_1(value);
            puz->value -= 1;
        }
    } while ((value = REMOVE_1(value)));
    puz->body[SUDOKU_INDEX(r, c)] = big;
    //printf("%d\t%d\n",GetValue(puz),puz->value);
    if (REMOVE_1(big) == 0) {
        //Locked in a new number, so run it through remove
        //Saves having to check with Reduction()
        puz = Remove(puz, r, c);
    }
    //printf("c:%d\n",puz->value);
    return puz;
}

//Removes a number from the specified row

static puzzle_struct* RemoveRow(puzzle_struct* puz, int r, int value, int* skip)
{
    int i;
    for (i = 0; i < 9; ++i) {
        if (skip[i])
            continue;
        puz = RemoveSingle(puz, r, i, value);
    }
    return puz;
}

//Removes a number from the specified column

static puzzle_struct* RemoveCol(puzzle_struct* puz, int c, int value, int* skip)
{
    int i;
    for (i = 0; i < 9; ++i) {
        if (skip[i])
            continue;
        puz = RemoveSingle(puz, i, c, value);
    }
    return puz;
}

//Removes a number from the specified box
//box is defined by lowest value row & column
//i.e. middle box is 3,3
//skip is at (r-rowbox)*3+c-colbox

static puzzle_struct* RemoveBox(puzzle_struct* puz, int rowbox, int colbox,
                                int value, int* skip)
{
    int i, n;
    for (i = rowbox; i < rowbox + 3; ++i)
        for (n = colbox; n < colbox + 3; ++n) {
            if (skip[(i - rowbox) * 3 + n - colbox])
                continue;
            puz = RemoveSingle(puz, i, n, value);
        }
    return puz;
}

//Checks if puzzle is finished
//according to basic rules

static int CheckSudoku_Bits(puzzle_struct* puz)
{
    if (puz == nullptr)
        return FALSE;
    if ((puz->body == nullptr) || (puz->value != 81))
        return FALSE;
	assert( GetValue(puz) == 81 );
    int a, b, r, c;
    int maska = 0, maskb = 0;
    for (a = 0; a < 9; ++a) {
        for (b = 0; b < 9; ++b) {
            maska |= puz->body[SUDOKU_INDEX(a, b)];
            maskb |= puz->body[SUDOKU_INDEX(b, a)];
        }
        if ((maska != mask) || (maskb != mask))
            return FALSE;
        maska = 0;
        maskb = 0;
    }

    for (a = 0; a < 9; a += 3)
        for (b = 0; b < 9; b += 3) {
            for (r = a; r < a + 3; ++r)
                for (c = b; c < b + 3; ++c) {
                    maska |= puz->body[SUDOKU_INDEX(r, c)];
                }
            if (maska != mask)
                return FALSE;
            maska = 0;
        }

    return TRUE;
}

//Returns # of #s left in bitspecification

static int BitCount(int bit)
{
    int count;
    for (count = 0; bit; ++count)
        bit = REMOVE_1(bit);
    return count;
}

//Count of numbers left in the puzzle
//81 indicates completion

static int GetValue(puzzle_struct* puz)
{
    if (puz->body == nullptr)
        return 0;
    int total = 0, tmp = 0, i;
    for (i = 0; i < 81; ++i) {
        tmp = BitCount(puz->body[i]);
        if (tmp == 0)
            return 0;
        total += tmp;
    }
    return total;
}

#ifndef NDEBUG
//Prints the puzzle
//Used only in debugging this code
void PrintSudoku_Bits(puzzle_struct* puz) {
    printf("%d\t%d\n", puz->value, guess);
    int r, c;
    printf("-------------------------");
    for (r = 0; r < 9; ++r) {
        printf("\n| ");
        for (c = 0; c < 9; ++c) {
            if (puz->value <= 81)
                printf("%d ", ConverttoDec(puz->body[SUDOKU_INDEX(r, c)]));
            else {
                int i, tmp = puz->body[SUDOKU_INDEX(r, c)];
                for (i = 9; i > BitCount(tmp); --i) {
                    printf(" ");
                }
                do {
                    printf("%d", ConverttoDec(ISOLATE_1(tmp)));
                } while ((tmp = REMOVE_1(tmp)) != 0);
                printf(" ");
            }
            if (c == 2 || c == 5)
                printf("| ");
        }
        printf("|");
        if (r == 2 || r == 5)
            printf("\n|-------|-------|-------|");

    }
    printf("\n-------------------------\n");
}
#endif

//Checks if puzzle is finished
//according to basic rules
//Took out Value check to avoid reimplementing GetValue
//Not optimized, only used outside this on DEC array

int CheckSudoku(int* puzzle)
{
    if (puzzle == nullptr)
        return FALSE;
    int a, b, i, r, c, n;
    for (a = 0; a < 9; a++)
        for (b = 0; b < 9; b++)
            for (i = b + 1; i < 9; i++) {
                if (puzzle[SUDOKU_INDEX(b, a)] == puzzle[SUDOKU_INDEX(i, a)])
                    return FALSE;
                if (puzzle[SUDOKU_INDEX(a, b)] == puzzle[SUDOKU_INDEX(a, i)])
                    return FALSE;
            }
    for (a = 0; a < 9; a += 3)
        for (b = 0; b < 9; b += 3)
            for (r = a; r < a + 3; ++r)
                for (c = b; c < b + 3; ++c)
                    for (i = a; i < a + 3; ++i)
                        for (n = b; n < b + 3; ++n)
                            if (puzzle[SUDOKU_INDEX(r, c)]
                                    == puzzle[SUDOKU_INDEX(i, n)] && r != i && c
                                    != n)
                                return FALSE;
    for (a = 0; a < 81; ++a)
        if (puzzle[a] == 0)
            return FALSE;
    return TRUE;
}

//Prints the puzzle
//Assumes it is complete

void PrintSudoku(int* puzzle)
{
    int r, c;
    printf("-------------------------");
    for (r = 0; r < 9; r++) {
        printf("\n| ");
        for (c = 0; c < 9; c++) {
            printf("%1d ", puzzle[SUDOKU_INDEX(r, c)]);
            if (c == 2 || c == 5)
                printf("| ");
        }
        printf("|");
        if (r == 2 || r == 5)
            printf("\n|-------|-------|-------|");

    }
    printf("\n-------------------------\n");
}
