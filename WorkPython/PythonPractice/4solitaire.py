from __future__ import print_function
import random

GAMESTOPLAY = 100
SUITS = ['s', 'h', 'c', 'd']
VALUES = ['A','2','3','4','5','6','7','8','9','10','J','Q','K']

class Card():
	def __init__(self, s, v):
		self.suit = s
		self.value = v

	def show(self):
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

		print (num, 'of', sue)


def makeDeck():
	d = []
	for s in SUITS:
		for v in VALUES:
			d.append(Card(s,v))

	random.shuffle(d)
	
	return d

def draw(hand, deck):
	hand.append(deck[0])
	del deck[0]
	return hand, deck
	
#print (SUITS)

#c = Card(SUITS[2], VALUES[10])
#c.show()

wins = []
for i in range(54):
	wins.append(0)



for x in range(GAMESTOPLAY):
	if not (x%100000):
		print (x/100000)

	deck = makeDeck()


	hand = []
	oldHand = [1]



	while oldHand != hand:
		oldHand = hand[:]

		if len(hand) < 4:
			if len(deck) == 0:
				continue
			else:
				hand, deck = draw(hand, deck)
				continue
		'''	
		for i in range(10):
		if i < len(hand):
			hand[len(hand)-1-i].show()

		raw_input('')
		'''
		if hand[-1].value == hand[-4].value:
			
			del hand [-1]
			del hand [-1]
			del hand [-1]
			del hand [-1]
			'''
			del hand [-2]
			del hand [-2]
			'''
			continue

		elif hand[-1].suit == hand[-4].suit:
			
			del hand[-2]
			del hand[-2]
			'''
			del hand[-1]
			del hand[-1]
			del hand[-1]
			del hand[-1]
			'''
			continue	

		if len(deck) == 0:
			pass
		else:
			hand, deck = draw(hand, deck)

	wins[53] += 1
	wins[len(hand)] += 1



for i in range(len(wins)):
	if not i%2:
#		print(i, '   ', wins[i], 'games one   ', wins[i]/float(GAMESTOPLAY)*100, '%')
		print('{0:2d} {1:8d} games one    {2:.4f}%'.format(i, wins[i], wins[i]/float(GAMESTOPLAY)*100))
