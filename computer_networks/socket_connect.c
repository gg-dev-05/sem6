#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[]) {
    struct sockaddr_in server;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket create failed\n");
        return 1;
    }
    printf("socket created\n");
    server.sin_addr.s_addr = inet_addr("142.250.192.46");
    server.sin_family = AF_INET;
    server.sin_port = htons(84);

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connection error\n");
        return 1;
    }
    printf("Connected\n");
    return 0;
}
