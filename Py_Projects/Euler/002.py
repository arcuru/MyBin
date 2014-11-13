def Euler_2(top=4000000):
	'''Find the sum of all even-valued terms in the Fibonacci sequence
	that do not exceed the input
	'''
	(a, b) = (1, 2)
	total = b
	while b <= top:
		(a, b) = (b, a+b)
		(a, b) = (b, a+b)
		(a, b) = (b, a+b)
		if  b <= top:
			total += b
	return total

if __name__ == '__main__':
	print(Euler_2())
