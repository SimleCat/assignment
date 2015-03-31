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
#include <signal.h>
#include <memory.h>
#include "map.h"

#define BUF_SIZE				64
#define SERVER1_PORT_BASE		21000
#define SERVER2_PORT_BASE		22000
#define SERVER3_PORT_BASE		23000
#define USC_ID					123
#define SERVER1_PORT 			(SERVER1_PORT_BASE + USC_ID)
#define SERVER2_PORT 			(SERVER2_PORT_BASE + USC_ID)
#define SERVER3_PORT 			(SERVER3_PORT_BASE + USC_ID)
#define SERVER1_ADDR			"localhost"
#define SERVER2_ADDR			"localhost"
#define SERVER3_ADDR			"localhost"

#define FILE_SERVER1			"server1.txt"
#define FILE_SERVER2			"server2.txt"
#define FILE_SERVER3			"server3.txt"

#define CLIENT_NUM				2

void server1(void){
	// Get Server IP
	struct hostent *my_hostent = gethostbyname(SERVER1_ADDR);
	char my_ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, my_hostent->h_addr_list[0], my_ip, sizeof(my_ip));
	// Get Map
	PMAP head = NULL;
	get_map(&head, FILE_SERVER1);
	// Create Socket
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0){
		perror("Error: Create socket failed!\n");
		exit(1);
	}
	// Bind
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	if (inet_pton(AF_INET, my_ip, &server_addr.sin_addr) < 0){
		perror("Error: inet_pton failed!\n");
		exit(1);
	}
	server_addr.sin_port = htons(SERVER1_PORT);
	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		perror("Error: Bind failed!\n");
		exit(1);
	}
	printf("The Server 1 has UDP port number %d and IP address %s.\n", \
		SERVER1_PORT, my_ip);
	// Recive and Block
	struct sockaddr_in client_addr;
	struct sockaddr_in addr;
	char buf[BUF_SIZE];
	char str[INET_ADDRSTRLEN];
	socklen_t client_len = sizeof(client_addr);
	int client_cnt = 0;
	for(;;){
		int cnt = recvfrom(sockfd, buf, BUF_SIZE, 0, (struct sockaddr *)&client_addr, &client_len);
		if ( cnt < 0){
			perror("Error: recvfrom failed!\n");
			exit(1);
		}
		// Client Count
		client_cnt ++;
		// printf("Raw rev: [%s]\n", buf);
		char *key;
		key = strtok(buf, " ");
		key = strtok(NULL, " ");
		printf("The Server 1 has received a request with key %s from client %d with port number %d and IP address %s.\n", \
			key, client_cnt, ntohs(client_addr.sin_port), inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str)));
		PMAP node = map_find(head, key);
		if (NULL == node){// Value Not Found
			//Create Socket
			int sockfd2 = socket(AF_INET, SOCK_STREAM, 0);
			struct sockaddr_in server_addr2;
			memset(&server_addr2, 0, sizeof(server_addr2));
			server_addr2.sin_family = AF_INET;
			inet_pton(AF_INET, my_ip, &server_addr2.sin_addr);
			server_addr2.sin_port = htons(SERVER2_PORT);
			if (connect(sockfd2, (struct sockaddr *)&server_addr2, sizeof(server_addr2)) != 0){
				perror("Error: connect failed!\n");
				exit(1);
			}
			// Write To Server2
			char key_tmp[KEY_SIZE];
			strcpy(key_tmp, key);
			sprintf(buf, "GET %s", key);
			write(sockfd2, buf, strlen(buf)+1);
			printf("The Sever 1 sends the request %s to the Server 2.\n", buf);
			getsockname(sockfd2, (struct sockaddr *)&addr, &client_len);
			printf("The TCP port number is %d and the IP address is %s.\n", \
				ntohs(addr.sin_port), inet_ntop(AF_INET, &addr.sin_addr, str, sizeof(str)));
			// Read From Server2
			read(sockfd2, buf, BUF_SIZE);
			char *value;
			value = strtok(buf, " ");
			value = strtok(NULL, " ");
			printf("The Server 1 received the value %s from the Server 2 with port number %d and IP address %s.\n", \
				value, SERVER2_PORT, my_ip);
			// Close Socket
			close(sockfd2);
			printf("The Server 1 closed the TCP connection with the Server 2.\n");
			sprintf(buf, "POST %s", value);
			map_insert(&head, key_tmp, value);
		}else{
			sprintf(buf, "POST %s", node->value);
		}
		// Send To Client
		sendto(sockfd, buf, strlen(buf)+1, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
		printf("The Server 1 sends the reply %s to Client %d with port number %d and IP address %s.\n", \
			buf, client_cnt, ntohs(client_addr.sin_port), inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str)));
		if (client_cnt >= CLIENT_NUM){
			break;
		}
	}
	// Free Map
	map_free(head);
	// Close Socket
	close(sockfd);

	exit(0);
}

void server2(void){
	// Get Server IP
	struct hostent *my_hostent = gethostbyname(SERVER2_ADDR);
	char my_ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, my_hostent->h_addr_list[0], my_ip, sizeof(my_ip));
	// Get Map
	PMAP head = NULL;
	get_map(&head, FILE_SERVER2);
	// Create Socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("Error: Create socket failed!\n");
		exit(1);
	}
	// Bind
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	if (inet_pton(AF_INET, my_ip, &server_addr.sin_addr) < 0){
		perror("Error: inet_pton failed!\n");
		exit(1);
	}
	server_addr.sin_port = htons(SERVER2_PORT);
	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		perror("Error: Bind failed!\n");
		exit(1);
	}
	// Listen
	listen(sockfd, 2);
	printf("The Server 2 has TCP port number %d and IP address %s.\n", \
		SERVER2_PORT, my_ip);
	for(;;){
		// Accept
		struct sockaddr_in client_addr;
		struct sockaddr_in addr;
		char buf[BUF_SIZE];
		char str[INET_ADDRSTRLEN];
		socklen_t client_len = sizeof(client_addr);
		int client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
		// Read From Server1
		read(client_fd, buf, BUF_SIZE);
		// printf("Raw rev: [%s]\n", buf);
		char *key;
		key = strtok(buf, " ");
		key = strtok(NULL, " ");
		printf("The Server 2 has received a request with key %s from the Server 1 with port number %d and IP address %s.\n", \
			key, ntohs(client_addr.sin_port), inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str)));
		// Find Value By Key
		PMAP node = map_find(head, key);
		if (NULL == node){	// Not Found
			// Create Socket
			int sockfd3 = socket(AF_INET, SOCK_STREAM, 0);
			struct sockaddr_in server_addr3;
			memset(&server_addr3, 0, sizeof(server_addr3));
			server_addr3.sin_family = AF_INET;
			inet_pton(AF_INET, my_ip, &server_addr3.sin_addr);
			server_addr3.sin_port = htons(SERVER3_PORT);
			if (connect(sockfd3, (struct sockaddr *)&server_addr3, sizeof(server_addr3)) != 0){
				perror("Error: connect failed!\n");
				exit(1);
			}
			// Write To Server3
			char key_tmp[KEY_SIZE];
			strcpy(key_tmp, key);
			sprintf(buf, "GET %s", key);
			write(sockfd3, buf, strlen(buf)+1);
			printf("The Sever 2 sends the request %s to the Server 3.\n", buf);
			getsockname(sockfd3, (struct sockaddr *)&addr, &client_len);
			printf("The TCP port number is %d and the IP address is %s.\n", \
				ntohs(addr.sin_port), inet_ntop(AF_INET, &addr.sin_addr, str, sizeof(str)));
			// Read From Server3
			read(sockfd3, buf, BUF_SIZE);
			char *value;
			value = strtok(buf, " ");
			value = strtok(NULL, " ");
			printf("The Server 2 received the value %s from the Server 3 with port number %d and IP address %s.\n", \
				value, SERVER3_PORT, my_ip);
			// Close Socket
			close(sockfd3);
			printf("The Server 2 closed the TCP connection with the Server 3.\n");
			sprintf(buf, "POST %s", value);
			map_insert(&head, key_tmp, value);
		}else{
			sprintf(buf, "POST %s", node->value);
		}
		// Write To Server1
		write(client_fd, buf, strlen(buf)+1);
		printf("The Server 2 sends the reply %s to the Server 1 with port number %d and IP address %s.\n", \
			buf, ntohs(client_addr.sin_port), inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str)));
		// Close Socket
		close(client_fd);		
	}
	// Free Map
	map_free(head);
	// Close Socket
	close(sockfd);

	exit(0);
}

void server3(void){
	// Get Server IP
	struct hostent *my_hostent = gethostbyname(SERVER3_ADDR);
	char my_ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, my_hostent->h_addr_list[0], my_ip, sizeof(my_ip));
	// Get Map
	PMAP head = NULL;
	get_map(&head, FILE_SERVER3);
	// Create Socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		perror("Error: Create socket failed!\n");
		exit(1);
	}
	// Bind
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	// server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (inet_pton(AF_INET, my_ip, &server_addr.sin_addr) < 0){
		perror("Error: inet_pton failed!\n");
		exit(1);
	}
	server_addr.sin_port = htons(SERVER3_PORT);
	if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		perror("Error: Bind failed!\n");
		exit(1);
	}
	// Listen
	listen(sockfd, 2);
	printf("The Server 3 has TCP port number %d and IP address %s.\n", \
		SERVER3_PORT, my_ip);
	for(;;){
		// Accept
		struct sockaddr_in client_addr;
		char buf[BUF_SIZE];
		char str[INET_ADDRSTRLEN];
		socklen_t client_len = sizeof(client_addr);
		int client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
		// Read From Server2
		read(client_fd, buf, BUF_SIZE);
		// printf("Raw rev: [%s]\n", buf);
		char *key;
		key = strtok(buf, " ");
		key = strtok(NULL, " ");
		printf("The Server 3 has received a request with key %s from the Server 2 with port number %d and IP address %s.\n", \
			key, ntohs(client_addr.sin_port), inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str)));
		PMAP node = map_find(head, key);
		if (NULL == node){
			sprintf(buf, "POST NULL");
		}else{
			sprintf(buf, "POST %s", node->value);
		}
		// Write To Server2
		write(client_fd, buf, strlen(buf)+1);
		printf("The Server 3 sends the reply %s to the Server2 with port number %d and IP address %s.\n", \
			buf, ntohs(client_addr.sin_port), inet_ntop(AF_INET, &client_addr.sin_addr, str, sizeof(str)));
		// Close Socket
		close(client_fd);		
	}
	
	map_free(head);
	close(sockfd);

	exit(0);
}

int main(void){
	pid_t pids[3] = {0};

	if ((pids[0] = fork()) < 0){
		perror("Error: fork failed!\n");
	} else if(pids[0] == 0){
		server1();
	} else{
		if ((pids[1] = fork()) < 0){
			perror("Error: fork failed!\n");
		} else if(pids[1] == 0){
			server2();
		}else{
			if ((pids[2] = fork()) < 0){
				perror("Error: fork failed!\n");
			} else if(pids[2] == 0){
				server3();
			}else{
				int status;
				waitpid(pids[0], &status, 0);
				kill(pids[1], SIGKILL);
				kill(pids[2], SIGKILL);
			}
		}
	}
	return 0;
}