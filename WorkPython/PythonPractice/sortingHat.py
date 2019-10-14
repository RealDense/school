from __future__ import print_function
import random
import time

houses = ['Gryffindor', 'Hufflepuff', 'Ravenclaw', 'Slytherin']
scripts = ['Hmmmmm..........', 'I know where to put you', ' ']

cont = True

def sorting():
	print(random.choice(scripts), '\n')
	time.sleep( .5)

	print(random.choice(houses))

while(cont):
	user = raw_input('Would you like to be sorted? y/n ')
	if (user == 'n'):
		cont = False
		break
	else:
		sorting()
