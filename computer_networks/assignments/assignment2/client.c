/**
 * @file client.c
 * @author Garvit Galgat (190001016)
 * @date 2022-02-06
 */

#include "connections.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        error("Please provide HOSTNAME and PORT.\n");
    }

    int server = connectToServer(argv[1], atoi(argv[2]));

    // creating a thread to listen for messages from server
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

    // sending messages to server
    while (1) {
        resetBuffer(buffer);
        fgets(buffer, BUFFER_SIZE, stdin);
        if (strncmp("QUIT", buffer, 4) == 0) break;
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
