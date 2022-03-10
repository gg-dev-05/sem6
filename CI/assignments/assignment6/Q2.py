class perceptron:
    def __init__(self,num,value):
        self.weights = [0.0]*num
        self.threshold = value
        self.bias =0
    def get_weights(self):
        return self.weights
    def get_bias(self):
        return self.bias
    def set_weights(self,weights):
        self.weights = weights
    def set_bias(self,bias):
        self.bias = bias
    def activation_func(self,value):
        if value>=self.threshold:
            return 1
        else:
            return 0
    def weights_calculate(self,learn_rate,inputs,prediction):
        for i in range(len(self.weights)):
            self.weights[i] += learn_rate*(inputs[1]-prediction)*inputs[0][i]
    def fit(self,inputs,learn_rate,epochs):
        for _ in range(epochs):
            for i in range(len(inputs)):
                prediction = self.predict(inputs[i])
                self.weights_calculate(learn_rate,inputs[i],prediction)
                self.bias+= learn_rate*(inputs[i][1]-prediction)   
    def predict(self,inputs):
        sum = self.bias
        for i in range(len(inputs[0])):
            sum+=self.weights[i]*inputs[0][i]
        return self.activation_func(sum)
    def predict_multiple(self,inputs):
        output = []
        for i in range(len(inputs)):
            output.append(self.predict(inputs[i]))
        return output
    

def model_accuracy(input,output):
    correct = 0.0
    total = len(input)
    for x in range(len(input)):
        if input[x][1] == output[x]:
            correct+=1
    return correct/total         


# we need 2 neurons as we need two lines to separate them 
neuron_1 = perceptron(2,0)
neuron_2 = perceptron(2,0)
learn_rate = 0.5
epochs = 20
weights_1= [0,0]
weights_2 = [0,0]
bias_1 = 0
bias_2 = 0
input_1 = [[[1,1],0],[[1,2],0],[[2,-1],1],[[2,0],1],[[-1,2],0],[[-2,1],0],[[-1,-1],1],[[-2,-2],1]]
input_2 = [[[1,1],0],[[1,2],0],[[2,-1],0],[[2,0],0],[[-1,2],1],[[-2,1],1],[[-1,-1],1],[[-2,-2],1]]
print("Initial weights:",weights_1)
print("Initial bias:",bias_1)
print("learning rate:",learn_rate)
print("Total epochs:",epochs)
print("epochs","acc1","acc2","weights1","bias1","weights2","bias2")
neuron_1.set_weights(weights_1)
neuron_2.set_weights(weights_2)
neuron_1.set_bias(bias_1)
neuron_2.set_bias(bias_2)
for i in range(1,epochs+1):
    neuron_1.fit(input_1,learn_rate,1)
    neuron_2.fit(input_2,learn_rate,1)
    prediction_1 = neuron_1.predict_multiple(input_1)
    prediction_2 = neuron_2.predict_multiple(input_2)
    accuracy_1 = model_accuracy(input_1,prediction_1)
    accuracy_2 = model_accuracy(input_2,prediction_2)
    weights_1 = neuron_1.get_weights()
    weights_2 = neuron_2.get_weights()
    bias_1 = neuron_1.get_bias()
    bias_2 = neuron_2.get_bias()
    print(i,accuracy_1,accuracy_2,weights_1,weights_2,bias_1,bias_2)


#2 input xor gate
input1 = [[[1,1],0],[[1,0],1],[[0,1],1],[[0,0],0]]
neuron1 = perceptron(2,0.5)
neuron2 = perceptron(2,1.5)
neuron3 = perceptron(2,1)
weights1 = [1,1]
weights2 = [1,1]
weights3 = [1,-1]
neuron1.set_weights(weights1)
neuron2.set_weights(weights2)
neuron3.set_weights(weights3)
output1 = neuron1.predict_multiple(input1)
output2 = neuron2.predict_multiple(input1)
input3 = []
for i in range(len(input1)):
    input3.append([[output1[i],output2[i]],1])
output3 = neuron3.predict_multiple(input3)
print(output1)
print(output2)
print(output3)



#3 input xor gate
# input1 = [[[1,1,1],1],[[1,0,1],0],[[0,1,1],0],[[0,0,1],1],[[1,1,0],0],[[1,0,0],1],[[0,1,0],1],[[0,0,0],0]]
# neuron1 = perceptron(3,0.5)
# neuron2 = perceptron(3,1.5)
# neuron3 = perceptron(3,1)
# neuron4 = perceptron(3,0.5)
# neuron5 = perceptron(3,1)
# weights1 = [1,1,0]
# weights2 = [1,1,0]
# weights3 = [1,-1,0]
# weights4 = [0,0,1]
# weights5 = [1,-1,0]
# neuron1.set_weights(weights1)
# neuron2.set_weights(weights2)
# neuron3.set_weights(weights3)
# neuron4.set_weights(weights4)
# neuron5.set_weights(weights5)
# output1 = neuron1.predict_multiple(input1)
# output2 = neuron2.predict_multiple(input1)
# input3 = []
# for i in range(len(input1)):
#     input3.append([[output1[i],output2[i]],1])
# output3 = neuron3.predict_multiple(input3)
# output4 = neuron4.predict_multiple(input1)
# input5 = []
# for i in range(len(input1)):
#     input5.append([[output3[i],output4[i]],1])
# output5 = neuron5.predict_multiple(input5)
# print(output1)
# print(output2)
# print(output3)
# print(output4)
# print(output5)




# data = [[[1,4],0],[[1,5],0],[[2,4],0],[[2,5],0],[[3,1],1],[[3,2],1],[[4,1],1],[[4,2],1]]
# model = perceptron(2,0)
# weights = [1,-1]
# bias = 0
# learn_rate = 0.5
# epochs = 10
# print("Initial weights:",weights)
# print("Initial bias:",bias)
# print("learning rate:",learn_rate)
# print("Total epochs:",epochs)
# print("epochs","accuracy","weights","bias")
# display_data = []
# model.set_weights(weights)
# model.set_bias(bias)
# for i in range(1,epochs+1):
#     model.fit(data,learn_rate,1)
#     prediction = model.predict_multiple(data)
#     accuracy = model_accuracy(data,prediction)
#     curr_weights = model.get_weights()
#     curr_bias = model.get_bias()
#     print(i,accuracy,curr_weights,curr_bias)