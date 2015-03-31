#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <memory.h>
#include <pthread.h>
#include "map.h"

#define BUF_SIZE				64
#define SERVER1_PORT_BASE		21000
#define USC_ID					123
#define SERVER1_PORT 			(SERVER1_PORT_BASE + USC_ID)
#define SERVER1_ADDR			"localhost"
#define FILE_CLIENT1			"client1.txt"
#define FILE_CLIENT2			"client2.txt"

void *client(void *arg){
	int client_num = (int)arg;
	// Get Map
	PMAP head = NULL;
	if (1 == client_num){
		get_map(&head, FILE_CLIENT1);
	} else{
		get_map(&head, FILE_CLIENT2);
	}
		
	// Get Server1 IP
	struct hostent *my_hostent = gethostbyname(SERVER1_ADDR);
	char my_ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, my_hostent->h_addr_list[0], my_ip, sizeof(my_ip));
	// Create Socket
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0){
		perror("Error: Create socket failed!\n");
		pthread_exit((void *)1);
	}
	// Bind
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	if (inet_pton(AF_INET, my_ip, &server_addr.sin_addr) < 0){
		perror("Error: inet_pton failed!\n");
		pthread_exit((void *)1);
	}
	server_addr.sin_port = htons(SERVER1_PORT);
	// Get Input
	char buf[BUF_SIZE];
	printf("Please Enter Your Search(USC,UCLA ect.): ");
	scanf("%s", buf);
	// Get Value
	PMAP node = map_find(head, buf);
	if (NULL == node){
		printf("The %s can not found!\n", buf);
		pthread_exit((void *)1);
	}
	printf("The Client %d has received a request with search word %s, which maps to key %s.\n", \
		client_num, buf, node->value);
	// Send
	struct sockaddr_in client_addr;
	socklen_t client_len = sizeof(client_addr);
	char str[INET_ADDRSTRLEN];
	sprintf(buf, "GET %s", node->value);
	int cnt = sendto(sockfd, buf, strlen(buf)+1, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (cnt < 0){
		perror("Error: Sendto failed!\n");
		pthread_exit((void *)1);
	}
	printf("The Client %d sends the request %s to the Server 1 with port number %d and IP address %s.\n", \
		client_num, buf, SERVER1_PORT, my_ip);
	getsockname(sockfd, (struct sockaddr *)&client_addr, &client_len);
	printf("The Client1`s port number is %d and the IP address is %s.\n", \
		ntohs(client_addr.sin_port), inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str)));
	// Receive
	cnt = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &client_len);
	if (cnt < 0){
		perror("Error: recvfrom failed!\n");
		pthread_exit((void *)1);
	}
	char *value;
	value = strtok(buf, " ");
	value = strtok(NULL, " ");
	printf("The Client %d received the value %s from the Server 1 with port number %d and IP address %s.\n", \
		client_num, value, ntohs(client_addr.sin_port), inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str)));
	getsockname(sockfd, (struct sockaddr *)&client_addr, &client_len);
	printf("The Client%d`s port number is %d and the IP address is %s.\n", \
		client_num, ntohs(client_addr.sin_port), inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str)));
	// Free Map
	map_free(head);
	// Close Socket
	close(sockfd);
	pthread_exit((void *)0);
}


int main(void){
	int i = 0;
	for (i=1; i<=2; i++){
		pthread_t tid;
		if (pthread_create(&tid, NULL, client, (void *)i) != 0){
			perror("Error: pthread_create failed!\n");
			exit(1);
		}
		pthread_join(tid, NULL);		
	}
	return 0;
}
