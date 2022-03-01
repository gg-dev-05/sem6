#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    struct sockaddr_in server, client;
    char message[100], server_reply[2000];

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket create failed\n");
        return 1;
    }
    printf("socket created\n");

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        puts("Bind failed\n");
        return 1;
    }
    puts("bind done\n");

    listen(sockfd, 2);

    while (1) {
        puts("Waiting for connections...\n");
        int c = sizeof(struct sockaddr_in);
        int new_socket = accept(sockfd, (struct sockaddr *)&client, (socklen_t *)&c);
        if (new_socket < 0) {
            perror("accept failed\n");
        }
        int clientPort = ntohs(client.sin_port);
        char *client_ip = inet_ntoa(client.sin_addr);
        puts("Connection accepted\n");
        snprintf(message, sizeof(message), "> %s:%d\n", client_ip, clientPort);
        puts(message);
        write(new_socket, &message, sizeof(message));
    }
    close(sockfd);
    return 0;
}
