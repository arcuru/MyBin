def Euler_2(top=4000000):
	'''Find the sum of all even-valued terms in the Fibonacci sequence
	that do not exceed the input
	'''
	total = 0
	(a, b) = (1, 1)
	while b <= top:
		(a, b) = (b, a+b)
		if b % 2 == 0 and b <= top:
			total += b
	return total


if __name__ == '__main__':
	print(Euler_2())
