import random
import csv
import math


def read_file(filename):
    file = open(filename)
    csvreader = csv.reader(file)
    rows = []
    for row in csvreader:
        rows.append(row)
    file.close()
    print(f"{filename} successfully read\n")
    return rows


def sigmoid_activation_func(x):
    if x <= -100:
        return 0
    if x >= 100:
        return 1
    return 1 / (1 + math.exp(-x))


def derivative_sigmoid_activation_function(x):
    return sigmoid_activation_func(x) * (1 - sigmoid_activation_func(x))


# Single Hidden Layer Neural Network
class SHLNN:
    # N : Size of Input Vector
    # M : Number of neurons in hidden layer
    def __init__(self, N, M):
        print(
            f"Initialize NN with {N} as size of input vector and {M} as number of neurons"
        )
        self.N = N
        self.M = M
        self.hidden_layer_weights = []
        self.hidden_layer_bias = []

        # initializing random weights
        for _ in range(M):
            self.hidden_layer_bias.append(random.uniform(-0.1, 0.1))
            w_temp = []
            for i in range(N):
                w_temp.append(random.uniform(-0.1, 0.1))
            self.hidden_layer_weights.append(w_temp)

        self.output_bias = random.uniform(-0.1, 0.1)
        w_temp = []
        for i in range(M):
            w_temp.append(random.uniform(-0.1, 0.1))
        self.output_weights = w_temp

    def train(self, train_data, train_labels, learning_rate, number_of_epochs):
        print(f"Training Model")
        for _ in range(number_of_epochs):
            print(f"Running epoch Number: {_}")
            for iterator in range(len(train_data)):
                data = train_data[iterator]
                label = train_labels[iterator]

                activated_sum_hidden_layer = []
                for i in range(self.M):
                    val = self.hidden_layer_bias[i]
                    for j in range(self.N):
                        val += self.hidden_layer_weights[i][j] * data[j]
                    activated_sum_hidden_layer.append(sigmoid_activation_func(val))

                sum_output_layer = self.output_bias
                activated_sum_output_layer = 0
                for i in range(self.M):
                    sum_output_layer += (
                        activated_sum_hidden_layer[i] * self.output_weights[i]
                    )
                activated_sum_output_layer = sigmoid_activation_func(sum_output_layer)

                if activated_sum_output_layer > 0.5:
                    activated_sum_output_layer = 1
                else:
                    activated_sum_output_layer = 0

                for i in range(self.M):
                    self.output_weights[i] += (
                        -1
                        * learning_rate
                        * (activated_sum_output_layer - label)
                        * derivative_sigmoid_activation_function(sum_output_layer)
                        * activated_sum_hidden_layer[i]
                    )

                # update output layer baises
                self.output_bias += (
                    -1
                    * learning_rate
                    * (activated_sum_output_layer - label)
                    * derivative_sigmoid_activation_function(sum_output_layer)
                )

                # update hidden layer weights
                for i in range(self.M):
                    for j in range(self.N):
                        self.hidden_layer_weights[i][j] += (
                            -1
                            * learning_rate
                            * (activated_sum_output_layer - label)
                            * derivative_sigmoid_activation_function(sum_output_layer)
                            * self.output_weights[i]
                            * derivative_sigmoid_activation_function(
                                activated_sum_hidden_layer[i]
                            )
                            * data[j]
                        )

                # update hidden layer baises
                for i in range(self.M):
                    self.hidden_layer_bias[i] += (
                        -1
                        * learning_rate
                        * (activated_sum_output_layer - label)
                        * derivative_sigmoid_activation_function(sum_output_layer)
                        * self.output_weights[i]
                        * derivative_sigmoid_activation_function(
                            activated_sum_hidden_layer[i]
                        )
                    )

    def test(self, test_data, test_labels):
        total_correct_results = 0
        total_incorrect_results = 0
        for iterator in range(len(test_data)):
            Data = test_data[iterator]
            Label = test_labels[iterator]

            sum_hidden_layer = []
            activated_sum_hidden_layer = []
            for i in range(self.M):
                val = self.hidden_layer_bias[i]
                for j in range(self.N):
                    val += self.hidden_layer_weights[i][j] * Data[j]
                sum_hidden_layer.append(val)
                activated_sum_hidden_layer.append(sigmoid_activation_func(val))

            sum_output_layer = self.output_bias
            activated_sum_output_layer = 0
            for i in range(self.M):
                sum_output_layer += (
                    activated_sum_hidden_layer[i] * self.output_weights[i]
                )
            activated_sum_output_layer = sigmoid_activation_func(sum_output_layer)

            if activated_sum_output_layer > 0.5:
                if Label == 1:
                    total_correct_results += 1
                else:
                    total_incorrect_results += 1
            else:
                if Label == 0:
                    total_correct_results += 1
                else:
                    total_incorrect_results += 1
        print(
            f"final accuracy of model = {float(total_correct_results)/float(total_correct_results+total_incorrect_results)}"
        )


if __name__ == "__main__":
    testDataRaw = read_file("testData.csv")
    testLabelsRaw = read_file("testLabels.csv")
    trainDataRaw = read_file("trainData.csv")
    trainLabelsRaw = read_file("trainLabels.csv")

    testData = []
    for row in testDataRaw:
        a = []
        for x in row:
            a.append(float(x))
        testData.append(a)

    trainData = []
    for row in trainDataRaw:
        a = []
        for x in row:
            a.append(float(x))
        trainData.append(a)

    testLabels = []
    for row in testLabelsRaw:
        testLabels.append(int(row[0]) - int(5))

    trainLabels = []
    for row in trainLabelsRaw:
        trainLabels.append(float(row[0]) - 5.0)

    NeuralNetwork = SHLNN(len(testData[0]), 10)

    NeuralNetwork.train(trainData, trainLabels, 0.001, 1000)

    NeuralNetwork.test(testData, testLabels)
