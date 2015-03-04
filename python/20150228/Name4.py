from simpleai.search import SearchProblem, hill_climbing_random_restarts
from simpleai.search.viewers import ConsoleViewer
import random


class TspProblem(SearchProblem):
	def __init__(self, numCities, distances, initial_state=None):
		super(TspProblem, self).__init__(initial_state)
		self.numCities = numCities
		self.distances = distances
		self.baseState = range(1, numCities)

	def actions(self, state):
		state_tmp = state[1]
		#if len(state) == 2:
		#	state_tmp = state[1]
		nodes = [0,0]
		while True:
			nodes[0] = random.randint(1, self.numCities-1)
			nodes[1] = random.randint(1, self.numCities-1)
			if nodes[0] != nodes[1]:
				break
		node_max = max(nodes)
		node_min = min(nodes)
		sub_list = state_tmp[node_min+1 : node_max]
		new_state = state_tmp[:node_min+1] + list(reversed(sub_list)) + state_tmp[node_max:]
		return [('2-change at ' + str(node_min) + ' and ' + str(node_max), new_state)]

	def result(self, state, action):
		return action

	def value(self, state):
		state_tmp = state[1]
		#if len(state) == 2:
		#	state_tmp = state[1]
		ret = self._tour_length(state_tmp)
		return -ret

	def generate_random_state(self):
		state = [0] + random.sample(self.baseState, len(self.baseState)) + [0]
		return (None, state)

	def _tour_length(self, s):
		length = 0
		for i in xrange(len(s)-1):
			length += self.distances[s[i]][s[i+1]]
		return length


if __name__ == "__main__":
	distances = [ \
	[0, 6, 5, 7, 8, 2, 2, 6, 6, 5, 7, 5], \
	[6, 0, 3, 5, 2, 4, 4, 5, 2, 2, 1, 5], \
	[5, 3, 0, 6, 1, 1, 8, 7, 7, 6, 4, 3], \
	[7, 5, 6, 0, 3, 5, 1, 1, 7, 3, 8, 4], \
	[8, 2, 1, 3, 0, 7, 7, 8, 7, 3, 2, 5], \
	[2, 4, 1, 5, 7, 0, 8, 2, 5, 5, 2, 6], \
	[2, 4, 8, 1, 7, 8, 0, 1, 7, 8, 1, 8], \
	[6, 5, 7, 1, 8, 2, 1, 0, 1, 5, 1, 4], \
	[6, 2, 7, 7, 7, 5, 7, 1, 0, 7, 5, 4], \
	[5, 2, 6, 3, 3, 5, 8, 5, 7, 0, 4, 2], \
	[7, 1, 4, 8, 2, 2, 1, 1, 5, 4, 0, 2], \
	[5, 5, 3, 4, 5, 6, 8, 4, 4, 2, 2, 0]]
	problem = TspProblem(len(distances),distances);
	#result = hill_climbing_random_restarts(problem, restarts_limit=200, viewer=ConsoleViewer())
	result = hill_climbing_random_restarts(problem, restarts_limit=200)
	print result.state
	#print result.path()




