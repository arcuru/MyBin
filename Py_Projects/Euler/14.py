from functools import reduce
def Euler_14(maxx=1000000):
    '''Find the number under the input max that produces the longest chain
        while moving along a Collatz sequence
    '''
    def collatz(x):
        '''Returns the number of terms in the collatz sequence of the given number
        '''
        retval = 0
        while x is not 1:
            if (x%2 is 0):
                x //= 2
            else:
                x = 3*x + 1
            retval += 1
        return retval

    clist = [collatz(x) for x in range(500000,maxx)]
    return clist.index(reduce(lambda i,j: max(i,j), clist)) + 500000

if __name__ == '__main__':
    print(Euler_14())
