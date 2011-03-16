def Euler_57(exp=1000):
    '''Returns the number of expansions up to the input where the num
        is greater than the denominator
    '''
    n1, n2 = 3, 7
    d1, d2 = 2, 5
    count = 0
    exp -= 2
    while exp is not 0:
        exp -= 1
        n1, n2 = n2, n2 * 2 + n1
        d1, d2 = d2, d2 * 2 + d1
        if (len(str(n2)) > len(str(d2))):
            count += 1
    return count

if __name__ == '__main__':
    print(Euler_57());
