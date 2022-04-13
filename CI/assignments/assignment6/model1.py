import numpy as np


class Model:
    def __init__(self, num_inputs):
        self.weights = np.zeros(num_inputs)
        self.bias = 0

    def predict(self, inputs):
        sum = np.dot(inputs, self.weights[:]) + self.bias
        if sum >= 0:
            prediction = 1
        else:
            prediction = 0
        return prediction

    def fit(self, inputs, label, learning_rate=0.5):
        epochNo = 0
        while True:
            flag = True
            for val, res in zip(inputs, label):
                predictedOutput = self.predict(val)
                if predictedOutput != res:
                    flag = False
                    break
            if flag == True:
                break
            epochNo = epochNo + 1
            for val, res in zip(inputs, label):
                prediction = self.predict(val)
                self.weights[:] += learning_rate * (res - prediction) * val
                self.bias += learning_rate * (res - prediction)
            print("Updated Weights: ")
            for i in self.weights:
                print(i, end=" ")
                print("")
                print(f"Updated Bias: {self.bias}")
                print("")
                print(str(epochNo) + " number of epochs took place")
