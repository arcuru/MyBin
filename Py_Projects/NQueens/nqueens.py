import sys
import time

def nqueens(queens=8):
    '''
        Calculate the number of ways to fit a queen in every row and every column
        of a board of size queens X queens

        This is a straight copy of my own C code
        (Bit manipulation is actually quite slow in Python, so perf is poor)
    '''
    maxbit = 1 << queens

    pos = [0] * queens
    diag_right = [0] * queens
    diag_left = [0] * queens
    col = [0] * queens

    count = 0
    lvl = 0
    while lvl >= 0:
        if lvl == 0 and pos[lvl] == queens//2:
            count *= 2
            if queens % 2 == 0:
                break

        if lvl == 0 and pos[lvl] == (queens//2) + 1:
            break

        bit = 1 << pos[lvl]
        while bit < maxbit:
            if (col[lvl] | diag_left[lvl] | diag_right[lvl]) & bit == 0:
                tmpcol = col[lvl] | bit
                tmpdiagl = diag_left[lvl] | bit
                tmpdiagr = diag_right[lvl] | bit
                break
            bit <<= 1
            pos[lvl] += 1

        if bit == maxbit:
            pos[lvl] = 0
            lvl -= 1
        elif lvl == queens - 1:
            count += 1
            pos[lvl] = 0
            lvl -= 1
        else:
            pos[lvl] += 1
            lvl += 1
            col[lvl] = tmpcol
            diag_left[lvl] = tmpdiagl << 1
            diag_right[lvl] = tmpdiagr >> 1

    return count


if __name__ == '__main__':
    if len(sys.argv) > 1:
        for x in sys.argv[1:len(sys.argv)]:
            start = time.clock()
            count = nqueens(int(x))
            print(x, ': ', count, '\nTimer: ', round(time.clock()-start, 3), 's', sep='')
    else:
        start = time.clock()
        count = nqueens()
        print('8: ', count, '\nTimer:', round(time.clock()-start, 3), 's', sep='')
