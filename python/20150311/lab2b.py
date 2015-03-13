import nltk
import math
from nltk.corpus import brown
from pylab import *

MIN_FREQ 	= 10
LOG_N		= 10

#brown_words = brown.words()
brown_words = brown.words(categories='editorial')
fd = nltk.FreqDist(brown_words)
fd_bi = nltk.FreqDist(nltk.bigrams(brown_words))

sample_list = []
for sample in fd:
	cnt = fd[sample]
	if cnt >= 10:		
		tmp = (cnt, str(sample))
		sample_list.append(tmp)

print "**** word ****"
print "word number:", len(sample_list)
sample_list = sorted(sample_list, reverse = True)
y1 = []
i = 1
print "Line\tFreq\tword"
for sample in sample_list:
	y1.append(math.log(sample[0], 10))
	print "%d\t%d\t%s" % (i, sample[0], sample[1])
	i += 1

x1 = range(len(y1))

sample_list = []
for sample in fd_bi:
	cnt = fd_bi[sample]
	if cnt >= 10:		
		tmp = (cnt, str(sample[0]), str(sample[1]))
		sample_list.append(tmp)
		
print "**** bigram ****"
print "bigram number:", len(sample_list)
sample_list = sorted(sample_list, reverse = True)
y2 = []
i = 1
print "Line\tFreq\tbigram"
for sample in sample_list:
	y2.append(math.log(sample[0], 10))
	print "%d\t%d\t%s %s " % (i, sample[0], sample[1], sample[2])
	i += 1

x2 = range(len(y2))

subplot(211)
plot(x1, y1)
xlabel("rank")
ylabel("lgFreq")
title("Word")
grid(True)
subplot(212)
plot(x2, y2)
subplots_adjust(hspace = 0.5)
title("Bigram")
xlabel("rank")
ylabel("lgFreq")
grid(True)

show()
