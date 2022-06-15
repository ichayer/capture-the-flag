#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <unistd.h>

#define PORT 3000

int main(int argc, char* argv[]){

    // Creating a stream socket with an IPv4 domain.
    int socketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(socketFD < 0){
        perror("Error while creating a socket\n");
        return 1;
    }

    struct sockaddr_in server;

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    // Establishes a connection with server socket
    int connectStatus = connect(socketFD, (struct sockaddr *)&server, sizeof(server));

    if(connectStatus < 0){
        perror("Connection time-out\n");
        return 1;
    }

    printf("Connected\n");

    close(socketFD);
    
    return 0;
}
