from model import Pits
import numpy as np

# AND Gate
train_inputs= np.array([[1,1,1],[1,1,0],[1,0,1],[1,0,0],[0,1,1],[0,1,0],[0,0,1],[0,0,0]])
labels= np.array([1,0,0,0,0,0,0,0])
pit = Pits(3)
pit.fit(train_inputs,labels)
for inputs in train_inputs:
  print(inputs, pit.predict(inputs))
print("Weights of the input quantitites",pit.weights)
print("No, of Epochs required",pit.epochs)
print("Threshold value which fits our",pit.threshold_value)

# OR Gate
labels= np.array([1,1,1,1,1,1,1,0])
pit = Pits(3)
pit.fit(train_inputs,labels)
for inputs in train_inputs:
  print(inputs, pit.predict(inputs))
print("Weights of the input quantitites",pit.weights)
print("No, of Epochs required",pit.epochs)
print("Threshold value which fits our",pit.threshold_value)

# NAND Gate
labels= np.array([0,1,1,1,1,1,1,1])
pit = Pits(3)
pit.fit(train_inputs,labels)
for inputs in train_inputs:
  print(inputs, pit.predict(inputs))
print("Weights of the input quantitites",pit.weights)
print("No, of Epochs required",pit.epochs)
print("Threshold value which fits our",pit.threshold_value)

# NOR Gate
labels= np.array([0,0,0,0,0,0,0,1])
pit = Pits(3)
pit.fit(train_inputs,labels)
for inputs in train_inputs:
  print(inputs, pit.predict(inputs))
print("Weights of the input quantitites",pit.weights)
print("No, of Epochs required",pit.epochs)
print("Threshold value which fits our",pit.threshold_value)