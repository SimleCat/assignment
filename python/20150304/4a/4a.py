FILE_PATH = r"planets.txt"

f = open(FILE_PATH)
planets_list = f.readlines()
f.close()

for line in planets_list:
	print line,
