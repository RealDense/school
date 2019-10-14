#!/usr/bin/env python

import random, math, pygame
from pygame.locals import *
import planet.py


#constants
WINSIZE = [200, 200]
#WINCENTER = [WINSIZE[0]/2, WINSIZE[1]/2]
screen = pygame.display.set_mode(WINSIZE)







def main():

	global FPSCLOCK, DISPLAYSURF

	pygame.init()
	FPSCLOCK = pygame.time.Clock()
	DISPLAYSURF = pygame.display.set_mode((WINSIZE[0], WINSIZE[1]))
	
	while True:
		runGame()



