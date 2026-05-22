/* udp client driver program */
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

#define PORT 5000
#define MAXLINE 1000
#define SHUTDOWN_CMD "shutdown"

/* Driver code */
int main()
{   
    char input[100];
    char buffer[100];
    int sockfd;
    struct sockaddr_in servaddr;
    
    /* clear servaddr */
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;
    
    /* create datagram socket */
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    
    /* connect to server */
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        exit(0);
    }

    for (;;) {

        bzero(input, sizeof(input));

        if ((fgets(input, sizeof(input), stdin)) == NULL) {
            printf("failed to read input\n");
            exit(-1);
        }
        printf("%s\n", input);

        if (strcmp(SHUTDOWN_CMD, input)) {
            printf("shutdown command recieved\n");
            sendto(sockfd, SHUTDOWN_CMD, MAXLINE, 0, (struct sockaddr*)NULL,
                   sizeof(servaddr));
            goto normal_exit;
        }

        printf("sending nomral msg\n");

        /* 
         * request to send datagram
         * no need to specify server address in sendto
         * connect stores the peers IP and port
         */
        /* sendto(sockfd, input, MAXLINE, 0, (struct sockaddr*)NULL, sizeof(servaddr)); */
    }
    
normal_exit:
    /* waiting for response */
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)NULL, NULL);
    puts(buffer);

    /* close the descriptor */
    close(sockfd);

    return 0;
}
