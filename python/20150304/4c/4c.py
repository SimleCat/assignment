from urllib.request import urlopen

URL = r"http://robjhyndman.com/tsdldata/ecology1/hopedale.dat"

f = urlopen(URL)
for line in f:
	line = line.decode('utf-8')
	print (line,end="")