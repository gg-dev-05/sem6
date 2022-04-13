import numpy as np


class Model:
    def __init__(self, num_inputs):
        self.weights = np.zeros(num_inputs)
        self.bias = 0

    def set_weight(self, num_inputs):
        for i in range(len(num_inputs)):
            self.weights[i] = num_inputs[i]

    def predict(self, inputs):
        sum = np.dot(inputs, self.weights[:]) + self.bias
        if sum >= 0:
            prediction = 1
        else:
            prediction = 0
        return prediction

    def fit(self, inputs, label, epochs=3, learning_rate=0.5):
        for _ in range(epochs):
            for val, res in zip(inputs, label):
                prediction = self.predict(val)
                self.weights[:] += learning_rate * (res - prediction) * val
                self.bias += learning_rate * (res - prediction)
