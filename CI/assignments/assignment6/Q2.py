from model1 import Model
import numpy as np


# 2 input Xor
train_inputs = np.array([[0, 0], [0, 1], [1, 0], [1, 1]])
labels1 = np.array([0, 0, 0, 0])
labels2 = np.array([0, 1, 1, 0])
# for 2 input xor and 3 input xor It cannot be done as it is linearly inseparable
# so we can do but we have to take that many lines i.e we have to make each input as a different class
# so then only we can do and after that also we have to combine few classes so perceptron layered network will be required
# also we can see by running this cell it will run an infinite loop
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
