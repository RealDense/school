#!/usr/bin/python

####################################################
# CS 5600/6600/7890: Assignment 1: Problems 1 & 2
# Riley Densley
# A01227345
#####################################################

import numpy as np
import math

class and_perceptron:

    def __init__(self):
        # your code here
        self.w = [.5,.5]
        self.b = -.5
        pass

    def output(self, x):
        # your code here
        y = 0
        for i in range(len(x)):
            y += (x[i]*self.w[i])  
        y += self.b 
        if(y > 0):
            return 1
        else:
            return 0
        pass

class or_perceptron:
    def __init__(self):
        # your code
        self.w = [.5,.5]
        self.b = 0
        pass

    def output(self, x):
        # your code
        y = 0
        for i in range(len(x)):
            y += (x[i]*self.w[i])  
        y += self.b 
        #print(y)
        if(y > 0):
            return 1
        else:
            return 0
        pass

class not_perceptron:
    def __init__(self):
        # your code
        self.w = [-1]
        self.b = 1
        pass

    def output(self, x):
        # your code
        y = 0
        for i in range(len(x)):
            y += (x[i]*self.w[i])  
        y += self.b 
        if(y > 0):
            return 1
        else:
            return 0
        pass

class xor_perceptron:
    def __init__(self):
        # your code
        self.w = [1,1]
        self.b = 1
        self.andp = and_perceptron()
        self.orp = or_perceptron()
        self.notp = not_perceptron()
        pass

    def output(self, x):
        # your code
        andResult = self.andp.output(x)
        orResult = self.orp.output(x)
        notResult = self.notp.output([andResult])
        and2Result = self.andp.output([orResult,notResult])
        return and2Result
        #return self.andp.output([self.orp.output(x), self.notp.output([self.andp.output(x)])])

class xor_perceptron2:
    def __init__(self):
        # your code
        self.w1 = [[-.5,-.5],[.5,.5]]
        self.b1 = [1,0]
        self.w2 = [.5,.5]
        self.b2 = -.5
        pass

    def output(self, x):
        # your code
        step1 = [0,0]
        y = 0
        for j in range(len(step1)):
            for i in range(len(x)):
                step1[j] += (x[i]*self.w1[j][i])  
            step1[j] += self.b1[j] 
            step1[j] = math.ceil(step1[j])

        for i in range(len(step1)):
            y += (step1[i]*self.w2[i])  
        y += self.b2 

        #print(x, step1, y)
        if(y > 0):
            return [1]
        else:
            return [0]
        pass

### ================ Unit Tests ====================

# let's define a few binary input arrays.    
x00 = np.array([0, 0])
x01 = np.array([0, 1])
x10 = np.array([1, 0])
x11 = np.array([1, 1])

# let's test the and perceptron.
def unit_test_01():
    andp = and_perceptron()
    assert andp.output(x00) == 0
    assert andp.output(x01) == 0
    assert andp.output(x10) == 0
    assert andp.output(x11) == 1
    print ('all andp assertions passed...')

# let's test the or perceptron.
def unit_test_02():
    orp = or_perceptron()
    assert orp.output(x00) == 0
    assert orp.output(x01) == 1
    assert orp.output(x10) == 1
    assert orp.output(x11) == 1
    print ('all orp assertions passed...')

# let's test the not perceptron.
def unit_test_03():
    notp = not_perceptron()
    assert notp.output(np.array([0])) == 1
    assert notp.output(np.array([1])) == 0
    print ('all notp assertions passed...')

# let's test the 1st xor perceptron.
def unit_test_04():
    xorp = xor_perceptron()
    assert xorp.output(x00) == 0
    assert xorp.output(x01) == 1
    assert xorp.output(x10) == 1
    assert xorp.output(x11) == 0
    print ('all xorp assertions passed...')

# let's test the 2nd xor perceptron.
def unit_test_05():
    xorp2 = xor_perceptron2()
    # xorp2.output(x00)
    # xorp2.output(x01)
    # xorp2.output(x10)
    # xorp2.output(x11)

    assert xorp2.output(x00)[0] == 0
    assert xorp2.output(x01)[0] == 1
    assert xorp2.output(x10)[0] == 1
    assert xorp2.output(x11)[0] == 0
    print ('all xorp2 assertions passed...')

unit_test_01()
unit_test_02()
unit_test_03()
unit_test_04()
unit_test_05()

        
        

    
        





