#!/usr/bin/env python
import time
from pygame import mixer
import sys

a = 'n'

if __name__ == "__main__":
	if len(sys.argv)>1:
		a = sys.argv[1]


if a == 's':
	sound = 'AUDIO/1_person_cheering.wav'
elif a == 'g':
	sound = 'AUDIO/SMALL_CROWD_APPLAUSE.wav'
else:
	sound = 'AUDIO/Bicycle_Bell.wav'


mixer.init()
mixer.music.load(sound)
mixer.music.play()
time.sleep(5)
