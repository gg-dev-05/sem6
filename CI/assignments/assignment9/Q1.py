import numpy as np


def shapeFunction(x):
    return np.array(x).shape


def parameters(input_features, num_of_neurons_in_hidden_layer, output_features):
    W1 = np.random.randn(num_of_neurons_in_hidden_layer, input_features) * 0.01
    W2 = np.random.randn(output_features, num_of_neurons_in_hidden_layer) * 0.01
    b1 = np.zeros((num_of_neurons_in_hidden_layer, 1))
    b2 = np.zeros((output_features, 1))
    parameters = {"W1": W1, "b1": b1, "W2": W2, "b2": b2}
    return parameters


def sigmoid(x):
    return 1 / (1 + np.exp(-x))


def sigmoid_derivative(x):
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


def calculate_accuracy(y_predicted, y_true_value):
    c, n = 0.0, 0.0
    for y, yt in zip(y_predicted, y_true_value):
        if y == yt:
            c += 1
        n += 1
    return c / n


def forward_propagation(X, params):
    W1, W2, b1, b2 = params["W1"], params["W2"], params["b1"], params["b2"]
    Z1 = np.dot(W1, X) + b1
    A1 = sigmoid(Z1)
    Z2 = np.dot(W2, A1) + b2
    A2 = sigmoid(Z2)
    cache = {"Z1": Z1, "A1": A1, "Z2": Z2, "A2": A2}
    return A2, cache


def calculate_cost(A2, Y):
    diff = Y - A2
    diff = diff * diff
    cost_sum = np.sum(diff)
    cost = 1 / 2 * cost_sum
    cost = np.squeeze(cost)
    return cost


def back_propagation_implementation(X, Y, params, cache, learning_rate):
    W1, W2, b1, b2 = params["W1"], params["W2"], params["b1"], params["b2"]
    A1 = cache["A1"]
    A2 = cache["A2"]
    dA2 = A2 - Y
    dZ2 = dA2 * sigmoid_derivative(A2)  # element wise multiplication
    dW2 = np.dot(dZ2, A1.T)
    db2 = np.sum(dZ2, axis=1, keepdims=True)
    dA1 = np.dot(W2.T, dZ2)
    dZ1 = dA1 * sigmoid_derivative(A1)
    dW1 = np.dot(dZ1, np.array(X).T)
    db1 = np.sum(dZ1, axis=1, keepdims=True)
    W1 = W1 - learning_rate * dW1
    b1 = b1 - learning_rate * db1
    W2 = W2 - learning_rate * dW2
    b2 = b2 - learning_rate * db2
    return W1, W2, b1, b2


def dataGeneration(n):
    x = np.random.randint(0, 2, size=(n, 7))
    y = []
    for i in range(len(x)):
        c = 0
        for item in x[i]:
            if item == 1:
                c += 1
        if c >= 4:
            y.append(1)
        else:
            y.append(0)
    y = np.array(y)
    return x, y


X_train = np.zeros((20, 7))
y_train = np.zeros((20, 1))
X_test = np.zeros((10, 7))
y_test = np.zeros((10, 1))

X_train, y_train = dataGeneration(len(X_train))
X_test, y_test = dataGeneration(len(X_test))

input_dims = len(X_train[0])
output_dims = 1
hidden_layer_dims = 15
parameters = parameters(input_dims, hidden_layer_dims, output_dims)

number_of_iterations = 200
learning_rate = 0.01

for i in range(0, number_of_iterations):
    for X, y in zip(X_train, y_train):
        X = X.reshape(-1, 1)
        y = y.reshape(-1, 1)
        A2, cache = forward_propagation(X, parameters)
        cost = calculate_cost(A2, y)
        W1, W2, b1, b2 = back_propagation_implementation(
            X, y, parameters, cache, learning_rate
        )
        parameters["W1"], parameters["W2"], parameters["b1"], parameters["b2"] = (
            W1,
            W2,
            b1,
            b2,
        )
    if i % 25 == 0 or i == 199:
        print("Cost after iteration % i: % f" % (i, cost))

threshold = 0.5
y_pred = predict(X_test, parameters)
for i in range(0, y_pred.shape[0]):
    if y_pred[i] >= threshold:
        y_pred[i] = 1
    else:
        y_pred[i] = 0
acc = calculate_accuracy(y_pred, y_test)
# print(parameters["W1"])
# print(parameters["W2"])
int(f"accuracy is {acc}")
