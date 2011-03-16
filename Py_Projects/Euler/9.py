def Euler_9(limit=1000):
    '''Find the pythagorean triplet for which a+b+c=limit
      Return the product of abc
    '''
    for a in range(1,limit):
        for b in range(a,limit):
            if (a**2 + b**2 == (limit-a-b)**2):
                return a*b*(limit-a-b)

    raise ValueError('No answer for input value')


if __name__ == '__main__':
    print(Euler_9())
