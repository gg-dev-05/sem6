#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netdb.h>
#include <sys/select.h>

#define BUFFER_SIZE 500
#define MAX_CLIENTS 2

typedef struct connection {
    int socket;
    struct sockaddr_in socketAddr;
    struct connection *clients;
    int isAlive;
    char *clientIP;
    int clientPort;
    char clientName[BUFFER_SIZE];
} Connection;

typedef struct {
    Connection *serverPtr;
    int index;
} argsServerAndIndex;

void error_fun(const char *err) {
    printf("%s\n", err);
    exit(1);
}

void resetBuffer(char buffer[BUFFER_SIZE]) {
    bzero(buffer, BUFFER_SIZE);
}

int connectToServer(char *hostName, int port) {
    struct sockaddr_in server;

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        printf("socket create failed\n");
        return 1;
    }
    printf("socket created\n");

    struct hostent *server_host = gethostbyname(hostName);
    if (server_host == NULL) {
        error_fun("Error, No such host");
    }

    bcopy((char *)server_host->h_addr, (char *)&server.sin_addr.s_addr, server_host->h_length);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (connect(serverSocket, (struct sockaddr *)&server, sizeof(server)) < 0) {
        error_fun("Connection error_fun\n");
    }
    printf("Connected\n");

    return serverSocket;
}

void *printServerMessages(void *serverPtr) {
    int server = *((int *)serverPtr);
    free(serverPtr);
    while (1) {
        char buffer[BUFFER_SIZE];
        resetBuffer(buffer);
        int byteSize = read(server, buffer, BUFFER_SIZE);
        if (byteSize <= 0) {
            error_fun("SERVER DISCONNECTED\n");
        }
        if (strncmp("QUIT", buffer, 4) == 0) {
            error_fun("QUIT");
        }
        printf("%s", buffer);
        fflush(stdout);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        error_fun("Please provide HOSTNAME and PORT.\n");
    }

    int server = connectToServer(argv[1], atoi(argv[2]));

    int *serverPtr = malloc(sizeof(int));
    *serverPtr = server;

    char buffer[BUFFER_SIZE];
    resetBuffer(buffer);

    printf("Enter Your Name: ");
    resetBuffer(buffer);
    fgets(buffer, BUFFER_SIZE, stdin);
    if (send(server, buffer, strlen(buffer), 0) < 0) {
        puts("Send Failed\n");
        return 1;
    }

    pthread_t serverMessageReader;
    pthread_create(&serverMessageReader, NULL, printServerMessages, serverPtr);

    while (1) {
        resetBuffer(buffer);
        fgets(buffer, BUFFER_SIZE, stdin);
        if (send(server, buffer, strlen(buffer), 0) < 0) {
            puts("Send Failed\n");
            return 1;
        }
    }

    pthread_cancel(serverMessageReader);
    close(server);
    free(serverPtr);
    return 0;
}
