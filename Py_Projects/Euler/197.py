def Euler_197(end=10**12):
	''' Returns the value of u(n) + u(n+1) for n = input
	     sequence is defined below
	'''
	step = lambda x : int(2**(30.403243784 - x**2)) * 10**(-9)
	u = -1
	for i in range(0,end,2):
		uu = step(u)
		uu = step(uu)
		if abs(u-uu) < 10**-10:
			break
		u = uu
	if 0 != end%2:
			u = step(u)
	return round(u + step(u), 9)

if __name__ == '__main__':
	print(Euler_197())

