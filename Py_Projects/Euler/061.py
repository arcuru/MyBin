from math import sqrt
def Euler_61():
	''' Find the ordered set of 6 cyclic 4-digit numbers for which each polygonal type:
		(triangle, square, pentagonal, hexagonal, heptagonal, octagonal) is represented
	'''

	# First, generate the lists
	# Note, endpoints are hardcoded
	p3 = [n*(n+1)/2 for n in range(1, 1+int(sqrt(20000)))]
	p4 = [n**2 for n in range(1, 1+int(sqrt(10000)))]
	p5 = [n*(3*n-1)/2 for n in range(1, 1+int(sqrt(20000)))]
	p6 = [n*(2*n-1) for n in range(1, 1+int(sqrt(10000)))]
	p7 = [n*(5*n-3)/2 for n in range(1, 1+int(sqrt(20000)))]
	p8 = [n*(3*n-2) for n in range(1, 1+int(sqrt(10000)))]

	# Check to make sure we have gone far enough
	assert p3[-1] >= 10**4
	assert p4[-1] >= 10**4
	assert p5[-1] >= 10**4
	assert p6[-1] >= 10**4
	assert p7[-1] >= 10**4
	assert p8[-1] >= 10**4

	# Remove all entries that are not 4 digits
	p3 = [n for n in p3 if (n >= 1000 and n < 10000)]
	p4 = [n for n in p4 if (n >= 1000 and n < 10000)]
	p5 = [n for n in p5 if (n >= 1000 and n < 10000)]
	p6 = [n for n in p6 if (n >= 1000 and n < 10000)]
	p7 = [n for n in p7 if (n >= 1000 and n < 10000)]
	p8 = [n for n in p8 if (n >= 1000 and n < 10000)]

	# Make it into a 2D List
	poly = [p3, p4, p5, p6, p7, p8]


	# Remove all the numbers that don't have a corresponding pair
	''' This is not needed, leaving code saved in for posterity
	cycle = removeNonCycles(poly)
	while poly != cycle:
		poly = cycle
		cycle = removeNonCycles(poly)
	'''
	
	for x in range(0, len(poly[0])):
		ans = cycleSearch(poly[0][x], poly[0][x], {0:poly[0][x]}, poly)
		if ans != None:
			break
	
	return sum(ans.values())

def removeNonCycles(start):
	''' Will remove items that don't fit into the cycles
		Needs to be run multiple times to get everything
	'''
	res = [[] for x in range(0, len(start))]
	for x in range(0, len(start)):
		for y in start[x]:
			# Y will be every number in start
			# Iterate again over every number
			for xx in range(0, len(start)):
				for yy in start[xx]:
					if yy//100 == y%100:
						if yy not in res[xx]:
							res[xx].append(yy)
	
	for x in range(0, len(res)):
		res[x].sort()
	return res

def cycleSearch(start, current, history, array):
	''' Searches through the given 2D list for a cycle equal to the
		length of the list
	'''

	# Check end condition
	if len(history) == len(array):
		# Check last cycle
		if start//100 == current%100:
			return history
	
	for x in range(0, len(array)):
		if x not in history:
			for y in array[x]:
				if y//100 == current%100:
					# Found one, recurse here
					history[x] = y
					tmp = cycleSearch(start, y, history, array)
					if tmp != None:
						return tmp
					del history[x]
	
	return None

if __name__ == '__main__':
	print(Euler_61())
