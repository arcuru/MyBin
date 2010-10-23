import sys
def printPossibleWords( input ):
    input=input.lower()
    file = open('dictionary.txt')
    for line in file:
        word=line.strip()
        word=word.lower()
        if len(input)!=len(word):
            continue
        matching=True
        for i in range(0,len(input)):
            if input[i].isalpha():
                if input[i]!=word[i]:
                    matching=False
        if matching==True:
            print word

for arg in sys.argv:
    printPossibleWords(arg)

