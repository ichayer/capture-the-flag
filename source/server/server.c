// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

/* Standard library */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/* Local headers */
#include "challenges.h"
#include "utils.h"

#define PORT 8080
#define BACKLOG 5

int main(int argc, char* argv[]) {
    struct sockaddr_storage serverStorage;

    // Creating a stream socket with an IPv4 domain.
    int socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (socketFD < 0) {
        perror("Error in socket function");
        return 1;
    }

    // Avoid the EADDRINUSE (“Address already in use”) error when a TCP server is
    // restarted and tries to bind a socket to a port that currently has an associated TCP

    // A local port can't be reused (i.e., specified in a call to bind()) if any TCP connection incarnation with a
    // matching local port exists on the host. Enabling the SO_REUSEADDR socket option relaxes this constraint.

    // Setting the SO_REUSEADDR option means that we can bind a socket to a local port even if another TCP is bound to the same port.
    int optval = 1;
    if (setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        perror("Error in setsockopt function");
        return 1;
    }

    // An IPv4 socket address is stored in a sockaddr_in structure
    struct sockaddr_in serverAddress;

    // Ensures that all of the structure fields have the value 0
    memset(&serverAddress, 0, sizeof(struct sockaddr_in));

    // The sin_family identifies the socket domain
    // The sin_port and sin_addr fields are the port number and the IP address, both in network byte order.
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1"); // https://stackoverflow.com/questions/16508685/understanding-inaddr-any-for-socket-programming
    serverAddress.sin_port = htons(PORT);

    // Bind the socket to an address so that client can locate the socket.
    if (bind(socketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Error in bind function");
        return 1;
    }

    // Allows a stream socket to accept incoming connections from other sockets.
    if (listen(socketFD, BACKLOG) < 0) {
        perror("Error in listen function");
        return 1;
    }

    // Accepts a connection from a peer application on a listening stream socket, and optionally returns the address of the peer socket
    struct sockaddr_in client;
    socklen_t addressLength = sizeof(serverStorage);

    int newSocket = accept(socketFD, (struct sockaddr*)&client, &addressLength);
    if (newSocket < 0) {
        perror("Error in accept fucntion");
        return 1;
    }

    int index = 0;
    while (executeChallenge(index, newSocket, STDOUT_FILENO)) {
        index++;
    }

    clearScreen();
    printf("%s", "Felicitaciones, finalizaron el juego. Ahora deberán implementar el servidor que se comporte como el servidor provisto");

    close(socketFD);
    return 0;
}