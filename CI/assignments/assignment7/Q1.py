import numpy as np
from model import Model

train_inputs = np.array(
    [
        [1, 1, 1, 1, 1, 1, 0],
        [0, 1, 1, 0, 0, 0, 0],
        [1, 1, 0, 1, 1, 0, 1],
        [1, 1, 1, 1, 0, 0, 1],
        [0, 1, 1, 0, 0, 1, 1],
        [1, 0, 1, 1, 0, 1, 1],
        [1, 0, 1, 1, 1, 1, 1],
        [1, 1, 1, 0, 0, 0, 0],
        [1, 1, 1, 1, 1, 1, 1],
        [1, 1, 1, 1, 0, 1, 1],
    ]
)

labels = np.array(
    [
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 1],  # 0
        [0, 0, 0, 0, 0, 0, 0, 0, 1, 0],  # 1
        [0, 0, 0, 0, 0, 0, 0, 1, 0, 0],  # 2
        [0, 0, 0, 0, 0, 0, 1, 0, 0, 0],  # 3
        [0, 0, 0, 0, 0, 1, 0, 0, 0, 0],  # 4
        [0, 0, 0, 0, 1, 0, 0, 0, 0, 0],  # 5
        [0, 0, 0, 1, 0, 0, 0, 0, 0, 0],  # 6
        [0, 0, 1, 0, 0, 0, 0, 0, 0, 0],  # 7
        [0, 1, 0, 0, 0, 0, 0, 0, 0, 0],  # 8
        [1, 0, 0, 0, 0, 0, 0, 0, 0, 0],  # 9
    ]
)

# Array of perceptrons
perceptrons = []
for i in range(10):
    perceptron = Model(7)
    perceptron.fit(train_inputs, labels[i], 50, 0.1)
    perceptrons.append(perceptron)

# use the trained perceptrons to predict the result
for j in range(10):
    inp = train_inputs[j]
    print(inp)
    for i in perceptrons:
        print(i.predict(inp), end=" ")
    print("\n")
