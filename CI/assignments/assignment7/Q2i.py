import numpy as np
from model import Model

train_inputs = np.array(
    [
        [1, 0, 0, 0, 0, 0, 1],
        [1, 0, 1, 0, 0, 1, 1],
        [1, 1, 1, 1, 0, 0, 0],
        [0, 0, 1, 1, 0, 1, 1],
        [1, 1, 0, 0, 0, 1, 1],
        [0, 0, 1, 1, 1, 0, 0],
    ]
)

labels = np.array([1, 0, 0, 0, 1, 1])
perceptron = Model(7)
perceptron.fit(train_inputs, labels, 50, 0.1)

dataset = [
    [1, 0, 0, 0, 0, 0, 1],
    [0, 0, 1, 1, 0, 1, 1],
    [0, 1, 0, 0, 0, 1, 0],
    [1, 1, 0, 0, 0, 1, 1],
    [1, 0, 1, 1, 1, 0, 1],
    [1, 0, 1, 0, 0, 1, 1],
]

for i in dataset:
    print(i, ": is palindrome => ", perceptron.predict(i))
