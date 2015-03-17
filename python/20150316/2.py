


numRedToken = 10
numBlueToken = 10
numSlot = 50
redToken = 1
blueToken = 2
state = [0] * numSlot
state[0] = redToken
state[-1] = blueToken

print state

state[3] = state[5] = state[7] = blueToken
print state

import random

while True:
	s = random.randint(1, numSlot-1)
	if state[s] == blueToken:
		state[s] = redToken
		break
print state


class Game():
	def __init__(self, numRedToken, numBlueToken, numSlot, redToken, blueToken, initial_state=None):
		self.numRedToken = numRedToken
		self.numBlueToken = numBlueToken
		self.numSlot = numSlot
		self.redToken = redToken
		self.blueToken = blueToken
		self.initial_state = initial_state

	def countReds(self, s):
		cnt = 0
		for item in s:
			if item == self.redToken:
				cnt += 1
		return cnt

	def reverse(self, s):
		return [s[0]] + s[1:-1][::-1] + [s[-1]]

game = Game(10, 10, 50, 1, 2, initial_state=state)
print game.reverse(state)