# Write a Program to build an Auto-Associative Neural Network (
# Discrete Hopfield Neural Network).
# Use Hebb rule (if two interconnected neurons are both “on” at the same time,
# then the weight between them should be increased.)to store
# vectors (1,1,1,1) and (1,1,-1,-1) in an auto associative neural net.
# a. Find the weight matrix.
# b. Test the net using vector (1,1,1,1) as input.
# c. Test net using (1,1,-1,-1) as input.
# d. Test the net using (1,1,1,0) as input.
# e. (1,4,3,2) is update order for this problem.

import numpy


class Hopfield:
    def __init__(self, ptrns, dimension, updt_ord):
        self.wts = []
        self.dimension = dimension
        for i in range(dimension):
            wt = []
            for j in range(dimension):
                wt.append(0)
            self.wts.append(wt.copy())
        self.ptrns = []
        self.updt_ord = updt_ord
        for i in range(len(ptrns)):
            result = self.biplr_to_bnry(ptrns[i])
            self.ptrns.append(result)
            for i in range(dimension):
                for j in range(dimension):
                    if i != j:
                        self.wts[i][j] += (2 * result[i] - 1) * (2 * result[j] - 1)

    def biplr_to_bnry(self, vec):
        result = vec.copy()
        for i in range(len(vec)):
            if result[i] == -1:
                result[i] = 0
        return result

    def bnry_to_biplr(self, vec):
        result = vec.copy()
        for i in range(len(vec)):
            if result[i] == 0:
                result[i] = -1
        return result

    def act_func(self, val):
        if val > 0:
            return 1
        elif val < 0:
            return 0
        return val

    def update(self, x, y):
        prev_y = y.copy()
        print("Prev_y = ", self.bnry_to_biplr(prev_y))
        for i in self.updt_ord:
            yin_i = x[i]
            for j in range(self.dimension):
                if i != j:
                    yin_i += y[j] * self.wts[j][i]
            y[i] = self.act_func(yin_i)

        print("New_y = ", self.bnry_to_biplr(y))
        print("\n")
        for i in range(self.dimension):
            if prev_y[i] != y[i]:
                return False
        return True

    def test_input(self, x):
        x = self.biplr_to_bnry(x)
        y = x.copy()
        while True:
            if self.update(x, y):
                break
        return self.bnry_to_biplr(y)


ptrns = [[1, 1, 1, 1]]
ptrns.append([1, 1, -1, -1])
updt_ord = [0, 3, 2, 1]
dim = 4
hopfield_network = Hopfield(ptrns, dim, updt_ord)

print(hopfield_network.wts)

res = hopfield_network.test_input([1, 1, 1, 1])
print("Converged Input (pattern it matched with) ", res)

res = hopfield_network.test_input([1, 1, -1, -1])
print("Converged Input (pattern it matched with) ", res)

res = hopfield_network.test_input([1, 1, 1, 0])
print("Converged Input (pattern it matched with) ", res)
