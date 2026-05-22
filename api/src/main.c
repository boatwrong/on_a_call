/* server program for udp connection */
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 5000
#define MAXLINE 1000
#define SHUTDOWN_CMD "shutdown"

/* Driver code */
int main()
{
    char buffer[100];
    char *message = "shutdown complete";
    int listenfd;
    socklen_t len;
    ssize_t n;
    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;
    bzero(&servaddr, sizeof(servaddr));

    /* Create a UDP Socket */
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    /* bind server address to socket descriptor */
    bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    /*receive the datagram */
    len = sizeof(cliaddr);

    for (;;) {
        bzero(buffer, sizeof(buffer));

        /*receive message from server */
        n = recvfrom(listenfd, buffer, sizeof(buffer), 0,
                     (struct sockaddr*)&cliaddr, &len);
        buffer[n] = '\0';
        puts(buffer);

        if (0 == strcmp(SHUTDOWN_CMD, buffer)) {
        }
    }

    /* send the shutdown complete response */
    sendto(listenfd, message, strlen(message), 0, (struct sockaddr*)&cliaddr,
           sizeof(cliaddr));
    return 0;
}
