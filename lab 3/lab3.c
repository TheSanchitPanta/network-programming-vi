#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd, client_sockets[MAX_CLIENTS];
    fd_set readfds;
    int max_fd;
    char buffer[BUFFER_SIZE];

    // Initialize client sockets to 0
    for(int i = 0; i < MAX_CLIENTS; i++)
        client_sockets[i] = 0;

    // Create server socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 5);

    printf("Server listening on port %d...\n", PORT);

    while(1) {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_fd = server_fd;

        // Add client sockets
        for(int i = 0; i < MAX_CLIENTS; i++) {
            if(client_sockets[i] > 0) {
                FD_SET(client_sockets[i], &readfds);
                if(client_sockets[i] > max_fd)
                    max_fd = client_sockets[i];
            }
        }

        select(max_fd + 1, &readfds, NULL, NULL, NULL);

        // New client connection
        if(FD_ISSET(server_fd, &readfds)) {
            client_fd = accept(server_fd, NULL, NULL);
            
            for(int i = 0; i < MAX_CLIENTS; i++) {
                if(client_sockets[i] == 0) {
                    client_sockets[i] = client_fd;
                    printf("New client connected (fd = %d)\n", client_fd);
                    break;
                }
            }
        }

        // Handle client messages
        for(int i = 0; i < MAX_CLIENTS; i++) {
            int sd = client_sockets[i];
            
            if(FD_ISSET(sd, &readfds)) {
                int bytes = read(sd, buffer, BUFFER_SIZE);
                
                if(bytes == 0) {
                    // Client disconnected
                    printf("Client disconnected (fd = %d)\n", sd);
                    close(sd);
                    client_sockets[i] = 0;
                } 
                else {
                    buffer[bytes] = '\0';
                    printf("Client %d: %s", sd, buffer);
                    send(sd, buffer, bytes, 0);  // Echo back
                }
            }
        }
    }

    return 0;
}