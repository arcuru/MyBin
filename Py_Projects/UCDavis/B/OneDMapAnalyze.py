f = open('onedmap.txt')
tot = 0
c1 = 0
c2 = 0
for line in f:
    tot += float(line.split(':')[1])
    c1 += 1
    c2 += 1 if float(line.split(':')[1]) > .5 else 0
f.close()

print('Average value of iterates -', tot / c1)
print('Fraction above 0.5 -', c2 / c1)

