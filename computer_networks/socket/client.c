#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>     //strlen
#include <arpa/inet.h>  //inet_addr
#include <string.h>     //strlen
#include <unistd.h>
#include <netdb.h>  //gethostbyname
/*
filename server_ipaddress portno
argv[0] - filename
argv[1] - server_ipaddress
argv[2] - portno
*/
void error_fun(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    int sockfd, connect_status, portno;
    struct sockaddr_in server;
    char buffer[255];
    struct hostent *server_host;

    if (argc < 3)  // if arguments are less than 3
    {
        printf("Please provide filename, hostname and port.\n");
        exit(1);
    }

    portno = atoi(argv[2]);
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        error_fun("Socket can not be created");
    }
    server_host = gethostbyname(argv[1]);
    if (server_host == NULL) {
        error_fun("Error, No such host");
    }

    bzero((char *)&server, sizeof(server));
    bcopy((char *)server_host->h_addr, (char *)&server.sin_addr.s_addr, server_host->h_length);
    // server.sin_addr.s_addr = inet_addr("142.250.194.196");//INADDR_ANY
    server.sin_family = AF_INET;
    server.sin_port = htons(portno);

    // Connect to remote server

    connect_status = connect(sockfd, (struct sockaddr *)&server, sizeof(server));
    printf("Connecting...%d", connect_status);
    if (connect_status < 0) {
        error_fun("connection error");
    }

    printf("Connected\n");

    // loop for client server chat
    while (1) {
        bzero(buffer, 255);  // zero a byte string
        printf("%s\n", buffer);
        fgets(buffer, 255, stdin);  // input of characters and strings

        // Receive a reply from the server
        if (recv(sockfd, buffer, 255, 0) < 0) {
            error_fun("recv failed");
        }
        printf("Server : %s\n", buffer);

        // condition for loop break
        int i = strncmp("close", buffer, 5);
        if (i == 0)
            break;
    }

    close(sockfd);
    return 0;
}
