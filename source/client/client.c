// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/* Standard library */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080

int main(int argc, char* argv[]) {
    // Creating a stream socket with an IPv4 domain.
    int socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);

    if (socketFD < 0) {
        perror("Error while creating a socket");
        return 1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);

    // Establishes a connection with server socket
    int status = connect(socketFD, (struct sockaddr*)&server, sizeof(server));
    if (status < 0) {
        perror("Connection time-out");
        return 1;
    }

    char* lineBuf = NULL;
    size_t lineBufSize = 0;
    size_t lineLen;

    while ((lineLen = getline(&lineBuf, &lineBufSize, stdin)) >= 0) {
        if (send(socketFD, lineBuf, lineLen, 0) < 0) {
            perror("Failed to send");
            break;
        }
    }

    printf("Disconnected.\n");

    free(lineBuf);
    close(socketFD);
    return 0;
}