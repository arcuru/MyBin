from functools import reduce
def Euler_20(limit=100):
    '''Returns the sum of the digits in limit!
    '''
    factorial = reduce(lambda i,j: i*j, range(1,limit))
    total = 0
    while factorial != 0:
        total += factorial % 10
        factorial //= 10
    return total


if __name__ == '__main__':
    print(Euler_20())

