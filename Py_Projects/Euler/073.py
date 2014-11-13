from fractions import gcd
def Euler_73(d=12000):
	'''Find the number of reduced proper fractions between 1/3
		and 1/2 with a denominator less than d
	'''
	total = 0
	for n in range(1, d+1):
		bot = n//3 + 1
		top = n//2
		if top*2 is n:
			top -= 1
		if top - bot >= 0:
			for x in range(bot,top+1):
				if gcd(x,n) is 1:
					total += 1
	return total

if __name__ == '__main__':
	print(Euler_73())
