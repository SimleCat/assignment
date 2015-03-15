from socket import * 

HOST = "192.168.0.105"
PORT = 21567
ADDR = (HOST, PORT)
BUFSIZ = 2048

tcpCliSock = socket(AF_INET, SOCK_STREAM)
# tcpCliSock.connect(ADDR)

while True:
	data = raw_input("> ")
	if not data:
		break
	tcpCliSock.connect(ADDR)
	tcpCliSock.send(data)

tcpCliSock.close()