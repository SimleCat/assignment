from simpleai.search import SearchProblem, genetic
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

	def crossover(self, s, t):
		cnt = 1
		k = random.randint(1, numObjects-1)
		y = s[:k] + t[k:]
		while not self._valid(y):
			if cnt > numObjects:
				return s
			cnt += 1
			k = random.randint(1, numObjects-1)
			y = s[:k] + t[k:]
		return y	

	def mutate(self, s):
		valid = False
		n = -1
		cnt = 0
		s_pre = s
		while not valid:
			s = s_pre
			if cnt > numObjects:
				break
			n = random.randint(0, numObjects-1)
			m = random.randint(0, numObjects-1)
			if s[n]+s[m] == 1:
				if not s[n]:
					s[n] = 1
					s[m] = 0
				else:
					s[n] = 0
					s[m] = 1
				valid = self._valid(s)
				cnt += 1
		return s

	def value(self, s):
		v = 0
		for index, item in enumerate(s):
			if item == 1:
				v += self.values[index]
		return v


	def _weight(self, s):
		weight = 0
		for index, item in enumerate(s):
			if item == 1:
				weight += self.weights[index]
		return weight

	def _valid(self, s):
		if self._weight(s) > maxWeight:
			return False
		return True

if __name__ == "__main__":
	numObjects = 20
	weights = [4, 6, 5, 5, 3, 2, 4, 8, 1, 5, 3, 7, 2, 5, 6, 3, 8, 4, 7, 2]
	values = [5, 6, 2, 8, 6, 5, 8, 2, 7, 6, 1, 3, 4, 4, 1, 5, 6, 2, 5, 3]
	maxWeight = 35
	problem = KnapsackProblem(numObjects, maxWeight, weights, values)
	result = genetic(problem, iterations_limit=100, population_size=16, mutation_chance=0.10)
	print result.path()
	print 'Weight = ' + str(problem._weight(result.path()[0][1]))
	print 'Value = ' + str(problem.value(result.path()[0][1]))