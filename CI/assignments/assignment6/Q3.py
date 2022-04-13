from model1 import Model
import numpy as np

# Q3

train_input = np.array([[1, 4], [1, 5], [2, 4], [2, 5], [3, 1], [3, 2], [4, 1], [4, 2]])
labels = np.array([0, 0, 0, 0, 1, 1, 1, 1])
mcp = Model(2)
mcp.fit(train_input, labels)
for inputs in train_input:
    print(inputs, mcp.predict(inputs))
