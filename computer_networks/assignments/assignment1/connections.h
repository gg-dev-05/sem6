/**
 * @file connections.h
 * @author Garvit Galgat (190001016)
 * @date 2022-01-30
 * header file for the the functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netdb.h>

// size for all the messages (sent and recieved)
#define BUFFER_SIZE 255

/* struct connection for both server and client */
struct connection {
    int socket;                     // socket
    struct sockaddr_in socketAddr;  // socket address
    char *clientIP;                 // the ip address (for client)
    int clientPort;                 // the port (for client)
};

/**
 * @brief display any erro and exit the program
 *
 * @param err error message
 */
void error(const char *err) {
    printf("%s\n", err);
    exit(1);
}

/**
 * @brief reset the buffer to zero
 *
 * @param buffer
 */
void resetBuffer(char buffer[BUFFER_SIZE]) {
    bzero(buffer, BUFFER_SIZE);
}

/**
 * @brief initialize the server at the given port number with given
 * number of maximum simultaneous clients
 *
 * @param portNumber port number for the server
 * @param numberOfConnections maximum number of simultaneous connections
 * @return int server socket
 */
int initializeServer(int portNumber, int numberOfConnections) {
    struct sockaddr_in serverSockAddr;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) error("Unable to create socket\n");
    printf("Socket created\n");

    serverSockAddr.sin_family = AF_INET;  // Address Family Internet
    serverSockAddr.sin_addr.s_addr = INADDR_ANY;
    serverSockAddr.sin_port = htons(portNumber);  // host to network (short)

    if (bind(serverSocket, (struct sockaddr *)&serverSockAddr, sizeof(serverSockAddr)) < 0) {
        error("Unable to bind\n");
    }
    printf("Binding completed\n");

    listen(serverSocket, numberOfConnections);
    char info[100];
    snprintf(info, sizeof(info), "Server listening on PORT:%d\n", portNumber);
    puts(info);

    return serverSocket;
}

/**
 * @brief accept new connections
 *
 * @param server server socket
 * @return struct connection new client connection
 */
struct connection acceptNewConnection(int server) {
    int addressSize = sizeof(struct sockaddr_in);
    struct sockaddr_in clientSockAddr;
    int clientFd = accept(server, (struct sockaddr *)&clientSockAddr, (socklen_t *)&addressSize);
    if (clientFd < 0) error("Accept Failed\n");
    char *clientIP = inet_ntoa(clientSockAddr.sin_addr);
    int clientPort = ntohs(clientSockAddr.sin_port);
    printf("[New Connection] => %s:%d\n", clientIP, clientPort);
    struct connection client;
    client.socket = clientFd;
    client.socketAddr = clientSockAddr;
    client.clientIP = clientIP;
    client.clientPort = clientPort;
    return client;
}

/**
 * @brief function for a thread to keep running and print clients messages
 *
 * @param clientPtr client pointer
 * @return void*
 */
void *printClientMessages(void *clientPtr) {
    struct connection client = *((struct connection *)clientPtr);
    free(clientPtr);
    while (1) {
        char buffer[BUFFER_SIZE];
        resetBuffer(buffer);
        int byteSize = read(client.socket, buffer, BUFFER_SIZE);
        if (byteSize == 0) {
            printf("[%s:%d (DISCONNECTED)]\n", client.clientIP, client.clientPort);
            fflush(stdout);
            error("");
        } else if (byteSize < 0) {
            error("Unable to read buffer\n");
        }
        printf("[%s:%d] %s", client.clientIP, client.clientPort, buffer);
    }
}

/**
 * @brief initialize the client's connection start listening for its messages
 * and send back messages
 *
 * @param client
 */
void handleConnection(struct connection client) {
    char message[100];
    snprintf(message, sizeof(message), "Connection OK\n");
    write(client.socket, &message, sizeof(message));

    pthread_t messageReaderThread;
    struct connection *clientPtr = malloc(sizeof(struct connection));
    *clientPtr = client;
    pthread_create(&messageReaderThread, NULL, printClientMessages, clientPtr);
    char buffer[BUFFER_SIZE];
    while (1) {
        resetBuffer(buffer);
        fgets(buffer, BUFFER_SIZE, stdin);
        write(client.socket, buffer, sizeof(buffer));
    }
}

/******************************** CLIENT FUNCTIONS *************************************/

/**
 * @brief initialize server connection at given port
 *
 * @param port int port
 * @return int server socket
 */
int connectToServer(char *hostName, int port) {
    struct sockaddr_in server;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket create failed\n");
        return 1;
    }
    printf("socket created\n");

    struct hostent *server_host = gethostbyname(hostName);
    if (server_host == NULL) {
        error("Error, No such host");
    }

    bcopy((char *)server_host->h_addr, (char *)&server.sin_addr.s_addr, server_host->h_length);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        error("Connection error\n");
    }
    printf("Connected\n");

    char message[BUFFER_SIZE];
    if (recv(sockfd, message, 2000, 0) < 0) {
        error("recv failed\n");
    }
    printf("[DEBUG] %s", message);
    return sockfd;
}

/**
 * @brief function for a thread to keep running and print servers messages
 *
 * @param serverPtr server pointer
 * @return void*
 */
void *printServerMessages(void *serverPtr) {
    int server = *((int *)serverPtr);
    free(serverPtr);
    while (1) {
        char buffer[BUFFER_SIZE];
        resetBuffer(buffer);
        int byteSize = read(server, buffer, BUFFER_SIZE);
        if (byteSize == 0) {
            fflush(stdout);
            error("[SERVER DISCONNECTED]\n");
        } else if (byteSize < 0) {
            error("Unable to read buffer\n");
        }
        if (strncmp("QUIT", buffer, 4) == 0) {
            error("QUIT");
        }
        printf("[SERVER] %s", buffer);
    }
}