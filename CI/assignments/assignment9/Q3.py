import numpy as np


def shape(x):
    return np.array(x).shape


def collect_Data(f):
    res = []
    for line in f:
        x = line.split(",")
        y = []
        for item in x:
            y.append(float(item.strip()))
        res.append(y)
    return np.array(res)


def parameters(inputFeatures, neuronsIn_Hidden_Layers, output_Features):
    W1 = np.random.randn(neuronsIn_Hidden_Layers, inputFeatures) * 0.01
    W2 = np.random.randn(output_Features, neuronsIn_Hidden_Layers) * 0.01
    b1 = np.zeros((neuronsIn_Hidden_Layers, 1))
    b2 = np.zeros((output_Features, 1))

    parameters = {"W1": W1, "b1": b1, "W2": W2, "b2": b2}
    return parameters


def sigmoid(x):
    return 1 / (1 + np.exp(-x))


def sigmoid_deriv(x):
    # compute the derivative of the sigmoid function ASSUMING
    # that x has already been passed through the 'sigmoid'
    # function
    return x * (1 - x)


def predict(X_test, params):
    W1, W2, b1, b2 = params["W1"], params["W2"], params["b1"], params["b2"]
    A2 = []
    for X in X_test:
        X = X.reshape(-1, 1)
        Z1 = np.dot(W1, X) + b1
        A1 = sigmoid(Z1)
        Z2 = np.dot(W2, A1) + b2
        A2.append(sigmoid(Z2))

    return np.array(A2).reshape(-1, 1)


def accuracy(predictions, targets):
    return 0.5 * np.sum((predictions - targets) ** 2)


def forward_propagation(X, params):
    W1, W2, b1, b2 = params["W1"], params["W2"], params["b1"], params["b2"]
    Z1 = np.dot(W1, X) + b1
    A1 = sigmoid(Z1)
    Z2 = np.dot(W2, A1) + b2
    A2 = sigmoid(Z2)
    # here the cache is the data of previous iteration
    # This will be used for backpropagation
    cache = {"Z1": Z1, "A1": A1, "Z2": Z2, "A2": A2}
    return A2, cache


def back_propagate(X, Y, params, cache, learning_rate):
    W1, W2, b1, b2 = params["W1"], params["W2"], params["b1"], params["b2"]
    # Retrieve also A1 and A2 from dictionary "cache"
    A1 = cache["A1"]
    A2 = cache["A2"]

    # Backward propagation: calculate dW1, db1, dW2, db2.
    # layer 1 from out

    dA2 = A2 - Y
    dZ2 = dA2 * sigmoid_deriv(A2)  # element wise multiplication
    dW2 = np.dot(dZ2, A1.T)
    db2 = np.sum(dZ2, axis=1, keepdims=True)
    # layer 2

    dA1 = np.dot(W2.T, dZ2)
    dZ1 = dA1 * sigmoid_deriv(A1)
    dW1 = np.dot(dZ1, np.array(X).T)
    db1 = np.sum(dZ1, axis=1, keepdims=True)

    # Updating the parameters according to algorithm
    W1 = W1 - learning_rate * dW1
    b1 = b1 - learning_rate * db1
    W2 = W2 - learning_rate * dW2
    b2 = b2 - learning_rate * db2

    return W1, W2, b1, b2


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
    params = parameters(input_dims, hidden_layer_dims, output_dims)

    num_iterations = 1000
    learning_rate = 0.01

    for i in range(0, num_iterations):
        for X, y in zip(X_train, y_train):
            X = X.reshape(-1, 1)
            y = y.reshape(-1, 1)
            A2, cache = forward_propagation(X, params)
            W1, W2, b1, b2 = back_propagate(X, y, params, cache, learning_rate)
            params["W1"], params["W2"], params["b1"], params["b2"] = W1, W2, b1, b2

    # testing
    y_pred = predict(X_test, params)
    loss = accuracy(y_pred, y_test)

    print(f"Loss is {loss}")
