#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define PORT 8801

int main() {

	int sockfd;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;
	char buffer[1024];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("Server socket created successfully.\n");
	memset(&serverAddr, '\0', sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;	
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	printf("[+]Bind to port number %d.\n", PORT);

	listen(sockfd, 5);
	printf("[+]Listening...\n");

	newSocket = accept(sockfd, (struct sockaddr*)&newAddr, &addr_size);

	strcpy(buffer, "Hello");
	send(newSocket, buffer, strlen(buffer), 0);
	printf("[+]Closing the connection.\n");

	return 0;
}
