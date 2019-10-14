import random

def addition(score):
	usr = 1
	print('\n\nCan you add?')
	while usr != 0:
		fir = random.randint(1,101)
		sec = random.randint(1,101)
		summ = fir + sec
	
		print '\n  ', fir, '\n','+ ', sec, '\n','------'
		usr = input('>  ')
	
		if(usr == 0):
			continue
		elif(usr == summ):
			print('\nWell done comrade!!')
			score[1] += 1
		else:
			print('\nCome on. Its simple addition.')
		score[0] += 1
	return score

def subtraction(score):
	usr = 1
	print('\n\nCan you subtraction?')
	while usr != 0:
		fir = random.randint(1,101)
		sec = random.randint(1,101)
		summ = fir + sec
	
		print '\n  ', summ, '\n','- ', sec, '\n','------'
		usr = input('>  ')
	
		if(usr == 0):
			continue
		elif(usr == fir):
			print('\nWell done comrade!!')
			score[1] += 1
		else:
			print('\nCome on. Its simple subtraction.')
		score[0] += 1
	return score

def mult(score):
	usr = 1
	nums = [1,2,3,4,5,6,7,8,9,10,11,12]
	print('\n\nCan you multiply?')
	while usr != 0:
		fir = random.choice(nums)
		sec = random.choice(nums)
		prod = fir * sec
	
		print '\n  ', fir, '\n','x ', sec, '\n','------'
		usr = input('>  ')
	
		if(usr == 0):
			continue
		elif(usr == prod):
			print('\nWell done comrade!!')
			score[1] += 1
		else:
			print('\nCome on. Its simple multiplication.')
		score[0] += 1
	return score

def divide(score):
	usr = 1
	nums = [1,2,3,4,5,6,7,8,9,10,11,12]
	print('\n\nCan you divide?')
	while usr != 0:
		fir = random.choice(nums)
		sec = random.choice(nums)
		prod = fir * sec
	
		print '\n  ', prod, '\n','/ ', sec, '\n','------'
		usr = input('>  ')
	
		if(usr == 0):
			continue
		elif(usr == fir):
			print('\nWell done comrade!!')
			score[1] += 1
		else:
			print('\nCome on. Its simple division.')
		score[0] += 1
	return score

score = [0,0]
while True:
	print '\n    Please choose something to practice:'
	print '    1:  Addition'
	print '    2:  Subtraction'
	print '    3:  Multiply'
	print '    4:  Division\n'
	choice = input('    > ')
	if (choice == 1):
		score = addition(score)
	elif (choice == 2):
		score = subtraction(score)
	elif (choice == 3):
		score = mult(score)
	elif (choice == 4):
		score = divide(score)
	else:
		break
	      

print '\n\nYou got ', score[0], ' right out of ', score[1]
print('Thanks for playing!!\n---------------------\n\n')








