def fib(n):    # write Fibonacci series up to n
    a, b = 0, 1
    i = 0
    while i < n:
        a, b = b, a+b
        i = i + 1
    print b
