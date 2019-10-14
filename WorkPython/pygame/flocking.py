#!/usr/bin/env python

import random, math, pygame, sys
from pygame.locals import *

WIDTH = 700
HEIGHT = 500


def main():

	global FPSCLOCK, DISPLAYSURF

	pygame.init()
	FPSCLOCK = pygame.time.Clock()
	DISPLAYSURF = pygame.display.set_mode((HEIGHT,WIDTH))


	#setup()

	while True:
		runGame()

def terminate():
	pygame.display.quit()
	pygame.quit()
	sys.exit()

class boid(): 
	position = (random.randint(0, WIDTH), random.randint(0, HEIGHT))
	
	def show(self):
		pygame.draw.rect(DISPLAYSURF, (255,255,255),( self.position[0], self.position[1], 3, 3))


def runGame():

	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			terminate()

	b = boid()
	print(b.position, b.position[0]+1)

	DISPLAYSURF.fill((0, 0, 0))
	b.show()
	
	pygame.display.update()

if __name__ == '__main__':
	main()
