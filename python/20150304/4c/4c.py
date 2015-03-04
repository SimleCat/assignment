from urllib import urlopen

URL = r"http://robjhyndman.com/tsdldata/ecology1/hopedale.dat"

f = urlopen(URL)
for line in f:
	print line,