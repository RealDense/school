from __future__ import print_function
import random

GAMESTOPLAY = 100000
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
		#return(num, 'of', sue)


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

def valueCalc(c):
	if c.value == 'A':
		return 0
	elif c.value == 'J':
		return 10
	elif c.value == 'Q':
		return 11
	elif c.value == 'K':
		return 12
	else:
		return int(c.value) - 1

def printDeck(a, b):
	for i in a:
		for j in i[b]:
			print(j, ' '*(20-len(str(j))), end='')
		print()
	print()
	
#print (SUITS)

#c = Card(SUITS[2], VALUES[10])
#c.show()

wins = 0

for x in range(GAMESTOPLAY):
#	if not (x%100000):
#		print (x/100000)

	deck = makeDeck()


	board = []

	for i in range(13):
		board.append([[],[]])
		for j in range(4):
			board[i][0].append(deck[0])
			del deck[0]

#	for i in range(13):
#		for j in board[i][0]:
#			print(j, ' '*(20-len(str(j))), end='')
#		
#		print ()

	gameOver = False

	newHand = board[12][0][0]
	del board[12][0][0]	

	while not gameOver:
		hand = newHand		

		board[valueCalc(hand)][1].append(hand)
		if len(board[valueCalc(hand)][0]) != 0:
			newHand = board[valueCalc(hand)][0][0]
			del board[valueCalc(hand)][0][0]
		else:
			gameOver = True

	count = 0	
	
	for i in board:
		count += len(i[0])
#		for j in i[1]:
#			print(j, ' '*(20-len(str(j))), end='')
#		print()

	if count == 0:
		wins += 1
		
		
#print(valueCalc(board[0][0][0]))


print('Regular Play   ', wins / float(GAMESTOPLAY)*100, '%', sep='')


#Play with a reverve
'''
wins = 0

for x in range(GAMESTOPLAY):
#	if not (x%100000):
#		print (x/100000)

	deck = makeDeck()


	board = []

	for i in range(13):
		board.append([[],[]])
		for j in range(3):
			board[i][0].append(deck[0])
			del deck[0]

	for i in range(13):
		for j in board[i][0]:
			print(j, ' '*(20-len(str(j))), end='')
		
		print ()
	print()
	gameOver = False

	newHand = deck[0]
	del deck[0]	

	while not gameOver:
		hand = newHand		

		print(hand, '\n')
		board[valueCalc(hand)][1].append(hand)
		if len(board[valueCalc(hand)][0]) != 0:
			newHand = board[valueCalc(hand)][0][0]
			del board[valueCalc(hand)][0][0]
		elif len(deck) != 0:
			newHand = deck[0]
			del deck[0]
		elif len(board[12][0]) == 0:
			print('here')
			gameOver = True
		else:
			gameOver = True
		
		printDeck(board,1)
		
		for i in board[12][0]:
			print(i, ' '*(18-len(str(i))), end='')
		print()		
		
		for i in deck:
			print(i, ' '*(18-len(str(i))), end='')
		print()
		raw_input()
	count = 0	
	
	for i in board:
		count += len(i[0])
		count += len(deck)
		for j in i[1]:
			print(j, ' '*(20-len(str(j))), end='')
		print()

	if count == 0:
		wins += 1
		
		
#print(valueCalc(board[0][0][0]))
print (len(board[12][0]))
print(wins)
print('Reserve Play   ', wins / float(GAMESTOPLAY)*100, '%', sep='')
'''
