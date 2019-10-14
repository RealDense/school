#!/usr/bin/env python

import random, math, pygame, sys
from pygame.locals import *

#constants
#FPS = 500
WIDTH = 800
HEIGHT = 800
CELLWIDTH = 4
CELLHEIGHT = 4
#WINCENTER = [WINSIZE[0]/2, WINSIZE[1]/2]
#screen = pygame.display.set_mode((WIDTH, HEIGHT))

sandpiles = []

#             R    G    B
WHITE     = (255, 255, 255)
BLACK     = (  0,   0,   0)
RED       = (255,   0,   0)
GREEN     = (  0, 255,   0)
DARKGREEN = (  0, 155,   0)
DARKGRAY  = ( 40,  40,  40)
BGCOLOR = BLACK


COLOR0    = (225, 225,   0)
COLOR1    = (  0, 185,  63)
COLOR2    = (  0, 104, 225)
COLOR3    = (122,   0, 229)




def main():

	global FPSCLOCK, DISPLAYSURF

	pygame.init()
	FPSCLOCK = pygame.time.Clock()
	DISPLAYSURF = pygame.display.set_mode((WIDTH, HEIGHT))

	setup()
	
	while True:
		runGame()


def setup():
	for i in range(HEIGHT/CELLHEIGHT):
		sandpiles.append([])
		for j in range(WIDTH/CELLWIDTH):
			sandpiles[i].append(0)
	#print (sandpiles)
	sandpiles[(HEIGHT/CELLHEIGHT)/2][(WIDTH/CELLWIDTH)/2]=100000
	

def terminate():
	pygame.quit()
	sys.exit()

def runGame():

	
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			terminate()



	
	DISPLAYSURF.fill(BLACK)
	drawpiles()
	pygame.display.update()
#	FPSCLOCK.tick(FPS)

	tumble()

def tumble():
	nextpiles = []
	for i in range(HEIGHT/CELLHEIGHT):
		nextpiles.append([])
		for j in range(WIDTH/CELLWIDTH):
			nextpiles[i].append(0)

	for i in range(HEIGHT/CELLHEIGHT):
		for j in range(WIDTH/CELLWIDTH):
			num = sandpiles[i][j]
			if num >= 4:
				nextpiles[i][j] += num - 4
				if i+1 < len(nextpiles):
					nextpiles[i+1][j] += 1
				if i-1 >= 0:				
					nextpiles[i-1][j] += 1
				if j+1 < len(nextpiles[i]):
					nextpiles[i][j+1] += 1
				if i-1 >= 0:
					nextpiles[i][j-1] += 1
			else:
				nextpiles[i][j] += num

	for i in range(HEIGHT/CELLHEIGHT):
		for j in range(WIDTH/CELLWIDTH):
			sandpiles[i][j] = nextpiles[i][j]

def drawpiles():
	for i in range(HEIGHT/CELLHEIGHT):
		for j in range(WIDTH/CELLWIDTH):
			if sandpiles[i][j] == 0:
				color = COLOR0	
			elif sandpiles[i][j] == 1:
				color = COLOR1	
			elif sandpiles[i][j] == 2:
				color = COLOR2	
			else:
				color = COLOR3	

			pygame.draw.rect(DISPLAYSURF, color, (j*CELLWIDTH, i*CELLHEIGHT, CELLWIDTH, CELLHEIGHT))


if __name__ =='__main__':
	main()

