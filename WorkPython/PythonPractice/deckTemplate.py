from __future__ import print_function
import random

SUITS = ['s', 'h', 'c', 'd']
VALUES = ['A','2','3','4','5','6','7','8','9','10','J','Q','K']

class Card():
	def __init__(self, s, v):
		self.suit = s
		self.value = v

	def __str__(self):
		'''
		print (self.suit, self.value, sep='')

		'''
		
		num = self.value
		sue = self.suit
		if num == 'A':
			num = 'Ace'
		elif num == 'J':
			num = 'Jack'
		elif num == 'Q':
			num = 'Queen'
		elif num == 'K':
			num = 'King'

		if sue == 's':
			sue = 'Spades'
		elif sue == 'h':
			sue = 'Hearts'
		elif sue == 'c':
			sue = 'Clubs'
		else:
			sue = 'Diamonds'

		face = num + ' of ' + sue
		
		return face


def makeDeck():
	d = []
	for s in SUITS:
		for v in VALUES:
			d.append(Card(s,v))

	random.shuffle(d)
	
	return d

'''	
print (SUITS)

c = Card(SUITS[2], VALUES[10])
print(c)

deck = makeDeck()

for i in range(10):
	print(deck[i], ' '*(18-len(str(deck[i]))), end='')
'''

