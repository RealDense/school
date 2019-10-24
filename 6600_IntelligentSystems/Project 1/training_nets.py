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

def build_bee1_ann_1():
    input_layer = input_data(shape=[None, 32, 32, 1])
    fc_layer_1 = fully_connected(
        input_layer, 40, activation='relu', name='fc_layer_1')
    fc_layer_2 = fully_connected(
        fc_layer_1, 40, activation='relu', name='fc_layer_2')
    fc_layer_3 = fully_connected(
        fc_layer_2, 2, activation='softmax', name='fc_layer_3')
    network = regression(fc_layer_3, optimizer='sgd',
                         loss='categorical_crossentropy', learning_rate=0.01)

    model = tflearn.DNN(network)
    return model


NUM_EPOCHS = 30
BATCH_SIZE = 10
MODEL = build_bee1_ann_1()
MODEL.fit(trainX, trainY, n_epoch=NUM_EPOCHS,
          shuffle=True,
          validation_set=(testX, testY),
          show_metric=True,
          batch_size=10,
          run_id='BEE1_ann_1')

SAVE_CONVNET_PATH = 'bee1_ann_1.tfl'
MODEL.save(SAVE_CONVNET_PATH)
