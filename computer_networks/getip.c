#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[]) {
    char *hostname = "www.facebook.com";
    char ip[100];
    struct hostent *he;
    struct in_addr **addr_list;
    int i;
    he = gethostbyname(hostname);
    if (he == NULL) {
        herror("gethostbyname");
        return 1;
    }

    addr_list = (struct in_addr **)he->h_addr_list;

    for (i = 0; addr_list[i] != NULL; i++) {
        strcpy(ip, inet_ntoa(*addr_list[i]));
        puts(ip);
    }
    printf("%s resolved to: %s\n", hostname, ip);
    printf("%s resolved to: %s\n", hostname, (char *)he->h_addr);

    return 0;
}
