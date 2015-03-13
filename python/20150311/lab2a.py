import nltk
from nltk.corpus import brown

brown_words = brown.words()

fd_tr = nltk.FreqDist(nltk.trigrams(brown_words))

sample_list = []
for sample in fd_tr:
	cnt = fd_tr[sample]
	if cnt >= 3:		
		tmp = (cnt, str(sample[0]), str(sample[1]), str(sample[2]))
		sample_list.append(tmp)

sample_list = sorted(sample_list, reverse = True)

for sample in sample_list:
	print "%d\t%s %s %s" % sample
