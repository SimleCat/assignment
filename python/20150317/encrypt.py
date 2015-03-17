import random


def random_encipher(s, n):
	random.seed(n)
	letters = list("abcdefghijklmnopqrstuvwxyz")
	random.shuffle(letters)
	result = ""
	a_value = ord("a")
	for element in s:
		if element.islower():
			element = letters[ord(element) - a_value]
		result += element
	return result

def random_decipher(s, n):
	random.seed(n)
	letters = list("abcdefghijklmnopqrstuvwxyz")
	random.shuffle(letters)
	result = ""
	a_value = ord("a")
	for element in s:
		if element.islower():
			element = chr(letters.index(element) + a_value)
		result += element
	return result

def rot(c, n):
	if c.islower():
		value = ord(c) + n
		if value > ord('z'):
			value = ord('a') + (value - ord('z')) - 1
		elif value < ord('a'):
			value = ord('z') - (ord('a') - value) + 1
		c = chr(value)
	return c

def rotate_encipher(s, n):
	result = ""
	for element in s:
		result += rot(element, n)
	return result

def letProb(c):
	if c == ' ': return 0.1904     
	if c == 'e': return 0.1017     
	if c == 't': return 0.0737     
	if c == 'a': return 0.0661     
	if c == 'o': return 0.0610     
	if c == 'i': return 0.0562     
	if c == 'n': return 0.0557     
	if c == 'h': return 0.0542     
	if c == 's': return 0.0508     
	if c == 'r': return 0.0458     
	if c == 'd': return 0.0369     
	if c == 'l': return 0.0325     
	if c == 'u': return 0.0228     
	if c == 'm': return 0.0205     
	if c == 'c': return 0.0192     
	if c == 'w': return 0.0190     
	if c == 'f': return 0.0175     
	if c == 'y': return 0.0165     
	if c == 'g': return 0.0161     
	if c == 'p': return 0.0131     
	if c == 'b': return 0.0115     
	if c == 'v': return 0.0088     
	if c == 'k': return 0.0066     
	if c == 'x': return 0.0014     
	if c == 'j': return 0.0008     
	if c == 'q': return 0.0008     
	if c == 'z': return 0.0005     
	return 1.0 

def letProb_str(s):
	prob = 0.0
	for c in s:
		prob += letProb(c)
	return prob


def rotate_decipher(s):
	all_encodings = [rotate_encipher(s, -n) for n in range(26)]
	for i, item in enumerate(all_encodings):
		prob = letProb_str(item)
		all_encodings[i] = [item, prob]
		# print "%d\t%s\t%f" % (i, item, prob)
	# print all_encodings
	return max(all_encodings, key = lambda x : x[1])[0]


if __name__ == "__main__":
	s = raw_input("Pelase input a string: ")
	if not s:
		exit(0)
	n = 0
	while True:
		n = raw_input("Please input a number: ")
		if n.isdigit():
			n = int(n)
			break
	print "s = %s, n = %d" % (s, n)

	print "\nrandom_encipher(\"%s\", %d)" % (s, n)
	ret = random_encipher(s, n)
	print ret

	print "\nrandom_decipher(\"%s\", %d)" % (ret, n)
	ret = random_decipher(ret, n)
	print ret

	print "\nrotate_encipher(\"%s\", %d)" % (s, n)
	ret = rotate_encipher(s, n)
	print ret

	print "\nrotate_decipher(\"%s\")" % ret
	ret = rotate_decipher(ret)
	print ret