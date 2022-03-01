import numpy as np

class Pits:
  def __init__(self, total_inputs):
    self.threshold_value = 0
    self.n = total_inputs
    self.epochs=0
    self.weights = np.zeros(total_inputs)

  def predict(self, inputs):
    sum = np.dot(inputs, self.weights[:])
    if sum >= self.threshold_value:
      return 1
    return 0
    
  def fit(self, inputs, label):
    self.epochs=0
    all_weights=[]
    for i in range(0,2**self.n):
      temp=[]
      for j in range(0,self.n):
        if (1<<j)&(i):
          temp.append(1)
        else:
          temp.append(-1)
      all_weights.append(temp)
    for weight in all_weights:
      self.weights= np.array(weight)
      self.epochs=self.epochs+1
      for threshold_value in range(-self.n,self.n+1):
        self.threshold_value= threshold_value
        i=0
        for input in inputs:
          prediction = self.predict(input)
          if prediction != label[i]:
              break
          i= i + 1
        if i==len(inputs):
          return
