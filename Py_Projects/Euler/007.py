from primes import PrimesIter
def Euler_7(primeindex=10001):
    '''Return the prime number that is the input prime
    '''
    for tmp in PrimesIter(2**31):
        primeindex -= 1
        if (primeindex == 0):
            return tmp

if __name__ == '__main__':
    print(Euler_7())
