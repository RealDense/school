from __future__ import print_function
import random

wins = 0
trys = 10000
for i in range(trys):

    doors = {0:False, 1:False, 2:False}

    doors[random.randint(0,2)] = True

    #print(doors)
    #del doors[1]
    #print(doors)

    player = random.randint(0,2)

    shown = False

    while(not shown):
        host = random.randint(0,2)
        if(host != player and not doors[host]):
            shown = True

    #print(doors)
    del doors[host]
    del doors[player]
    for value in doors.itervalues():
        result = value

    #print(host, player, result)
    if(value):
        wins += 1

print(wins)
print("If you change you win", (float(wins)/trys)*100, "% of the time")



    