from itertools import combinations
def Euler_90():
    '''Returns the number of combinations of two dice that can be used
        to form all the square numbers from 0 - 100
        9's are interchangeable with 6's, but are distinct in counting
    '''
    def formSquares(aa, bb):
        sqset = {'01', '04', '09', '16', '25', '36', '49', '64', '81'}
        a = list(aa)
        b = list(bb)
        if ('6' in a):
            a.append('9')
        elif ('9' in a):
            a.append('6')
        if ('6' in b):
            b.append('9')
        elif ('9' in b):
            b.append('6')
        for x in sqset:
            if (x[0] in a and x[1] in b):
                continue
            if (x[0] in b and x[1] in a):
                continue
            return False
        return True

    vallist = [str(x) for x in range(0,10)]
    combolist = [x for x in combinations(vallist, 6)]
    count = 0
    for a in range(0, len(combolist)):
        for b in range(a, len(combolist)):
            if (formSquares(combolist[a], combolist[b])):
                if (len(combolist[a]) > 6):
                        print(combolist[a])
                count += 1
    return count

if __name__ == '__main__':
    print(Euler_90())
