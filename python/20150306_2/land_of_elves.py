import random

INTRO = \
'''
********************************************************
You are in a land of elves. In front of you, you see two
tree houses. In one, the elf is friendly and will share
his treasure with you. The other elf is mean and nasty, 
and will cast a spell on you.
********************************************************
'''
MSG_REWARD = [\
'''
***********************************************************
* Dear prince charming, you will meet your princess!      *
***********************************************************
''',
'''
***********************************************************
* Dear duke, you go out to see %s bags of gold coins!      *
***********************************************************
''']

MSG_SPELL = [\
'''
***********************************************************
* An elf jumps out in front of you. He waves his wand and *
* turns you into a giant toad!                            *
***********************************************************
''',
'''
***********************************************************
* An elf jumps out in front of you. He waves his wand and *
* turns you into a balck crow whith %d feathers !          *
***********************************************************
''']

def displayIntro():
	print (INTRO)

def chooseTree():
	tree = None
	while True:
		tree = input("Which tree house will you go into? (1 or 2)\n")
		if tree.isdigit():
			tree = int(tree)
			if tree >= 1 and tree <= 2:
				break
	return tree

def checkTree(tree):
	if tree == random.randint(1, 2):
		return True
	else:
		return False

def rewards():
	num  = random.randint(0, 1)
	if num == 0:
		return MSG_REWARD[0]
	else:
		return MSG_REWARD[1] % random.randint(1, 9)

def spells():
	num = random.randint(0, 1)
	if num == 0:
		return MSG_SPELL[0]
	else:
		return MSG_SPELL[1] % random.randint(1, 9)

def again():
	ret = None
	while True:
		ret = input("Do you want to play again? (y or n)\n")
		if ret == "y" or ret == "Y":
			ret = True
			break
		elif ret == 'n' or ret == "N":
			ret  = False
			break
		else:
			continue
	return ret

def main():
	displayIntro()
	while True:
		tree = chooseTree()
		if checkTree(tree):
			print (rewards())
		else:
			print (spells())
		if not again():
			break

if __name__ == "__main__":
	main()
