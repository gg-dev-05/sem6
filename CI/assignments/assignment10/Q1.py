import numpy as np

target_array = np.array([[1, 1, 1, 1], [1, 1, -1, -1]])


class Hopfield_Neural_Network:
    def __init__(self):
        self.weights = np.dot(target_array.T, target_array)
        for i in range(len(self.weights)):
            self.weights[i][i] = 0
        self.threshold_value = 0
        print(self.weights)

    def check_threshold(self, y_in, y):
        output = y
        if y_in > self.threshold_value:
            output = 1
        elif y_in < self.threshold_value:
            output = 0
        return output

    def parse(self, input_matrix):
        for x in input_matrix:
            y = x
            y_in = y
            order = [1, 4, 3, 2]
            iter = 1
            while True:
                temp = list(y)
                for i in order:
                    sum = 0
                    c = 0
                    for row in self.weights:
                        sum += y[c] * row[i - 1]
                        c = c + 1
                    y_in[i - 1] = x[i - 1] + sum
                    y[i - 1] = self.check_threshold(y_in[i - 1], y[i - 1])
                    print(y)
                if np.array_equal(y, temp):
                    break
                iter += 1
            print(iter)


print("------------------------------")
input_matrix = np.array([[1, 1, 1, 1], [1, 1, -1, -1], [1, 1, 1, 0]])
model = Hopfield_Neural_Network()
model.parse(input_matrix)
