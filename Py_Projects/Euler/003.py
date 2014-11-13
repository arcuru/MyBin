def Euler_3(i_num=600851475143):
	'''Find the largest prime factor of input
	'''
	for x in range(2,1000000):
		while i_num % x == 0:
			i_num /= x
		if i_num == 1 or i_num == x:
			return x
	raise ValueError('input number too large')

if __name__ == '__main__':
	print(Euler_3())
