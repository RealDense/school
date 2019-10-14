#!/bin/python

import math
import random

print (math.pi)

x = 0
y = 1
ins = 0


def cross(j, k):
    #i is always (0,0)
    c = (k[x] * j[y]) - (k[y] * j[x])
    if(c < 0):
        return False
    return True

def randomXY():
    #Pick a random number between 0 and 2 pi
    #Return a X and Y based on the radian value
    num = random.uniform(0, 2*math.pi)
    return [math.cos(num), math.sin(num)]

#iterate 500 times
for i in range(1, 501):
    num1 = randomXY()
    num2 = randomXY()
    num3 = randomXY()

    if(cross(num1, num2) == cross(num2, num3) == cross(num3, num1)):
        ins+=1
    else:
        pass

    #print every 10 results to see if value is converging
    if( i%10 == 0):
        print(ins/(i))
