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

Connection initializeServer(int portNumber) {
    Connection server;
    server.socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server.socket == -1) error_fun("Unable to create socket\n");
    printf("Socket created\n");

    server.socketAddr.sin_family = AF_INET;
    server.socketAddr.sin_addr.s_addr = INADDR_ANY;
    server.socketAddr.sin_port = htons(portNumber);

    if (bind(server.socket, (struct sockaddr *)&(server.socketAddr), sizeof(server.socketAddr)) < 0) {
        error_fun("Unable to bind\n");
    }
    printf("Binding completed\n");

    server.clients = (Connection *)malloc(MAX_CLIENTS * sizeof(Connection));

    listen(server.socket, MAX_CLIENTS);
    char info[100];
    snprintf(info, sizeof(info), "Server listening on PORT:%d\n", portNumber);
    puts(info);

    return server;
}

void broadcastToAll(Connection *server, char buffer[3 * BUFFER_SIZE]) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].isAlive) {
            Connection client = server->clients[i];
            if (send(server->clients[i].socket, buffer, strlen(buffer), 0) < 0) {
                server->clients[i].isAlive = 0;
            }
        }
    }
}

void broadcastMessage(Connection *server, int index, char buffer[BUFFER_SIZE]) {
    Connection client = server->clients[index];
    char message[3 * BUFFER_SIZE];
    snprintf(message, 3 * BUFFER_SIZE, "(%s) > %s", client.clientName, buffer);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (i != index && server->clients[i].isAlive) {
            if (send(server->clients[i].socket, message, strlen(message), 0) < 0) {
                server->clients[i].isAlive = 0;
            }
        }
    }
}

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
            char message[3 * BUFFER_SIZE];
            snprintf(message, 3 * BUFFER_SIZE, "(%s) LEFT THE CHATROOM\n", client.clientName);
            broadcastToAll(server, message);
            server->clients[index].isAlive = 0;
            return NULL;
        }
        broadcastMessage(server, index, buffer);
    }
}

void getIncommingMessages(Connection *server, int indexOfClient) {
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "Welcome To The Chatroom\n");
    write(server->clients[indexOfClient].socket, &buffer, sizeof(buffer));

    pthread_t messageReaderThread;
    argsServerAndIndex *args = (argsServerAndIndex *)malloc(sizeof(argsServerAndIndex));
    args->serverPtr = server;
    args->index = indexOfClient;
    pthread_create(&messageReaderThread, NULL, messageListner, (void *)args);
}

void *getClientNameThreadFunction(void *argsPtr) {
    argsServerAndIndex args = *((argsServerAndIndex *)argsPtr);
    int index = args.index;
    Connection *server = args.serverPtr;
    free(argsPtr);
    char buffer[BUFFER_SIZE];
    resetBuffer(buffer);
    int byteSize = read(server->clients[index].socket, buffer, BUFFER_SIZE);
    if (byteSize == 0) {
        char message[3 * BUFFER_SIZE];
        snprintf(message, 3 * BUFFER_SIZE, "%s LEFT THE CHATROOM\n", server->clients[index].clientName);
        broadcastToAll(server, message);
        server->clients[index].isAlive = 0;
        return NULL;
    } else if (byteSize < 0) {
        char message[3 * BUFFER_SIZE];
        snprintf(message, 3 * BUFFER_SIZE, "%s LEFT THE CHATROOM\n", server->clients[index].clientName);
        broadcastToAll(server, message);
        server->clients[index].isAlive = 0;
        return NULL;
    }

    int len = strlen(buffer);
    if (buffer[len - 1] == '\n') buffer[len - 1] = 0;

    strncpy(server->clients[index].clientName, buffer, BUFFER_SIZE);
    Connection client = server->clients[index];
    printf("Username: %s\nAddress: %s:%d\n", client.clientName, client.clientIP, client.clientPort);

    char message[3 * BUFFER_SIZE];
    snprintf(message, 3 * BUFFER_SIZE, "(%s) JOINED THE CHATROOM\n", server->clients[index].clientName);
    broadcastToAll(server, message);
    fflush(stdout);
    getIncommingMessages(server, index);
}

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

void acceptNewConnection(Connection *server) {
    int socket = server->socket;
    int addressSize = sizeof(struct sockaddr_in);
    struct sockaddr_in clientSockAddr;
    int clientFd = accept(socket, (struct sockaddr *)&clientSockAddr, (socklen_t *)&addressSize);
    if (clientFd <= 0) error_fun("Accept Failed\n");
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

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (!(server->clients[i].isAlive)) {
            server->clients[i] = client;
            initializeClient(server, i);  // get the name of this client
            return;
        }
    }
    printf("[SERVER LIMIT REACHED][Remove Connection] %s:%d\n", clientIP, clientPort);
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

    printf("Checking if server is available...[PLEASE WAIT]\n");

    struct timeval tv;
    tv.tv_sec = 2;  // wait for response from server for 2 secs
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(serverSocket, &rfds);
    int ret = select(serverSocket + 1, &rfds, NULL, NULL, &tv);
    if (ret == 0) {
        error_fun("[SERVER NOT RESPONDING] (TIMEOUT)\n");
    }
    if (ret < 0) {
        error_fun("[UNABLE TO READ BUFFER]\n");
    }
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
            error_fun("[SERVER DISCONNECTED]\n");
        }
        printf("%s", buffer);
        fflush(stdout);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        error_fun("Please provide PORT number\n");
    }

    Connection server = initializeServer(atoi(argv[1]));

    while (1) {
        acceptNewConnection(&server);
    }

    return 0;
}
