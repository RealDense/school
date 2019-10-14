import random, math, pygame, sys
from pygame.locals import *

WIDTH = 400
HEIGHT = 400


#             R    G    B
WHITE     = (255, 255, 255)
BLACK     = (  0,   0,   0)
RED       = (255,   0,   0)
GREEN     = (  0, 255,   0)
DARKGREEN = (  0, 155,   0)
DARKGRAY  = ( 40,  40,  40)
BGCOLOR = BLACK



def main():
	global FPSCLOCK, DISPLAYSURF

	pygame.init()
	FPSCLOCK = pygame.time.Clock()
	DISPLAYSURF = pygame.display.set_mode((WIDTH, HEIGHT))

	setup()

	while True:
		runGame()


def setup():
	pass

def terminate():
	pygame.quit()
	sys.exit()

def runGame():

	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			terminate()

	# get all events
	ev = pygame.event.get()

	# proceed events
	for event in ev:

		# handle MOUSEBUTTONUP
		if event.type == pygame.MOUSEBUTTONUP:
			pos = pygame.mouse.get_pos()
	
			# get a list of all sprites that are under the mouse cursor
			clicked_sprites = [s for s in sprites if s.rect.collidepoint(pos)]
			# do something with the clicked sprites...

	DISPLAYSURF.fill(BLACK)

	pygame.display.update()
	

