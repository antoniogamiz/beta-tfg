from typing import Tuple
import numpy as np
import sys
from functools import reduce


class LSFRG():
    def __init__(self, polynomial: Tuple[int], userandomseed: int = False):
        if userandomseed:
            self.initstate = np.random.randint(0, 2, np.max(polynomial))
        else:
            self.initstate = np.ones(np.max(polynomial))

        self.state = self.initstate.astype(int)
        self.polynomial = polynomial
        self.polynomial.sort(reverse=True)
        self.seq = np.empty([1], dtype=int)

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


lfsrg = LSFRG([int(sys.argv[1]), int(sys.argv[2])])

for i in range(lfsrg.expectedPeriod()):
    lfsrg.next()

print(reduce(lambda a, b: str(a)+str(b), lfsrg.seq))
