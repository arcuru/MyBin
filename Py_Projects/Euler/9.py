def Euler_9(limit=1000):
    '''Find the pythagorean triplet for which a+b+c=limit
      Return the product of abc
    '''
    for a in range(1,limit):
        for b in range(a,limit):
            if (a*a + b*b == (limit-a-b)*(limit-a-b)):
                return a*b*(limit-a-b)

    raise ValueError('No answer for input value')


if __name__ == '__main__':
    print(Euler_9())
