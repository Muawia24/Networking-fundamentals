#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define APP_MAX_BUFFER 1024
#define PORT 8080

int main()
{
    int server_fd, client_fd;

    struct sockaddr_in address;
    int addres_len = sizeof(address);

    char buffer[APP_MAX_BUFFER] = {0};

    // Initialize socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // bind socket to port
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // create queue for incoming connections
    // Listen for incoming connections with a backlog of 10
    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("\nWaiting for a connection...\n");

        // Accept client connection client_fd == connection
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addres_len)) < 0) {
            perror("Accept failed");
            exit(EXIT_FAILURE);
        }

        // Read data from client
        read(client_fd, buffer, APP_MAX_BUFFER);
        printf("Received request:\n%s\n", buffer);

	char *http_response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 13\r\n\r\nHello, World!";

    	// write to socket
    	// send queue os
    	write(client_fd, http_response, strlen(http_response));

    	// close the connection
    	close(client_fd);
    }

    return 0;
}
