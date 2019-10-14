
#########################################
# module: hw02_f19.py
# author: Riley Densley A01227345
#########################################

import numpy as np
import pickle
import random
from hw02_f19_data import *

# save() function to save the trained network to a file
def save(ann, file_name):
    with open(file_name, 'wb') as fp:
        pickle.dump(ann, fp)

# restore() function to restore the file
def load(file_name):
    with open(file_name, 'rb') as fp:
        nn = pickle.load(fp)
    return nn

def build_nn_wmats(mat_dims):
    # your code here
    random.seed(1)
    wmats = []
    #wmats = np.random.randn(mat_dims[:])
    for i in range(len(mat_dims)-1):
        wmats.append(np.empty((mat_dims[i], mat_dims[i+1])))
        for j in range(mat_dims[i]):
            for k in range(mat_dims[i+1]):
                wmats[i][j][k] = random.uniform(-1,1)

    return wmats

def sigmoid(x, deriv=False):
        if(deriv == True):
            return x * (1-x)
            #return np.exp(-x)/((1+ np.exp(-x))**2)
        return 1 / (1 + np.exp(-x))

## Training 3-layer neural net.
## X is the matrix of inputs
## y is the matrix of ground truths.
## build is a nn builder function.
def train_3_layer_nn(numIters, X, y, build):
    W1, W2 = build()
    ## your code here
    for i in range (numIters):
        #Feed Forward
        Z2 = np.dot(X, W1)
        a2 = sigmoid(Z2)
        Z3 = np.dot(a2, W2)
        yHat = sigmoid(Z3)

        #Back Propagation
        yHat_error = y - yHat
        yHat_delta = yHat_error * sigmoid(yHat, deriv=True)

        a2_error = yHat_delta.dot(W2.T)
        a2_delta = a2_error * sigmoid(a2, deriv=True)

        W2 += a2.T.dot(yHat_delta)
        W1 += X.T.dot(a2_delta)
            
    return W1, W2

def train_4_layer_nn(numIters, X, y, build):
    W1, W2, W3 = build()
    ## your code here.
    for i in range (numIters):
        #Feed Forward
        Z2 = np.dot(X, W1)
        a2 = sigmoid(Z2)
        Z3 = np.dot(a2, W2)
        a3 = sigmoid(Z3)
        Z4 = np.dot(a3, W3)
        yHat = sigmoid(Z4)

        #Back Propagation
        yHat_error = y - yHat
        yHat_delta = yHat_error * sigmoid(yHat, deriv=True)

        a3_error = yHat_delta.dot(W3.T)
        a3_delta = a3_error * sigmoid(a3, deriv=True)

        a2_error = a3_delta.dot(W2.T)
        a2_delta = a2_error * sigmoid(a2, deriv=True)

        W3 += a3.T.dot(yHat_delta)
        W2 += a2.T.dot(a3_delta)
        W1 += X.T.dot(a2_delta)
                
    return W1, W2, W3

def fit_3_layer_nn(x, wmats, thresh=0.4, thresh_flag=False):
    # your code here
    Z2 = np.dot(x, wmats[0])
    a2 = sigmoid(Z2)
    Z3 = np.dot(a2, wmats[1])
    yHat = sigmoid(Z3)

    if(thresh_flag):
        if yHat >= thresh:
            return 1
        else:
            return 0
    return yHat
    
def fit_4_layer_nn(x, wmats, thresh=0.4, thresh_flag=False):
    # your code here
    Z2 = np.dot(x, wmats[0])
    a2 = sigmoid(Z2)
    Z3 = np.dot(a2, wmats[1])
    a3 = sigmoid(Z3)
    Z4 = np.dot(a3, wmats[2])
    yHat = sigmoid(Z4)

    if(thresh_flag):
        if yHat >= thresh:
            return 1
        else:
            return 0
    return yHat

## Remember to state in your comments the structure of each of your
## ANNs (e.g., 2 x 3 x 1 or 2 x 4 x 4 x 1) and how many iterations
## it took you to train it.


def build_4222_nn():
    return build_nn_wmats((4, 2, 2, 2))

def build_231_nn():
    return build_nn_wmats((2, 3, 1))

def build_221_nn():
    return build_nn_wmats((2, 2, 1))

def build_2331_nn():
    return build_nn_wmats((2, 3, 3, 1))

def build_131_nn():
    return build_nn_wmats((1, 3, 1))

def build_1331_nn():
    return build_nn_wmats((1, 3, 3, 1))

def build_461_nn():
    return build_nn_wmats((4, 6, 1))

def build_4661_nn():
    return build_nn_wmats((4, 6, 6, 1))

#xor_wmats_231 = train_3_layer_nn(100, X1, y_xor, build_231_nn)
#xor_wmats_221 = train_3_layer_nn(100, X1, y_xor, build_221_nn)

print("and 3 layer")
and_wmats_231 = train_3_layer_nn(900, X1, y_and, build_231_nn)
print(fit_3_layer_nn(X1[0], and_wmats_231, .3, True))
print(fit_3_layer_nn(X1[1], and_wmats_231, .3, True))
print(fit_3_layer_nn(X1[2], and_wmats_231, .3, True))
print(fit_3_layer_nn(X1[3], and_wmats_231, .3, True))

print("and 4 layer")
and_wmats_2331 = train_4_layer_nn(900, X1, y_and, build_2331_nn)
print(fit_4_layer_nn(X1[0], and_wmats_2331, .3, True))
print(fit_4_layer_nn(X1[1], and_wmats_2331, .3, True))
print(fit_4_layer_nn(X1[2], and_wmats_2331, .3, True))
print(fit_4_layer_nn(X1[3], and_wmats_2331, .3, True))

print("or 3 layer")
or_wmats_231 = train_3_layer_nn(900, X1, y_or, build_231_nn)
print(fit_3_layer_nn(X1[0], or_wmats_231, .3, True))
print(fit_3_layer_nn(X1[1], or_wmats_231, .3, True))
print(fit_3_layer_nn(X1[2], or_wmats_231, .3, True))
print(fit_3_layer_nn(X1[3], or_wmats_231, .3, True))

print("or 4 layer")
or_wmats_2331 = train_4_layer_nn(900, X1, y_or, build_2331_nn)
print(fit_4_layer_nn(X1[0], or_wmats_2331, .3, True))
print(fit_4_layer_nn(X1[1], or_wmats_2331, .3, True))
print(fit_4_layer_nn(X1[2], or_wmats_2331, .3, True))
print(fit_4_layer_nn(X1[3], or_wmats_2331, .3, True))

print("not 3 layer")
not_wmats_131 = train_3_layer_nn(900, X2, y_not, build_131_nn)
print(fit_3_layer_nn(X2[0], not_wmats_131, .3, True))
print(fit_3_layer_nn(X2[1], not_wmats_131, .3, True))

print("not 4 layer")
not_wmats_1331 = train_4_layer_nn(900, X2, y_not, build_1331_nn)
print(fit_4_layer_nn(X2[0], not_wmats_1331, .3, True))
print(fit_4_layer_nn(X2[1], not_wmats_1331, .3, True))

print("xor 3 layer")
xor_wmats_231 = train_3_layer_nn(900, X1, y_xor, build_231_nn)
print(fit_3_layer_nn(X1[0], xor_wmats_231, .3, True))
print(fit_3_layer_nn(X1[1], xor_wmats_231, .3, True))
print(fit_3_layer_nn(X1[2], xor_wmats_231, .3, True))
print(fit_3_layer_nn(X1[3], xor_wmats_231, .3, True))

print("xor 4 layer")
xor_wmats_2331 = train_4_layer_nn(900, X1, y_xor, build_2331_nn)
print(fit_4_layer_nn(X1[0], xor_wmats_2331, .3, True))
print(fit_4_layer_nn(X1[1], xor_wmats_2331, .3, True))
print(fit_4_layer_nn(X1[2], xor_wmats_2331, .3, True))
print(fit_4_layer_nn(X1[3], xor_wmats_2331, .3, True))

# print(X4.shape)
# print(bool_exp.shape)

print("bool 3 layer")
bool_wmats_461 = train_3_layer_nn(900, X4, bool_exp, build_461_nn)
for x in X4:
    print(fit_3_layer_nn(x, bool_wmats_461, .3, True))

print("bool 4 layer")
bool_wmats_4661 = train_4_layer_nn(900, X4, bool_exp, build_4661_nn)
for x in X4:
    print(fit_4_layer_nn(x, bool_wmats_4661, .3, True))

save(and_wmats_231, 'and_3_layer_ann.pck')
save(and_wmats_2331, 'and_4_layer_ann.pck')
save(or_wmats_231, 'or_3_layer_ann.pck')
save(or_wmats_2331, 'or_4_layer_ann.pck')
save(not_wmats_131, 'not_3_layer_ann.pck')
save(not_wmats_1331, 'not_4_layer_ann.pck')
save(xor_wmats_231, 'xor_3_layer_ann.pck')
save(xor_wmats_2331, 'xor_4_layer_ann.pck')
save(bool_wmats_461, 'bool_3_layer_ann.pck')
save(bool_wmats_4661, 'bool_4_layer_ann.pck')


print("Did not crash")




    

    
