FILE_PATH = r"planets2.txt"

def km_to_mi(km):
	mi = km * 0.6213712
	return int(mi)

f = open(FILE_PATH)
planets_list = []
for line in f:
	tmp_list = line.split(',')
	tmp_list[0] = tmp_list[0].strip()
	tmp_list[1] = int(tmp_list[1].strip())
	planets_list.append(tmp_list)
f.close()

# for data in planets_list:
# 	print "%s\t %d million km from Sun" % (data[0], data[1])

for data in planets_list:
	print ("%s\t %d million km = %d million miles from Sun, on average" %\
		(data[0], data[1], km_to_mi(data[1])))

