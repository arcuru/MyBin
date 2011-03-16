import urllib.request

f = open('ga.txt','w')
for line in urllib.request.urlopen('http://cse.ucdavis.edu/~chaos/courses/nlp/Homework/GettysburgAddress.txt'):
    f.write(str(line).split('\'')[1][:-2])
    f.write('\n')
f.close()

