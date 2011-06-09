def indentFix(filename,spaces=4):
	''' Fix leading indents in a file
	'''
	with open(filename, encoding="utf-8") as data:
		for a_line in data:
			count = 0
			while a_line[count].encode('utf-8') is ' '.encode('utf-8'):
				count += 1
			tabcount = count//spaces
			print('\t'*tabcount + a_line[spaces*tabcount:-1])

import sys
if __name__ == '__main__':
	for arg in sys.argv[1:]:
		print(indentFix(arg))
