f = open('onedmap.txt','w')
x = 0.3
for i in range(1,101):
    f.write(str(i) + ':' + str(x) + '\n')
    x = 4 * x * ( 1 - x )
f.close()

