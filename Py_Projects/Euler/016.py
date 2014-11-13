def Euler_16(exponent=1000):
	'''Sum of the digits of 2 ^ input
	'''
	return sum([int(digit) for digit in str(2**exponent)])

if __name__ == '__main__':
	print(Euler_16())
