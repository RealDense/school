import cv2

import json
import random
import sys

# Other Imports
# from mnist_loader import load_data_wrapper
import network2
import pickle as cPickle


import tflearn
from tflearn.data_utils import shuffle, to_categorical
from tflearn.layers.core import input_data, dropout, fully_connected
from tflearn.layers.conv import conv_2d, max_pool_2d
from tflearn.layers.estimator import regression
import tflearn.datasets.mnist as mnist
import numpy as np
import pickle
from scipy import stats


# img = cv2.imread('BEE1')/

net_path_1 = 'hw06_my_net_01.tfl'


def load_bee1_ann_1(path):
    input_layer = input_data(shape=[None, 32, 32, 1])
    fc_layer_1 = fully_connected(
        input_layer, 40, activation='relu', name='fc_layer_1')
    fc_layer_2 = fully_connected(
        fc_layer_1, 40, activation='relu', name='fc_layer_2')
    fc_layer_3 = fully_connected(
        fc_layer_2, 2, activation='softmax', name='fc_layer_3')

    model = tflearn.DNN(fc_layer_3)
    model.load(path)
    return model


def load(file_name):
    with open(file_name, 'rb') as fp:
        obj = pickle.load(fp)
    return obj


VALID_X_PATH = '2valid_x.pck'
VALID_Y_PATH = '2valid_y.pck'
validX = load(VALID_X_PATH)
validY = load(VALID_Y_PATH)

model = load_bee1_ann_1(net_path_1)
