/**
 * @file server.c
 * @author Garvit Galgat (190001016)
 * @date 2022-02-06
 */

#include "connections.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        error("Please provide PORT number\n");
    }

    // initialize the server at the specified port
    Connection server = initializeServer(atoi(argv[1]));

    while (1) {
        // accepting new connections
        acceptNewConnection(&server);
    }

    return 0;
}
