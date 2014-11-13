import gmpy2
def Euler_104():
	'''Find the index of the first Fibonacci number with first and last 9 digits pandigital
	'''
	# a is lower fib number, b is higher fib number
	# index is the fibonacci index of b

	(a, b, index) = (gmpy2.mpz(1), gmpy2.mpz(1), 2)
	while True:
		(a, b, index) = (b, a + b, index + 1)
		low_num = b % (10 ** 9)
		high_num = b
		if isPandigital(low_num):
			while high_num > 10 ** 9:
				if high_num > 10 ** 50:
					if high_num > 10 ** 500:
						if high_num > 10 ** 5000:
							high_num //= 10 ** 4500
						high_num //= 10 ** 450
					high_num //= 10 ** 41
				high_num //= 10
			if isPandigital(high_num):
				return index

def isPandigital(number):
	'''Return true if a number is pandital (contains 1-9 exactly once)
		False otherwise
	'''
	if number < 10 ** 8 or number >= 10 ** 9:
		return False
	count_list = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
	while number > 0:
		if number % 10 == 0:
			return False
		if count_list[(number % 10)]  == 0:
			count_list[(number % 10)] = 1
			number //= 10
		else:
			return False
	return True

if __name__ == '__main__':
	print(Euler_104())
