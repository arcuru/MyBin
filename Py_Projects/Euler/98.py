import itertools
import gmpy2
def Euler_98(i_file='98.txt'):
	'''Find the largest square anagram in the given text file
		The anagram of the word must exist in the text file
	'''
	with open(i_file, encoding="utf-8") as data:
		for a_line in data:
			word_tuple = tuple([x.strip('"') for x in a_line.split('","')])
	
	if not word_tuple:
		return None
	word_list = [x for x in reversed(sorted(list(word_tuple), key=len))]
	dict_list = [{a:x.count(a) for a in x} for x in word_list]
	'''
	word_tuple = tuple(word_list)
	for x in range(len(word_tuple)):
		pair = False
		for y in range(len(word_list)):
			if (not word_tuple[x] == word_list[y]) and dict_list[
				print(x,y)
				pair = True
				break
		if not pair:
			word_list.remove(x) 
	
	'''
	print(word_list)
	word_tuple = tuple(word_list)
	max_length = 0
	max_sq = 0
	digits = tuple(ord(c) for c in '0123456789')
	for index in range(word_tuple):
		word = word_tuple[index]
		tmp = dict_list[index]
		dict_list[index] = 0
		if not tmp in dict_list:
			break
		if len(word) < max_length:
			break
		letter_set = tuple(ord(c) for c in set(word))
		for guess in itertools.permutations(digits, len(letter_set)):
			translation = dict(zip(letter_set, guess))
			if not gmpy2.is_square(int(word.translate(translation))):
				continue
			word_dict = {x:word.count(x) for x in word}
			for candidate in word_tuple:
				if word_dict == {x:candidate.count(x) for x in candidate} and gmpy2.is_square(int(candidate.translate(translation))):
					if int(candidate.translate(translation)) > max_sq:
						max_sq = int(candidate.translate(translation))
						max_length = len(candidate)
					if int(word.translate(translation)) > max_sq:
						max_sq = int(word.translate(translation))
						max_length = len(word)
	
	return max_sq

if __name__ == '__main__':
	print(Euler_98())
