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

    printf("Connected\n");
    
    char* lineBuf = NULL;
    size_t lineBufSize = 0;
    size_t lineLen;

    while ((lineLen = getline(&lineBuf, &lineBufSize, stdin)) >= 0) {
        printf("Sending %ld bytes: %s.\n", lineLen, lineBuf);
        fflush(stdout);
        if (send(socketFD, lineBuf, lineLen, 0) < 0) {
            perror("Failed to send");
            break;
        }
    }

    free(lineBuf);

    close(socketFD); // Server sees EOF
    return 0;
}
