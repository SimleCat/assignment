FILE_PATH = r"yob1994short.txt"

def find(msg_list, name):
	result = []
	for msg in msg_list:
		if msg[0] == name:
			result.append(msg)
	return result

f = open(FILE_PATH) 
msg_list = []
items_len = []
for line in f:
	print (line, end="")
	msg_list.append(line.strip().split(','))
f.close()

while True:
	name = input("\nLook for: ")
	if not name:
		break
	ret = find(msg_list, name)
	if ret:
		for data in ret:
			print ('\t'.join(data))
	else:
		print ("%s not found" % name)
