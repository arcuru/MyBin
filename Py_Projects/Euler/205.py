def Euler_205():
	''' Returns the chance that Pete wins in the game
	'''
	def fill_list(array, dice, sides, total):
		for x in range(1, sides+1):
			if dice == 1:
				array[total+x] += 1
			else:
				fill_list(array, dice-1, sides, total + x)

	collist = [0 for x in range(0, 37)]
	petelist = [0 for x in range(0, 37)]
	fill_list(collist, 6, 6, 0)
	fill_list(petelist, 9, 4, 0)
	prob = 0
	for x in range(0,37):
		prob += (petelist[x] / sum(petelist)) * (sum(collist[0:x]) / sum(collist))
	return round(prob*(10**7)) / 10**7

if __name__ == '__main__':
	print(Euler_205())

