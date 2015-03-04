from urllib import urlopen

URL = r"http://www.cs.uoregon.edu/Classes/15W/cis122/data/yob1994.txt"
RESULTS_FILE_PATH = r"results.txt"

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
	print "\nHow do you want to search:"
	i = 1
	for line in SEARCH_MODE:
		print "%d\t%s" % (i, line)
		i += 1
	mode = 0
	while True:
		mode = raw_input("Select: ")
		if mode and mode.isdigit():
			mode = int(mode)
		else:
			print "Please enter a number between 1 to %d" % len(SEARCH_MODE)
			continue

		if mode >= 1 and mode <= len(SEARCH_MODE):
			break
		else:
			print "Please enter a number between 1 to %d" % len(SEARCH_MODE)

	return mode

def get_msg(url):
	f = urlopen(url) 
	msg_list = []
	for line in f:
		msg_list.append(line.strip().split(','))
	f.close()
	return msg_list

def get_items_max_length(msg_list):
	items_len = []
	for items in msg_list:
		for i in xrange(len(items)):
			if i >= len(items_len):
				items_len.append(len(items[i]))
			else:
				if items_len[i] < len(items[i]):
					items_len[i] = len(items[i])
	return items_len

def get_print_items(items_len, items):
	format_str = ""
	for i in xrange(len(items)):
		format_str += "%"
		if i != 2:
			format_str += "-"
		format_str += str(items_len[i]) + "s  "
	return format_str % tuple(items)

if __name__ == "__main__":
	msg_list = get_msg(URL)
	f = open(RESULTS_FILE_PATH, "w")
	while True:
		mode = get_find_mode();
		letters = raw_input("Look for: ")
		if not letters:
			break
		ret = find(msg_list, letters, mode)
		if mode > 1:
			f.write("\nLook for \"%s\" by \"%s\":\n" % (letters, SEARCH_MODE[mode-1]))
		if ret:
			items_len = get_items_max_length(ret)
			for data in ret:
				if mode > 1:
					f.write(','.join(data) + "\n")
				#print '\t'.join(data)
				print get_print_items(items_len, data)
		else:
			print "%s not found" % letters
			if mode > 1:
				f.write("%s not found\n" % letters)
		if mode > 1:
			f.flush()
	f.close()