from simpleai.search import SearchProblem, hill_climbing_random_restarts
# from simpleai.search.viewers import ConsoleViewer
import random

class KnapsackProblem(SearchProblem):
	def __init__(self, numObjects, maxWeight, weights, values, initial_state=None):
		super(KnapsackProblem, self).__init__(initial_state)
		self.numObjects = numObjects
		self.maxWeight = maxWeight
		self.weights = weights
		self.values = values;

	def generate_random_state(self):
		r = range(self.numObjects)
		choice = [1] * self.numObjects
		while not self._valid(choice):
			k = random.randint(1, self.numObjects)
			x = random.sample(r, k)
			for i in x:
				choice[i] = 0
		return choice

	def crossover():
		pass

	def mutate():
		pass

	def value(self, s):
		v = 0
		for index, item x in enumerate(s):
			if item == 1:
				v += self.values[index]
		return v


	def _weight(self, s):
		weight = 0
		for index, item x in enumerate(s):
			if item == 1:
				weight += self.weights[index]
		return weight

	def _valid(self, s):
		if self._weight(s) > maxWeight:
			return False
		return True