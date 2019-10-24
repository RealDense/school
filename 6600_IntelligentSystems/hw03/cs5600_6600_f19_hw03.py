#/usr/bin/python

############################
# Module: cs5600_6600_f19_hw03.py
# Your name
# Your A#
############################

from network import Network
from mnist_loader import load_data_wrapper
from mnist_loader import vectorized_result
import random
import pickle as cPickle
import numpy as np
import os

# load training, validation, and testing MNIST data
train_d, valid_d, test_d = load_data_wrapper()

# define your networks
net1 = [784, 30, 30, 30, 30, 10]
net2 = [784, 30, 30, 30, 10]
net3 = [784, 60, 60, 10]
net4 = [784, 20, 10]
net5 = [784, 120, 10]
# net5 = [784, 20, 20, 10]

# define an ensemble of 5 nets
networks = (net1, net2, net3, net4, net5)
eta_vals = (0.1, 0.25, 0.3, 0.4, 0.5)
mini_batch_sizes = (5, 10, 15, 20)

# train networks
def train_nets(networks, eta_vals, mini_batch_sizes, num_epochs, path):
    # your code here
    for net in networks:
      if(net == None):
        continue
      n = Network(net)
      print(net)
      eta = random.choice(eta_vals)
      print(eta)
      mini = random.choice(mini_batch_sizes)
      print(mini)
      n.SGD(train_d, num_epochs, mini, eta, test_data=test_d)
      fileName = 'net'
      for part in net:
        fileName = fileName +'_'+ str(part)
      
      fileName = fileName + '_' + str(eta*100) + '_' + str(mini) + '.pck'
      print(fileName)
      cPickle.dump(n, open(path + fileName, "wb"))


def load_nets(path):
    # your code here
    net = []
    for fileName in os.listdir(path):
      net.append([str(fileName), cPickle.load(open(os.path.join(path,fileName), "rb"))])
    return net
    # pass

# evaluate net ensemble.
def evaluate_net_ensemble(net_ensemble, test_data):
  # your code here
  right = 0
  results = np.zeros(10)
  for test in test_data:
    results = np.zeros(10)

    for net in net_ensemble:
      result = net[1].feedforward(test[0])
      results[np.where(result == np.amax(result))[0][0]] += 1
    thisMax = np.where(results == np.amax(results))
    # print(test[1])
    # print(thisMax)
    if(thisMax[0][0] == test[1]):
      right +=1
  return (right, len(test_data))
    

# net = Network([784, 30, 10])
# train_d, valid_d, test_d = load_data_wrapper()
# net.SGD(train_d, 20, 10, 3.0, test_data=test_d)

num_epochs = 30
# 5 - 8985
# 15 - 9383
# 30 - 9519
# 60 - 9618
path = '/mnt/c/Users/rtden/Documents/UBU/6600_IntelligentSystems/hw03/output/'
#path = './output'

train_nets(networks, eta_vals, mini_batch_sizes, num_epochs, path)
trained_nets = load_nets(path)

# print(trained_nets[0][1].sizes)
# print(trained_nets[0][1].biases)
# print(trained_nets[0][1].weights)

# print(valid_d)

validation = evaluate_net_ensemble(trained_nets, valid_d)

print(validation)

# print("here")
# print(Network(net1))
# print(trained_nets)
