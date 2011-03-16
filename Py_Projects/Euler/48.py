from functools import reduce
def Euler_48(base=1000, cut=10):
    '''Find the last cut digits of 1^1 + 2^2 ... + base^base
    '''
    #ans = 0
    #for x in range(1, base+1):
    #	ans += (x ** x)
    #return ans % (10 ** cut)
    return reduce(lambda i,j:i+j,[x**x for x in range(1,base)]) % 10 ** cut

if __name__ == '__main__':
    print(Euler_48())
