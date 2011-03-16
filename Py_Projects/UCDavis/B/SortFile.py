f = open('ga.txt')

l = list()
for line in f:
    l.append(line[:-1])
l.sort()
f.close()

f = open('ga_sorted.txt','w')
for line in l:
    f.write(line + '\n')
f.close()

