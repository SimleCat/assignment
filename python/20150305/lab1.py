import sys
import codecs

OUP_FILE = r"chinesetext_segmented.utf8"
HELP_MSG = \
'''
Please execute as below:
%s chinesetrad_wordlist.utf8 chinesetext.utf8
'''
MATCH_STAND_LEN = 5
MATCH_MAX_LEN = 12

def check_argv(argv):
	len_argv = len(argv)
	if len_argv != 3:
		if len_argv < 3:
			print "Too few parameters!"
		elif len_argv > 3:
			print "Too many parameters"
		print HELP_MSG % argv[0]
		exit(1)


def get_word_list(file_path):
	global MATCH_MAX_LEN
	word_list = [[],[],[],[],[],[]]
	f = codecs.open(file_path, mode='r', encoding="utf8")
	for line in f:
		line = line.strip()
		if len(line) > 5:
			word_list[5].append(line)
		else:
			word_list[len(line)-1].append(line)
		if MATCH_MAX_LEN < len(line):
			MATCH_MAX_LEN = len(line)
		#print line.encode("utf8")
	f.close()
	print "MATCH_MAX_LEN: ", MATCH_MAX_LEN
	return word_list

def match(word_list, line, ignore=None):
	if ignore:
		print "ignore: ",','.join(ignore).encode("utf8")
	for i in range(0, MATCH_STAND_LEN)[::-1]:
		word = line[:i+1]
		if ignore and word in ignore:
			continue
		if word in word_list[i]:
			return (i, word)
	return None

def match_more(word_list, line):
	for i in xrange(MATCH_STAND_LEN+1, MATCH_MAX_LEN+1):
		word = line[:i]
		if word in word_list[MATCH_STAND_LEN]:
			return (i-1, word)
	return None

def segmenter(word_list, line):
	words = []
	line_copy = line
	len_line = len(line)
	len_match = 0
	line_pre = []
	len_match_pre = []
	ignore = []
	none_cnt = 0
	line_last = ""
	print "len_line: ", len_line
	while True:
		print line.encode("utf8")
		ret = match(word_list, line, ignore)
		if not ret:
			print "not match"
			ret = match_more(word_list, line)
			if not ret:
				print "not match more"
				if not words:
					words.append(line_copy)
					break;
				ignore.append(words.pop())
				line_last = line
				line = line_pre.pop()
				len_match -= len_match_pre.pop()
				if none_cnt > 20:
					break
				none_cnt += 1
				continue
		# ignore = []
		line_pre.append(line)
		len_match_pre.append(ret[0]+1)
		len_match += ret[0]+1
		line = line[ret[0]+1:]
		words.append(ret[1])
		print "len_match: ", len_match
		if len_match >= len_line:
			break;
	return words

def segmenter_file(word_list, in_file, out_file):
	fin = codecs.open(in_file, mode='r', encoding="utf8")
	fout = codecs.open(out_file, mode='w', encoding="utf8")
	for line in fin:
		line = line.strip()
		words = segmenter(word_list, line)
		if words:
			line = " ".join(words)
		print line.encode("utf8")
		fout.write(line+"\n")
	fin.close()
	fout.close()



if __name__ == "__main__":
	check_argv(sys.argv)
	word_list = get_word_list(sys.argv[1])
	segmenter_file(word_list, sys.argv[2], OUP_FILE)
