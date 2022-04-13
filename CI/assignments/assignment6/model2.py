class perceptron:
    def __init__(self, num, value):
        self.weights = [0.0] * num
        self.threshold = value
        self.bias = 0

    def get_weights(self):
        return self.weights

    def get_bias(self):
        return self.bias

    def set_weights(self, weights):
        self.weights = weights

    def set_bias(self, bias):
        self.bias = bias

    def activation_func(self, value):
        if value >= self.threshold:
            return 1
        else:
            return 0

    def weights_calculate(self, learn_rate, inputs, prediction):
        for i in range(len(self.weights)):
            self.weights[i] += learn_rate * (inputs[1] - prediction) * inputs[0][i]

    def fit(self, inputs, learn_rate, epochs):
        for _ in range(epochs):
            for i in range(len(inputs)):
                prediction = self.predict(inputs[i])
                self.weights_calculate(learn_rate, inputs[i], prediction)
                self.bias += learn_rate * (inputs[i][1] - prediction)

    def predict(self, inputs):
        sum = self.bias
        for i in range(len(inputs[0])):
            sum += self.weights[i] * inputs[0][i]
        return self.activation_func(sum)

    def predict_multiple(self, inputs):
        output = []
        for i in range(len(inputs)):
            output.append(self.predict(inputs[i]))
        return output


def model_accuracy(input, output):
    correct = 0.0
    total = len(input)
    for x in range(len(input)):
        if input[x][1] == output[x]:
            correct += 1
    return correct / total
