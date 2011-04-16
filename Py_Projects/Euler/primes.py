class PrimesIter:

    def __init__(self, max):
        self.max = max

    def __iter__(self):
        self.plist = [2]
        self.first = True
        return self

    def __next__(self):
        if self.first:
            self.first = False
            return self.plist[0]
        for tmp in range(self.plist[-1] + 1, self.max):
            for prime in self.plist:
                if prime**2 > tmp:
                    self.plist.append(tmp)
                    return tmp
                if tmp%prime is 0:
                    break
        raise StopIteration

