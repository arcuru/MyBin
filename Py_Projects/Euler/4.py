
def Euler_4(n=3):
	''' Find the largest palindrome made from the product of two
		n-digit numbers
	'''

	# Set an initial value of 0 for maxval
	maxval = 0

	for a in range (10**n-1, 0, -1):
		for b in range (10**n-1, 0, -1):
			if maxval > a*b:
				break
			if a*b == reverseNumber(a*b):
				maxval = a*b
				break
	return maxval

def reverseNumber(number):
	''' Reverses the base 10 representation of a number
		returns the new value

		Requires that number is an integer
	'''

	rev = 0
	while number > 0:
		rev *= 10
		rev += number % 10
		number //= 10
	return rev

if __name__ == '__main__':
	print(Euler_4())
