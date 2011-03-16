f = open('ga.txt')
print('Count statistics in file ga.txt')
words = 0
lines = 0
for line in f:
    words += len(line.split(' '))
    lines += 1

print('The number of words is ' + str(words) + '.')
print('The number of lines is ' + str(lines) + '.')
f.close()

