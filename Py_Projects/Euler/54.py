def Euler_54(i_file="54.txt"):
	'''Determine how many hands of poker player 1 wins
	'''
	def import_line(i_file):
		with open(i_file, encoding="utf-8") as poker_file:
			for line in poker_file:
				cards = line.split()
				p1_vals = [card[0] for card in cards[:5]]
				p1_suit = {card[1] for card in cards[:5]}
				p2_vals = [card[0] for card in cards[5:]]
				p2_suit = {card[1] for card in cards[5:]}
				yield p1_vals, p1_suit, p2_vals, p2_suit
	
	def hand_value(values, suits):
		flush = False
		if len(set(suits)) == 1:
			flush = True
		pairs, trip, quad = False, False, False
		val_dict = {x:values.count(x) for x in values}

	p1_wins = 0
	for p1_v, p1_s, p2_v, p2_s in import_line(i_file):
		p1 = hand_value(p1_v, p1_s)
		p2 = hand_value(p2_v, p2_s)
		if p1[0] == p2[0]:
			if p1[1] > p2[1]:
				p1_wins += 1
		else if p1[0] > p2[0]:
			p1_wins += 1
	
	return p1_wins

if __name__ == '__main__':
	print(Euler_54())
