from socket import * 

HOST = "192.168.0.105"
PORT = 21567
ADDR = (HOST, PORT)
BUFSIZ = 2048

tcpSerSock = socket(AF_INET, SOCK_STREAM) 
tcpSerSock.bind(ADDR)
tcpSerSock.listen(5)

while True:
	print 'Ready to serve...' 
	tcpCliSock, addr = tcpSerSock.accept() 
	print 'Received a connection from:', addr
	message = tcpCliSock.recv(BUFSIZ)# Fill in start. # Fill in end.
	print "tcpCliSock message start"
	print message
	print "tcpCliSock message end"
	tcpCliSock.close()

tcpSerSock.close()