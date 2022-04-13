# 190001016
# Garvit Galgat

import numpy as np


def shape(x):
    return np.array(x).shape


def collectData(f):
    rs = []
    for line in f:
        x = line.split(",")
        y = []
        for item in x:
            y.append(float(item.strip()))
        rs.append(y)
    return np.array(rs)


def initializeParameters(inputFeatures, neuronsInHiddenLayers, outputFeatures):
    w1 = np.random.randn(neuronsInHiddenLayers, inputFeatures) * 0.01
    w2 = np.random.randn(outputFeatures, neuronsInHiddenLayers) * 0.01
    b1 = np.zeros((neuronsInHiddenLayers, 1))
    b2 = np.zeros((outputFeatures, 1))

    parameters = {"w1": w1, "b1": b1, "w2": w2, "b2": b2}
    return parameters


def sigmoid(x):
    return 1 / (1 + np.exp(-x))


def sigmoid_deriv(x):
    # compute the derivative of the sigmoid function assuming
    # that x has already been passed thru the sigmoid function
    return x * (1 - x)


def predict(X_test, params):
    w1, w2, b1, b2 = params["w1"], params["w2"], params["b1"], params["b2"]
    a2 = []
    for X in X_test:
        X = X.reshape(-1, 1)
        Z1 = np.dot(w1, X) + b1
        a1 = sigmoid(Z1)
        Z2 = np.dot(w2, a1) + b2
        a2.append(sigmoid(Z2))

    return np.array(a2).reshape(-1, 1)


def accuracy(predictions, targets):
    return 0.5 * np.sum((predictions - targets) ** 2)


def forward_prop(X, params):
    w1, w2, b1, b2 = params["w1"], params["w2"], params["b1"], params["b2"]
    Z1 = np.dot(w1, X) + b1
    a1 = sigmoid(Z1)
    Z2 = np.dot(w2, a1) + b2
    a2 = sigmoid(Z2)
    # here the cache is the data of previous itr
    # This will be used for backpropagation
    cache = {"Z1": Z1, "a1": a1, "Z2": Z2, "a2": a2}
    return a2, cache


def back_propagate(X, Y, params, cache, learning_rate):
    w1, w2, b1, b2 = params["w1"], params["w2"], params["b1"], params["b2"]
    # Retrieving also a1 and a2 from dictionary "cache"
    a1 = cache["a1"]
    a2 = cache["a2"]

    # Backward propagation: calculate dw1, db1, dw2, db2.
    # layer 1 from out

    da2 = a2 - Y
    dZ2 = da2 * sigmoid_deriv(a2)  # element wise multiplication
    dw2 = np.dot(dZ2, a1.T)
    db2 = np.sum(dZ2, axis=1, keepdims=True)
    # layer 2

    da1 = np.dot(w2.T, dZ2)
    dZ1 = da1 * sigmoid_deriv(a1)
    dw1 = np.dot(dZ1, np.array(X).T)
    db1 = np.sum(dZ1, axis=1, keepdims=True)

    # Updating the parameters
    w1 = w1 - learning_rate * dw1
    b1 = b1 - learning_rate * db1
    w2 = w2 - learning_rate * dw2
    b2 = b2 - learning_rate * db2

    return w1, w2, b1, b2


def unison_shuffled_copies(a, b):
    assert len(a) == len(b)
    p = np.random.permutation(len(a))
    return a[p], b[p]


# Generate 7 input majority
def input_1(n=100):
    Train = np.zeros(n)
    Label = np.zeros(n)
    for i in range(n):
        Train[i] = i + 1
        Label[i] = 1 / Train[i]
    X, y = unison_shuffled_copies(Train, Label)
    len_train = int(0.7 * n)
    # len_test = int(0.3*n)
    return X[0:len_train], y[0:len_train], X[len_train:], y[len_train:]


if __name__ == "__main__":

    # encode labels
    X_train, y_train, X_test, y_test = input_1()
    X_train = np.array(X_train)
    X_test = np.array(X_test)
    y_train = np.array(y_train)
    y_test = np.array(y_test)
    X_train = X_train.reshape(-1, 1)
    X_test = X_test.reshape(-1, 1)
    y_train = y_train.reshape(-1, 1)
    y_test = y_test.reshape(-1, 1)

    input_dims = len(X_train[0])
    output_dims = 1
    print("enter number of neurons in hidden layer: ")
    hidden_layer_dims = int(input())
    params = initializeParameters(input_dims, hidden_layer_dims, output_dims)

    num_iterations = 1000
    learning_rate = 0.01

    for i in range(0, num_iterations):
        for X, y in zip(X_train, y_train):
            X = X.reshape(-1, 1)
            y = y.reshape(-1, 1)
            a2, cache = forward_prop(X, params)
            w1, w2, b1, b2 = back_propagate(X, y, params, cache, learning_rate)
            params["w1"], params["w2"], params["b1"], params["b2"] = w1, w2, b1, b2

    # testing
    y_pred = predict(X_test, params)
    acc = accuracy(y_pred, y_test)

    print(f"Acc is {acc}")
