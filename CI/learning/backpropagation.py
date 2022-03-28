__author__ = "stark"

# Back-Propagation Neural Networks
#
import math
import random

random.seed(0)

# calculate a random number where:  a <= rand < b
def rand(a, b):
    return (b - a) * random.random() + a


# Make a matrix (we could use NumPy to speed this up)
def makeMatrix(I, J, fill=0.0):
    m = []
    for i in range(I):
        m.append([fill] * J)
    return m


# our sigmoid function, tanh is a little nicer than the standard 1/(1+e^-x)
def sigmoid(x):
    return math.tanh(x)


# derivative of our sigmoid function, in terms of the output (i.e. y)
def dsigmoid(y):
    return 1.0 - y**2


class NN:
    def __init__(
        self, number_of_inputs, number_of_hidden_layers, number_of_output_nodes
    ):
        # number of input, hidden, and output nodes
        self.number_of_inputs = number_of_inputs + 1  # +1 for bias node
        self.number_of_hidden_layers = number_of_hidden_layers
        self.number_of_output_nodes = number_of_output_nodes

        # activations for nodes
        self.ai = [1.0] * self.number_of_inputs
        self.ah = [1.0] * self.number_of_hidden_layers
        self.ao = [1.0] * self.number_of_output_nodes

        # create weights
        self.wi = makeMatrix(self.number_of_inputs, self.number_of_hidden_layers)
        self.wo = makeMatrix(self.number_of_hidden_layers, self.number_of_output_nodes)
        # set them to random vaules
        for i in range(self.number_of_inputs):
            for j in range(self.number_of_hidden_layers):
                self.wi[i][j] = rand(-0.2, 0.2)
        for j in range(self.number_of_hidden_layers):
            for k in range(self.number_of_output_nodes):
                self.wo[j][k] = rand(-2.0, 2.0)

        # last change in weights for momentum
        self.ci = makeMatrix(self.number_of_inputs, self.number_of_hidden_layers)
        self.co = makeMatrix(self.number_of_hidden_layers, self.number_of_output_nodes)

    def update(self, inputs):
        if len(inputs) != self.number_of_inputs - 1:
            raise ValueError("wrong number of inputs")

        # input activations
        for i in range(self.number_of_inputs - 1):
            # self.ai[i] = sigmoid(inputs[i])
            self.ai[i] = inputs[i]

        # hidden activations
        for j in range(self.number_of_hidden_layers):
            sum = 0.0
            for i in range(self.number_of_inputs):
                sum = sum + self.ai[i] * self.wi[i][j]
            self.ah[j] = sigmoid(sum)

        # output activations
        for k in range(self.number_of_output_nodes):
            sum = 0.0
            for j in range(self.number_of_hidden_layers):
                sum = sum + self.ah[j] * self.wo[j][k]
            self.ao[k] = sigmoid(sum)

        return self.ao[:]

    def backPropagate(self, targets, N, M):
        if len(targets) != self.number_of_output_nodes:
            raise ValueError("wrong number of target values")

        # calculate error terms for output
        output_deltas = [0.0] * self.number_of_output_nodes
        for k in range(self.number_of_output_nodes):
            error = targets[k] - self.ao[k]
            output_deltas[k] = dsigmoid(self.ao[k]) * error

        # calculate error terms for hidden
        hidden_deltas = [0.0] * self.number_of_hidden_layers
        for j in range(self.number_of_hidden_layers):
            error = 0.0
            for k in range(self.number_of_output_nodes):
                error = error + output_deltas[k] * self.wo[j][k]
            hidden_deltas[j] = dsigmoid(self.ah[j]) * error

        # update output weights
        for j in range(self.number_of_hidden_layers):
            for k in range(self.number_of_output_nodes):
                change = output_deltas[k] * self.ah[j]
                self.wo[j][k] = self.wo[j][k] + N * change + M * self.co[j][k]
                self.co[j][k] = change
                # print N*change, M*self.co[j][k]

        # update input weights
        for i in range(self.number_of_inputs):
            for j in range(self.number_of_hidden_layers):
                change = hidden_deltas[j] * self.ai[i]
                self.wi[i][j] = self.wi[i][j] + N * change + M * self.ci[i][j]
                self.ci[i][j] = change

        # calculate error
        error = 0.0
        for k in range(len(targets)):
            error = error + 0.5 * (targets[k] - self.ao[k]) ** 2
        return error

    def test(self, patterns):
        for p in patterns:
            print(p[0], "->", self.update(p[0]))

    def weights(self):
        print("Input weights:")
        for i in range(self.number_of_inputs):
            print(self.wi[i])
        print()
        print("Output weights:")
        for j in range(self.number_of_hidden_layers):
            print(self.wo[j])

    def train(self, patterns, iterations=1000, N=0.5, M=0.1):
        # N: learning rate
        # M: momentum factor
        for i in range(iterations):
            error = 0.0
            for p in patterns:
                inputs = p[0]
                targets = p[1]
                self.update(inputs)
                error = error + self.backPropagate(targets, N, M)
            if i % 100 == 0:
                print("error %-.5f" % error)


def demo():
    # Teach network XOR function
    pat = [[[0, 0], [0]], [[0, 1], [1]], [[1, 0], [1]], [[1, 1], [0]]]

    # create a network with two input, two hidden, and one output nodes
    n = NN(2, 2, 1)
    # train it with some patterns
    n.train(pat)
    # test it
    n.test(pat)


if __name__ == "__main__":
    demo()
