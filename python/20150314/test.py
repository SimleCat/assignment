from socket import * 
BUFSIZ = 1024
filename = "www.baidu.com"

c = socket(AF_INET, SOCK_STREAM)
c.connect(("baidu.com", 80))
fileobj = c.makefile('r', 0) 
fileobj.write("GET "+"http://" + filename + " HTTP/1.0\n\n")
# for line in fileobj:
# 	print line,

# data = c.recv(BUFSIZ)
# print data,
# while data:
# 	data = c.recv(BUFSIZ)
# 	print data,

print fileobj.readlines()

c.close()