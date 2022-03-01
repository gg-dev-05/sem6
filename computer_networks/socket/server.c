#include <stdio.h>
#include <sys/socket.h>  //socket
#include <stdlib.h>      //strlen
#include <arpa/inet.h>   //inet_addr
#include <string.h>      //strlen
#include <unistd.h>      //read and write
#include <pthread.h>     //thread

/*
filename portno
argv[0] - filename
argv[1] - portno

Local server
*/
void error_fun(const char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please provide filename and port.\n");
        exit(1);
    }
    int socket_desc, client_socket, c, client_port, *client_sock, portno, byte_size;
    struct sockaddr_in server, client;
    char *client_ip, buffer[255];

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        error_fun("Could not create socket");
    }

    bzero((char *)&server, sizeof(server));
    portno = atoi(argv[1]);

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(portno);

    // Bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        error_fun("bind failed");
    }
    printf("bind done\n");

    // Listen
    listen(socket_desc, 3);

    // Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    client_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
    if (client_socket < 0) {
        error_fun("accept failed");
    }
    printf("Connection accepted");
    // ip address of the connected client
    client_ip = inet_ntoa(client.sin_addr);
    client_port = ntohs(client.sin_port);
    printf("Client ip is %s and cllient port is %d\n", client_ip, client_port);

    // loop for client server chat
    while (1) {
        bzero(buffer, 255);  // zero a byte string
        byte_size = read(client_socket, buffer, 255);
        if (byte_size == 0) {
            puts("Client disconnected");
            fflush(stdout);  // flush a stream
        } else if (byte_size < 0) {
            error_fun("Error on reading");
        }
        printf("Client : %s\n", buffer);
        bzero(buffer, 255);
        fgets(buffer, 255, stdin);  // input of characters and strings

        byte_size = write(client_socket, buffer, strlen(buffer));
        if (byte_size < 0) {
            error_fun("Error on writing.");
        }

        // condition for loop break
        int i = strncmp("close", buffer, 5);
        if (i == 0)
            break;
    }

    close(client_socket);
    close(socket_desc);
    return 0;
}
