def Euler_16(exponent=1000):
	'''Sum of the digits of 2 ^ input
	'''
	x = 2 ** exponent
	total = 0
	while x != 0:
		total += x % 10
		x //= 10
	return total


if __name__ == '__main__':
	print(Euler_16())
