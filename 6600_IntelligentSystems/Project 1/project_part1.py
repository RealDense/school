# /usr/bin/python

################################################################
# Riley Densley
# A01227345
# Project 1.1
################################################################

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

img = cv2.imread('/home/vladimir/AI/project_01/images/yes_bee.png')
gray_image = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
gray_image.shape

scaled_gray_image = gray_image/255.0
