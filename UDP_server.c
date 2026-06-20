#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>


int main(int argc, char  **argv) {
	int port = 5501;
	int socketfd;
	struct sockaddr_in myaddr, remoteAddr;
	char buffer[1024];
	socklen_t addr_size;

	socketfd = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&myaddr, '\0', sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(port);
	myaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	bind(socketfd, (struct sockaddr *)&myaddr, sizeof(myaddr));
	addr_size = sizeof(remoteAddr);
	recvfrom(socketfd, buffer, 1024, 0, (struct sockaddr *)&remoteAddr, &addr_size);
	
	printf("got data from %s", buffer);

	return 0;
}
