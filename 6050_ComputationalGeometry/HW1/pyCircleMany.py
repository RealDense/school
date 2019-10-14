#!/bin/python

import math
import random

print (math.pi)

x = 0
y = 1
ins = 0
insTotal = 0
count = 0

def cross(j, k):
    #i is always (0,0)
    c = (k[x] * j[y]) - (k[y] * j[x])
    if(c < 0):
        return False
    return True

def randomXY():
    num = random.uniform(0, 2*math.pi)
    return [math.cos(num), math.sin(num)]


for j in range (3,5):
    for i in range(1, 500):
        num = []
        for k in range(j):
            num.append(randomXY())
        #print(num) 
        centered = True
        first = cross(num[0], num[1])
        for a in num:
            for b in num:
                if (a != b):
                    #print(a)
                    #print(b)
                    if(cross(a,b) == first):
                        centered = True
                        #print("True")
                    else:
                        centered = False
                        #print("false")
                        break
            if(centered == False):
                break
        if(centered == True):
            ins +=1
            print("same")
        count += 1 
        if( i%100 == 0):
            print(j, " points of ", i, " iterations")
            print(count)
            print(ins/(i))
