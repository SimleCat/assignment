import sys
import random

help_str = \
'''
Please like:
python generate_matrix.py arg1 arg2 arg3
	arg1: Number of cities
	arg2: The minimum distance between the two cities
	arg3: The largest distance between the two cities
'''

def check_argv(argv):

	flag = False
	if len(argv) != 4:
		print "Less parameters!"
		print help_str
		exit(0)

	_argv = []
	try:
		_argv.append(int(argv[1]))
		_argv.append(int(argv[2]))
		_argv.append(int(argv[3]))
	except ValueError:
		print "All the parameters must be a number!"
		print help_str
		exit(0)

	if _argv[0] < 2:
		flag = False
		print "Number of cities must >= 2!"
	elif _argv[1] < 1:
		print "The distance between the cities must >= 1!"
	elif _argv[2] <= _argv[1]:
		print "The largest distance must be greater than the minimum distance!"
	else:
		flag = True

	if not flag:
		print help_str
		exit(0)
	return _argv

def generate(argv):
	matrix = []
	for i in xrange(argv[0]):
		matrix.append([])
		for j in xrange(argv[0]):
			matrix[i].append(0)
	for i in xrange(argv[0]):
		for j in xrange(i+1, argv[0]):
			matrix[i][j] = matrix[j][i] = random.randint(argv[1], argv[2])

	return matrix

def print_matrix(matrix, width):
	num_format = "%" + str(width) + "s"
	for i in xrange(len(matrix)):
		line = "["
		for j in xrange(len(matrix[i])):
			line += num_format % str(matrix[i][j])
			if j != len(matrix[i])-1:
				line += ", "
		line = line + "]"
		if i != len(matrix)-1:
			line += ", \\"
		print line


if __name__ == '__main__':
	argv = check_argv(sys.argv)
	matrix = generate(argv)
	print_matrix(matrix, len(str(argv[2])))

