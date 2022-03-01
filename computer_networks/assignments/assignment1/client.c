/**
 * @file client.c
 * @author Garvit Galgat (190001016)
 * @date 2022-01-30
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
    pthread_t serverMessageReader;
    pthread_create(&serverMessageReader, NULL, printServerMessages, serverPtr);

    // sending messages to server
    char buffer[BUFFER_SIZE];
    while (1) {
        fgets(buffer, BUFFER_SIZE, stdin);
        if (strncmp("QUIT", buffer, 4) == 0) break;
        if (send(server, buffer, strlen(buffer), 0) < 0) {
            puts("Send Failed\n");
            return 1;
        }
    }

    close(server);
    free(serverPtr);
    return 0;
}
