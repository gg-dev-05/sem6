/**
 * @file connections.h
 * @author Garvit Galgat (190001016)
 * @brief header file for both client and server
 * @date 2022-02-06
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netdb.h>
#include <sys/select.h>

// size for all the messages (sent and recieved)
#define BUFFER_SIZE 255
#define MAX_CLIENTS 3

/* struct for both server and client */
typedef struct connection {
    int socket;                     // socket
    struct sockaddr_in socketAddr;  // socket address
    /******** SERVER VARIABLES *******/
    struct connection *clients;  // array holding the list of all the clients
    /******** CLIENT VARIABLES *******/
    int isAlive;                   // is the client alive
    char *clientIP;                // the ip address (for client)
    int clientPort;                // the port (for client)
    char clientName[BUFFER_SIZE];  // clients name
} Connection;

/* struct for arguments for thread functions */
typedef struct {
    Connection *serverPtr;  // server pointer
    int index;              // index of current client in server's client array
} argsServerAndIndex;

/**
 * @brief display any error and exit the program
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
 * @brief initialize the server at the given port number
 *
 * @param portNumber port number for the server
 * @return server running at given port
 */
Connection initializeServer(int portNumber) {
    Connection server;
    server.socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server.socket == -1) error("Unable to create socket\n");
    printf("Socket created\n");

    server.socketAddr.sin_family = AF_INET;
    server.socketAddr.sin_addr.s_addr = INADDR_ANY;
    server.socketAddr.sin_port = htons(portNumber);

    if (bind(server.socket, (struct sockaddr *)&(server.socketAddr), sizeof(server.socketAddr)) < 0) {
        error("Unable to bind\n");
    }
    printf("Binding completed\n");

    server.clients = (Connection *)malloc(MAX_CLIENTS * sizeof(Connection));

    listen(server.socket, MAX_CLIENTS);
    char info[100];
    snprintf(info, sizeof(info), "Server listening on PORT:%d\n", portNumber);
    puts(info);

    return server;
}

/**
 * @brief send a message present in buffer to all alive clients
 *
 * @param server
 * @param buffer
 */
void broadcastToAll(Connection *server, char buffer[3 * BUFFER_SIZE]) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        // check if the client is alive
        if (server->clients[i].isAlive) {
            Connection client = server->clients[i];
            if (send(server->clients[i].socket, buffer, strlen(buffer), 0) < 0) {
                printf("[DEBUG] Unable to send message to %s:%d\n", client.clientIP, client.clientPort);
                server->clients[i].isAlive = 0;
            }
        }
    }
}

/**
 * @brief broadcast given message to every client except the client
 * with given index
 *
 * @param server
 * @param index
 * @param buffer
 */
void broadcastMessage(Connection *server, int index, char buffer[BUFFER_SIZE]) {
    Connection client = server->clients[index];
    char message[3 * BUFFER_SIZE];
    printf("[%s:%d] (%s) > %s", client.clientIP, client.clientPort, client.clientName, buffer);
    snprintf(message, 3 * BUFFER_SIZE, "(%s) > %s", client.clientName, buffer);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        // check if index not matches i, and client is alive
        if (i != index && server->clients[i].isAlive) {
            if (send(server->clients[i].socket, message, strlen(message), 0) < 0) {
                printf("[DEBUG] Unable to send message to %s:%d\n", client.clientIP, client.clientPort);
                server->clients[i].isAlive = 0;
            }
        }
    }
}

/**
 * @brief listen for messages from the client
 *
 * @param argsPtr includes server pointer and index of the client
 * @return void*
 */
void *messageListner(void *argsPtr) {
    argsServerAndIndex args = *((argsServerAndIndex *)argsPtr);
    int index = args.index;
    Connection *server = args.serverPtr;
    free(argsPtr);
    Connection client = server->clients[index];
    while (1) {
        char buffer[BUFFER_SIZE];
        resetBuffer(buffer);
        int byteSize = read(client.socket, buffer, BUFFER_SIZE);
        if (byteSize <= 0) {
            printf("[%s:%d (DISCONNECTED)]\n", client.clientIP, client.clientPort);
            char message[3 * BUFFER_SIZE];
            snprintf(message, 3 * BUFFER_SIZE, "(%s) LEFT THE CHATROOM\n", client.clientName);
            broadcastToAll(server, message);
            server->clients[index].isAlive = 0;
            return NULL;
        }
        broadcastMessage(server, index, buffer);
    }
}

/**
 * @brief initialize the client's connection start listening for its messages
 * and send back messages
 *
 * @param server
 * @param indexOfClient
 */
void getIncommingMessages(Connection *server, int indexOfClient) {
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "Welcome To The Chatroom\n");
    write(server->clients[indexOfClient].socket, &buffer, sizeof(buffer));

    // create new thread for listening messages
    pthread_t messageReaderThread;
    argsServerAndIndex *args = (argsServerAndIndex *)malloc(sizeof(argsServerAndIndex));
    args->serverPtr = server;
    args->index = indexOfClient;
    pthread_create(&messageReaderThread, NULL, messageListner, (void *)args);
}

/**
 * @brief function for thread to wait for client to send its name
 * if client is disconnected, set isAlive = 0
 * @param argsPtr (includes server and index of client)
 * @return void*
 */
void *getClientNameThreadFunction(void *argsPtr) {
    argsServerAndIndex args = *((argsServerAndIndex *)argsPtr);
    int index = args.index;
    Connection *server = args.serverPtr;
    free(argsPtr);
    char buffer[BUFFER_SIZE];
    resetBuffer(buffer);
    int byteSize = read(server->clients[index].socket, buffer, BUFFER_SIZE);
    if (byteSize == 0) {
        printf("[%s:%d (DISCONNECTED)]\n", server->clients[index].clientIP, server->clients[index].clientPort);
        char message[3 * BUFFER_SIZE];
        snprintf(message, 3 * BUFFER_SIZE, "[%s:%d](%s) LEFT THE CHATROOM\n", server->clients[index].clientIP, server->clients[index].clientPort, server->clients[index].clientName);
        broadcastToAll(server, message);
        server->clients[index].isAlive = 0;
        return NULL;
    } else if (byteSize < 0) {
        printf("Unable to get client's name for %s:%d\n", server->clients[index].clientIP, server->clients[index].clientPort);
        char message[3 * BUFFER_SIZE];
        snprintf(message, 3 * BUFFER_SIZE, "[%s:%d](%s) LEFT THE CHATROOM\n", server->clients[index].clientIP, server->clients[index].clientPort, server->clients[index].clientName);
        broadcastToAll(server, message);
        server->clients[index].isAlive = 0;
        return NULL;
    }

    // remove trailing newline from name
    int len = strlen(buffer);
    if (buffer[len - 1] == '\n') buffer[len - 1] = 0;

    // assign client's name from buffer
    strncpy(server->clients[index].clientName, buffer, BUFFER_SIZE);
    Connection client = server->clients[index];
    printf("Username: %s\nAddress: %s:%d\n", client.clientName, client.clientIP, client.clientPort);

    char message[3 * BUFFER_SIZE];
    snprintf(message, 3 * BUFFER_SIZE, "(%s) JOINED THE CHATROOM\n", server->clients[index].clientName);
    broadcastToAll(server, message);
    fflush(stdout);
    getIncommingMessages(server, index);
}

/**
 * @brief Get the Client Name object
 *
 * @param serverPtr pointer for server
 * @param indexOfClient index of the client
 */
void initializeClient(Connection *serverPtr, int indexOfClient) {
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "\n");
    write(serverPtr->clients[indexOfClient].socket, &buffer, sizeof(buffer));
    pthread_t getNameThread;
    argsServerAndIndex *args = (argsServerAndIndex *)malloc(sizeof(argsServerAndIndex));
    args->serverPtr = serverPtr;
    args->index = indexOfClient;
    pthread_create(&getNameThread, NULL, getClientNameThreadFunction, (void *)args);
}

/**
 * @brief accept a new connection and set accepted client as alive
 *
 * @param server pointer to server
 * @return index of client in the server's client array
 */
void acceptNewConnection(Connection *server) {
    int socket = server->socket;
    int addressSize = sizeof(struct sockaddr_in);
    struct sockaddr_in clientSockAddr;
    int clientFd = accept(socket, (struct sockaddr *)&clientSockAddr, (socklen_t *)&addressSize);
    if (clientFd <= 0) error("Accept Failed\n");
    char *clientIP = inet_ntoa(clientSockAddr.sin_addr);
    int clientPort = ntohs(clientSockAddr.sin_port);
    printf("[New Connection] => %s:%d\n", clientIP, clientPort);
    Connection client;
    client.socket = clientFd;
    client.socketAddr = clientSockAddr;
    client.clientIP = clientIP;
    client.clientPort = clientPort;
    client.isAlive = 1;              // set client as alive
    resetBuffer(client.clientName);  // reset buffer for name

    // add this client to the list of clients of server
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (!(server->clients[i].isAlive)) {
            server->clients[i] = client;
            initializeClient(server, i);  // get the name of this client
            return;
        }
    }
    printf("[SERVER LIMIT REACHED][Remove Connection] %s:%d\n", clientIP, clientPort);
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

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
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

    if (connect(serverSocket, (struct sockaddr *)&server, sizeof(server)) < 0) {
        error("Connection error\n");
    }
    printf("Connected\n");

    printf("Checking if server is available...[PLEASE WAIT]\n");

    struct timeval tv;
    tv.tv_sec = 2;  // wait for response from server for 2 secs
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(serverSocket, &rfds);
    int ret = select(serverSocket + 1, &rfds, NULL, NULL, &tv);
    if (ret == 0) {
        error("[SERVER NOT RESPONDING] (TIMEOUT)\n");
    }
    if (ret < 0) {
        error("[UNABLE TO READ BUFFER]\n");
    }
    return serverSocket;
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
        if (byteSize <= 0) {
            error("[SERVER DISCONNECTED]\n");
        }
        if (strncmp("QUIT", buffer, 4) == 0) {
            error("QUIT");
        }
        printf("%s", buffer);
        fflush(stdout);
    }
}