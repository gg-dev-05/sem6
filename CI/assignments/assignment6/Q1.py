import numpy as np
from model1 import Model

# Q1

train_inputs = np.array(
    [[1, 1], [1, 2], [2, -1], [2, 0], [-1, 2], [-2, 1], [-1, -1], [-2, -2]]
)
# 00 means C1 01 means C2 10 means C3 11 means C4
labels1 = np.array([0, 0, 0, 0, 1, 1, 1, 1])
labels2 = np.array([0, 0, 1, 1, 0, 0, 1, 1])
# 2 input features for 1st neuron total epochs :- 1
mcp1 = Model(2)
mcp1.fit(train_inputs, labels1)
# 2 input features for 1st neuron total epochs :- 2
mcp2 = Model(2)
mcp2.fit(train_inputs, labels2)
# predicted class with the help of 2 neuron
for inputs in train_inputs:
    print(inputs, end="")
print(mcp1.predict(inputs), mcp2.predict(inputs))
