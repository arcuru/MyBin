def Euler_79(passfile='79.txt'):
    '''Find the secret password, knowing that each line of the input
        file contains an in order subset of the password chars

        TODO: Allow for different lengths of keylogs
    '''
    keylog = list()
    with open(passfile, encoding="utf-8") as data:
        for a_line in data:
            keylog.append(a_line[0:3])

    tree = dict()
    for key in keylog:
        for single in key:
            if (single not in tree):
                tree[single] = [set(), set()]
        tree[key[0]][1].add(key[1])
        tree[key[0]][1].add(key[2])
        tree[key[1]][0].add(key[0])
        tree[key[1]][1].add(key[2])
        tree[key[2]][0].add(key[0])
        tree[key[2]][0].add(key[1])

    passcode = str()
    while len(tree):
        for x in tree:
            if (len(tree[x][0]) == 0):
                passcode += x
                break
        for x in tree:
            tree[x][0].discard(passcode[-1])
        del tree[passcode[-1]]
    return passcode

if __name__ == '__main__':
    print(Euler_79())
