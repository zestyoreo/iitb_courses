'''
  Backpropagation in a Shallow Neural Net
  Machine learning for Remote Sensing 2 - GNR638
  Author: P Balasubramanian
  Rollno: 200050103

  A shallow neural net with 
      -> 1 input layer with 2 nodes &
      -> 1 hidden layer with 3 nodes & 
      -> 1 output layer with 1 node.
'''
import numpy as np

def initialization():
    #input initialization
    no_nodes = 3                #number of nodes in hidden layer
    x = np.random.randn(2,1)*0.1
    y = 0                       #ground truth

    n_x = x.shape[0]            #number of nodes in input layer
    n_h = 3                     #number of nodes in hidden layer
    n_y = 1                     #number of nodes in output layer

    #weights and biases initialization
    W1 = np.random.randn(n_h,n_x)*0.1
    b1 = np.zeros((n_h,1))
    W2 = np.random.randn(n_y,n_h)*0.1
    b2 = np.zeros((n_y,1))

    return x,y,W1,b1,W2,b2

def print_parameters(W1,b1,W2,b2):
    print("W1:",W1,"    b1:",b1)
    print("W2:",W2,"    b2:",b2)

def sigmoid(logit):
    return ( 1/(1+np.exp(-1*logit)))

def forward_prop(x,W,b,activation):
    logit = W.dot(x)+b

    if activation=='tanh':
        a = np.tanh(logit)
    elif activation== 'sigmoid':
        a = sigmoid(logit)
    
    return logit,a

def compute_cost(a,y):
    return float(np.squeeze((-1)*(y*np.log(a)+(1-y)*np.log(1-a))))

def backprop(W1,b1,W2,b2,z1,a1,z2,a2,j,alpha):
    z1_dash = 1 - np.square(a1)
    dz2 = a2 - y
    dW2 = dz2.dot(a1.T)
    db2 = np.sum(dz2, axis=1, keepdims=True)
    dz1 = (W2.T).dot(dz2)*(z1_dash)
    dW1 = dz1.dot(x.T)
    db1 = np.sum(dz1, axis=1, keepdims=True)

    W1 = W1 - alpha*dW1
    b1 = b1 - alpha*db1
    W2 = W2 - alpha*dW2
    b2 = b2 - alpha*db2
    return W1,b1,W2,b2

x,y,W1,b1,W2,b2 = initialization()
print("Inputs: ",x," ",y)
print("Initial Weights and Biases")
print_parameters(W1,b1,W2,b2)
alpha = 0.2                                     #learning rate

no_epochs = int(input("Enter number of epochs: "))

for i in range(1,no_epochs+1):
    z1,a1 = forward_prop(x,W1,b1,'tanh')        # logit & activation from hidden layer
    z2,a2 = forward_prop(a1,W2,b2,'sigmoid')    # logit & activation from output layer (the prediction)
    j = compute_cost(a2,y)                      # cost calculation

    if i%100 ==0:
        print("After ",i," epochs:\tprediction :",float(np.squeeze(a2)),"\tground truth: ",y,"\tcost: ",j)
    
    W1,b1,W2,b2 = backprop(W1,b1,W2,b2,z1,a1,z2,a2,j,alpha) #backpropagation step

    if i%1000 ==0:
        print("Weights and Biases after ",i," epochs")
        print_parameters(W1,b1,W2,b2)

