from socket import * 
import sys
import os

HOST = ''
PORT = 8888
BUFSIZ = 1024
DNS = ["com", "net", "org", "biz", "cc", "tv", "name", "me", "info", "us", "cn", "jp"]

if len(sys.argv) <= 1: 
	print 'Usage : "python ProxyServer.py server_ip"\n[server_ip : It is the IP Address Of Proxy Server' 
	sys.exit(2) 
# Create a server socket, bind it to a port and start listening 
tcpSerSock = socket(AF_INET, SOCK_STREAM) 
# Fill in start.
HOST = sys.argv[1]
if len(sys.argv) == 3:
	PORT = int(sys.argv[2])
tcpSerSock.bind((HOST, PORT))
tcpSerSock.listen(5)
hostn_pre = ''
# Fill in end. 
while 1: 
	# Strat receiving data from the client 
	print '\nReady to serve...' 
	tcpCliSock, addr = tcpSerSock.accept() 
	print 'Received a connection from:', addr 
	message = tcpCliSock.recv(BUFSIZ)# Fill in start. # Fill in end.
	if not message.strip():
		tcpCliSock.close()
		continue
	print message
	# Extract the filename from the given message 
	print message.split()[1] 
	filename = message.split()[1].partition("/")[2] 
	print filename 
	fileExist = False
	# filetouse = "/" + filename 
	# print filetouse 
	try: 
		# Check wether the file exist in the cache 
		# f = open(filetouse[1:], "rb")

		hostn = filename.replace("www.","",1)
		hostn = hostn.split('/')[0]
		print "hostn.split('.'):", hostn.split('.')
		if len(hostn.split('.')) > 1 and hostn.split('.')[-1] in DNS:
			pass
		else:
			filename = "www."+hostn_pre+"/"+filename
			hostn = hostn_pre

		print "hostn:", hostn
		hostn_pre = hostn
		tmpList = filename.split('/')
		tmpDir = ''
		if len(tmpList) == 1 or not tmpList[1]:
			tmpDir = tmpList[0]
			filename = tmpList[0] + "/index.html"
		else:
			tmpDir = '/'.join(tmpList[:-1])
		print "dir:", tmpDir
		print "filename:", filename
		f = open(filename, "r")

		print "open %s sucess" % filename
		outputdata = f.readlines()
		f.close()
		fileExist = True
		# ProxyServer finds a cache hit and generates a response message 
		tcpCliSock.send("HTTP/1.0 200 OK\r\n") 
		tcpCliSock.send("Content-Type:text/html\r\n")
		tcpCliSock.send("\r\n")
		# Fill in start. 
		if len(outputdata) == 0:
			raise IOError('Not Found!')
		else:
			for line in outputdata:
				tcpCliSock.send(line)
				print line,
		# Fill in end.
			print '\nRead from cache' 
	# Error handling for file not found in cache 
	except IOError: 
		if fileExist == False: 
			# Create a socket on the proxyserver 
			c = socket(AF_INET, SOCK_STREAM)# Fill in start. # Fill in end.
			# hostn = filename.replace("www.","",1)
			# print hostn 
			try: 
				# Connect to the socket to port 80 
				# Fill in start. 

				c.connect((hostn, 80))
				# Fill in end.
				# Create a temporary file on this socket and ask port 80 for the file requested by the client 
				fileobj = c.makefile('r', 0) 
				fileobj.write("GET "+"http://" + filename + " HTTP/1.0\n\n") 
				# Read the response into buffer 
				# Fill in start. 
				data = fileobj.readlines()
				fileobj.close()
				# print data
				# Fill in end.
				# Create a new file in the cache for the requested file. 
				# Also send the response in the buffer to client socket and the corresponding file in the cache 
				if not os.path.exists(tmpDir):
					os.makedirs(tmpDir)
				tmpFile = open("./" + filename,"wb")
				# Fill in start. 
				tcpCliSock.send("HTTP/1.0 200 OK\r\n") 
				tcpCliSock.send("Content-Type:text/html\r\n")
				tcpCliSock.send("\r\n")
				isData = False
				for line in data:
					print line,
					if not isData and not line.strip():
						print "start save"
						isData = True
						continue
					if isData:
						tmpFile.write(line)
						tcpCliSock.send(line)
				tmpFile.close()
				# Fill in end.
			except Exception, e: 
				print "Illegal request" 
				print e
		else: 
			# HTTP response message for file not found 
			# Fill in start. 
			print "Not Found"
			tcpCliSock.send("<html><h1>404 Not Found!</h1></html>")
			# Fill in end.
	# Close the client and the server sockets 
	tcpCliSock.close() 
# Fill in start. 
tcpSerSock.close()
print "End!"
# Fill in end. 