#include <stdio.h>
#include <sys/socket.h>

int main(int argc, char const *argv[]) {
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        printf("socket creation failed\n");
        return 1;
    }
    printf("Socket created\n");
    return 0;
}
