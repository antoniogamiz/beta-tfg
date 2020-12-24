from typing import Tuple
import numpy as np
import sys
from functools import reduce
from math import floor


class LSFRG():
    def __init__(self, polynomial: Tuple[int], userandomseed: int = False):
        if userandomseed:
            self.initstate = np.random.randint(0, 2, np.max(polynomial))
        else:
            self.initstate = np.ones(np.max(polynomial))

        self.state = self.initstate.astype(int)
        self.polynomial = polynomial
        self.polynomial.sort(reverse=True)
        self.seq = np.array(0)

    def expectedPeriod(self):
        return 2**self.initstate.shape[0]-1

    def next(self):
        b = np.logical_xor(self.state[self.polynomial[0] - 1],
                           self.state[self.polynomial[1] - 1])

        self.state = np.roll(self.state, 1)
        self.state[0] = b * 1
        if self.seq.size == 0:
            self.seq = self.state[-1]
        else:
            self.seq = np.append(self.seq, self.state[-1])

    def listNumbers(self, l):
        numbers = []
        i, j = 0, l-1
        count = self.expectedPeriod()
        while count >= 0:
            number = 0
            if i < j:
                number = self.seq[i:j]
            else:
                number = np.concatenate(
                    (self.seq[i::], self.seq[0:j]))
            numbers.append(self._toInteger(number))
            i = (i+l) % 32
            j = (j+l) % 32
            count -= 1
        return numbers

    def _toInteger(self, arr):
        return sum(j << i for i, j in enumerate(reversed(arr)))


lfsrg = LSFRG([int(sys.argv[1]), int(sys.argv[2])])

for i in range(lfsrg.expectedPeriod()):
    lfsrg.next()


# print("Sequence: ")
# print(reduce(lambda a, b: str(a)+str(b), lfsrg.seq))
# print(lfsrg.listNumbers(17))

l = 17
d = 6
n = len(lfsrg.listNumbers(l))
Ni = [0] * d
for x in lfsrg.listNumbers(l):
    x = x / float(2**l-1)
    Ni[floor(d*x)] += 1

chisquare = 0
for x in Ni:
    chisquare += x**2
chisquare *= d/float(n)
chisquare -= n

print(chisquare)
