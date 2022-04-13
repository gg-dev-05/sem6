import numpy as np
from model1 import Model

train_inputs = []
train_inputs.append(np.array([1, 1]))
train_inputs.append(np.array([1, 2]))
train_inputs.append(np.array([2, -1]))
train_inputs.append(np.array([2, 0]))
train_inputs.append(np.array([-1, 2]))
train_inputs.append(np.array([-2, 1]))
train_inputs.append(np.array([-1, -1]))
train_inputs.append(np.array([-2, -2]))

labels1 = np.array([0, 0, 0, 0, 1, 1, 1, 1])
labels2 = np.array([0, 0, 1, 1, 0, 0, 1, 1])

model1 = Model(2)
model1.fit(train_inputs, labels1)

model2 = Model(2)
model2.fit(train_inputs, labels2)

for inputs in train_inputs:
    print(inputs, end="")
    # print(model1.predict(inputs), model2.predict(inputs))
    model1_prediction = model1.predict(inputs)
    model2_prediction = model2.predict(inputs)
    print(f" {model1_prediction * 2 + model2_prediction}th class")

# model1 used 2 iterations
# model2 used 1 iterations
