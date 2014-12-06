def Euler_15(side=20):
	''' In a 20x20 grid, how many paths are their from one corner to the other?
		Note: This is really the number of paths from corner to opposite 
			corner of a 21x21 node graph
	'''

	# Idea is to create a 21x21 array and iterate over 1 time
	# inserting the number of paths from the original corner to that point

	side += 1
	grid = [[0 for x in range(0,side)] for y in range(0,side)]

	# init to start
	grid[0][0] = 1

	for y in range(0,side):
		for x in range(0,side):

			# Add stuff from the left
			if x > 0:
				grid[x][y] += grid[x-1][y]

			# Add stuff from above
			if y > 0:
				grid[x][y] += grid[x][y-1]

	# Return the stuff at the final corner
	return grid[side-1][side-1]


if __name__ == '__main__':
	print(Euler_15())
