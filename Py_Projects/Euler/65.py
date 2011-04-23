def Euler_65(endPoint=100):
	''' Sum of digits in the numerator for the input #'d convergent
			of the continued fraction for e
	'''
	pos, oldNum, num = 3, 3, 8
	k = 2
	while pos < endPoint:
		pos, oldNum, num = pos+1, num, num+oldNum
		if pos == endPoint:
			break
		pos, oldNum, num = pos+1, num, num+oldNum
		if pos == endPoint:
			break
		pos, oldNum, num = pos+1, num, num*2*k+oldNum
		k += 1
		if pos == endPoint:
			break
	return sum([int(x) for x in str(num)])


if __name__ == '__main__':
	print(Euler_65())

