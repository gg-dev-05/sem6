/**
 * @file server.c
 * @author Garvit Galgat (190001016)
 * @date 2022-01-30
 */

#include "connections.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        error("Please provide PORT number\n");
    }

    // initialize the server at the specified port
    int serverSocket = initializeServer(atoi(argv[1]), 3);

    while (1) {
        // if any new connections comes up handle it with handleConnection

        struct connection client = acceptNewConnection(serverSocket);
        handleConnection(client);
    }

    return 0;
}
