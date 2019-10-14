#lslsl

from PIL import Image
import pygame, random, sys
from pygame.locals import *

im = Image.open('data/smile.png')

im = im.convert(mode='L')

im = im.resize((300,300), Image.ANTIALIAS)
width, height = im.size
im.show()

pixels = []

for ( j in range(0,height)):
	pixels.append([])
	for (i in range(0,width)):
		pixels[j].append([
		

CELLSIZE = 3

def main():
	global FPSCLOCK, DISPLAYSURF

	pygame.init()
	FPSCLOCK = pygame.time.Clock()
	DISPLAYSURF = pygame.display.set_mode((width * CELLSIZE, height * CELLSIZE))

	while True:
		runGame()

def terminate():
	pygame.display.quit()
	pygame.quit()
	sys.exit()

def runGame():
	
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			terminate()

	DISPLAYSURF.fill((0,0,0))

	pygame.display.update()

if __name__ == '__main__':
	main()

