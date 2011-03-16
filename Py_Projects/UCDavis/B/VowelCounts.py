f = open('ga.txt')

vowels = 'aeiou'
vowelcount = [0 for x in range(0, len(vowels))]
for line in f:
    for i in range(0, len(vowels)):
        vowelcount[i] += line.count(vowels[i])

print(vowelcount)
f.close()

