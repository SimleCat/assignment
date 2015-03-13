#-*- encoding: utf-8 -*-

import nltk
# from nltk.corpus import webtext

# fd = nltk.FreqDist(webtext.words())

# fd.plot(20)


# from nltk.corpus import brown
# brown_words = brown.words(categories='editorial')
# fd_bi = nltk.FreqDist(nltk.bigrams(brown_words))
# print fd_bi
# fd_bi.plot(20)


from nltk.corpus import brown

#create a set of stop words and single character punctuation
unwanted = set(nltk.corpus.stopwords.words("english"))
unwanted.update(list('!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~£'))

iter_bigrams = nltk.bigrams( brown.words(categories='editorial') )
fd_bi = nltk.FreqDist( (w1.lower(),w2.lower()) for w1,w2 in iter_bigrams
    if not (w1.lower() in unwanted or w2.lower() in unwanted) )

print fd_bi.items()[0:20]
#print fd_bi.keys()[:20]
print fd_bi[fd_bi.max()],"\t",fd_bi.max()
i = 0
for sample in fd_bi:
	print fd_bi[sample],"\t",
	print sample
	if i >= 20:
		break;
	i += 1
	#print "%d\t%s" % (sample[1], str(sample[0]))

fd_bi.plot(20)

#fd_bi.tabulate()