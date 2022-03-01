#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    struct sockaddr_in server;
    char *message, server_reply[2000];

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket create failed\n");
        return 1;
    }
    printf("socket created\n");
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connection error\n");
        return 1;
    }
    printf("Connected\n");
    message = "GET / HTTP/1.1\r\n\r\n";
    puts("Sending...\n");
    puts(message);
    if (send(sockfd, message, strlen(message), 0) < 0) {
        puts("Send Failed\n");
        return 1;
    }
    puts("Data Sent\n");

    if (recv(sockfd, server_reply, 2000, 0) < 0) {
        puts("recv failed\n");
        return 1;
    }
    puts("reply recieved\n");
    puts(server_reply);
    // close(sockfd);
    return 0;
}
