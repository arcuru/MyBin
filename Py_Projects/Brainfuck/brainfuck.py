# Brainfuck interpreter
'''
Brainfuck rules

Consists of an array of bytes and a pointer to the array

Initial conditions:
	Pointer starts at 0
	Array starts with zeroed values and a length of N
		In this case we will use 2^15 (32768)
	Array contains 1-byte values

Clarifications:
	Array indices wrap
		i.e. 0-1 = End of Array
	Array values wrap

Commands:
	>:
		Increment Pointer
	<:
		Decrement Pointer
	+:
		Add 1 to value at pointer
	-:
		Subtract 1 from value at pointer
	[:
		Jump to corresponding ']' if value at pointer is 0
	]:
		Jump back to matching '[' if value at pointer is not 0
	.:
		Print the character at the pointer
	,:
		Accept one character of input into the current location


'''
import sys
class Brainfuck:
	''' Brainfuck interpreter class
		Encapsulates several methods for working with a brainfuck program
	'''

	def __init__(self, filename):
		self.arraylength = 2**15 # Size of array is 32k
		self.maxvalue = 0x100 # 1-byte max value in each place
		self.array = [0 for x in range(0, self.arraylength)]
		self.pointer = 0
		f = open(filename, 'r')
		self.prog = f.read()
		f.close()
		self.progplace = 0
	
	def step(self):
		''' Perform one step of the brainfuck function on the next pointer and execution point
			End condition:
				Returns 0 if executed correctly
				Returns 1 if computation is complete
				Returns 2 if error
		'''
		current = self.prog[self.progplace]
		self.progplace += 1
		if '>' == current:
			self.pointer += 1
			self.pointer %= self.arraylength

		elif '<' == current:
			self.pointer -= 1
			self.pointer %= self.arraylength

		elif '+' == current:
			self.array[self.pointer] += 1
			self.array[self.pointer] %= self.maxvalue

		elif '-' == current:
			self.array[self.pointer] -= 1
			self.array[self.pointer] %= self.maxvalue

		elif '[' == current:
			# Jump to matching ']' if current place == 0
			if self.array[self.pointer] == 0:
				# Find matching thing
				self.progplace
				check = 1
				while check > 0:
					if self.prog[self.progplace] == '[':
						check += 1
					elif self.prog[self.progplace] == ']':
						check -= 1
					self.progplace += 1

		elif ']' == current:
			# Jump to matching '[' if current place != 0
			if self.array[self.pointer] != 0:
				# Find matching thing
				self.progplace -= 2 # Go one place behind current ']'
				check = 1
				while check > 0:
					if self.prog[self.progplace] == ']':
						check += 1
					elif self.prog[self.progplace] == '[':
						check -= 1
					self.progplace -= 1
				self.progplace += 2

		elif '.' == current:
			# Print a character
			sys.stdout.write(chr(self.array[self.pointer]))

		elif ',' == current:
			# Read a character
                        self.array[self.pointer] = ord(raw_input("\nGimme a character: ")[0])
                        

		elif '=' == current:
			return 1

		else:
			# Nothing should happen
			# If debug print current
			print 'No Command'

		if self.progplace == len(self.prog):
			return 1
		return 0

	def run(self):
		# Run until the end
		ret = self.step()
		while ret == 0:
			ret = self.step()
			#self.printState()
	
	def printState(self):
		print 'State:'
		print self.array[0:10]
		print self.pointer
		print self.progplace
		print self.array[self.pointer]
		print self.prog[self.progplace]
	

if __name__ == '__main__':
	interp = Brainfuck('hello.bf')
	#interp.printState()
	interp.run()


