FILE_PATH = r"yob1994.txt"

SEARCH_MODE = \
[\
"Exact March",\
"Start with",\
"Ends with",\
"Contains"\
]

def find(msg_list, letters, mode):
	result = []
	for msg in msg_list:
		if (mode == 1 and msg[0] == letters) or \
			(mode == 2 and msg[0].lower().startswith(letters.lower())) or \
			(mode == 3 and msg[0].lower().endswith(letters.lower())) or \
			(mode == 4 and letters.lower() in msg[0].lower()):
			result.append(msg)
	return result

def get_find_mode():
	print ("\nHow do you want to search:")
	i = 1
	for line in SEARCH_MODE:
		print ("%d\t%s" % (i, line))
		i += 1
	mode = 0
	while True:
		mode = input("Select: ")
		if mode and mode.isdigit():
			mode = int(mode)
		else:
			print ("Please enter a number between 1 to %d" % len(SEARCH_MODE))
			continue

		if mode >= 1 and mode <= len(SEARCH_MODE):
			break
		else:
			print ("Please enter a number between 1 to %d" % len(SEARCH_MODE))

	return mode

def get_msg(file_path):
	f = open(file_path) 
	msg_list = []
	for line in f:
		msg_list.append(line.strip().split(','))
	f.close()
	return msg_list

def get_items_max_length(msg_list):
	items_len = []
	for items in msg_list:
		for i in range(len(items)):
			if i >= len(items_len):
				items_len.append(len(items[i]))
			else:
				if items_len[i] < len(items[i]):
					items_len[i] = len(items[i])
	return items_len

def get_print_items(items_len, items):
	format_str = ""
	for i in range(len(items)):
		format_str += "%"
		if i != 2:
			format_str += "-"
		format_str += str(items_len[i]) + "s  "
	return format_str % tuple(items)

if __name__ == "__main__":
	msg_list = get_msg(FILE_PATH)
	while True:
		mode = get_find_mode();
		letters = input("Look for: ")
		if not letters:
			break
		ret = find(msg_list, letters, mode)
		if ret:
			items_len = get_items_max_length(ret)
			for data in ret:
				#print '\t'.join(data)
				print (get_print_items(items_len, data))
		else:
			print ("%s not found" % letters)