#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "util.h"
#include "client.h"

//PORT defined in util.h

#define OLD_IP "107.170.106.89"
#define LOCALHOST "127.0.0.1"

int start_client() {

        printf("Starting client\n");

        struct addrinfo hints, *servinfo;
        hints.ai_family = PF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        memset(&hints, 0, sizeof(hints));

        // Open connection to server here
        int rv = getaddrinfo(LOCALHOST, PORT, &hints, &servinfo);
        if (rv != 0) {
                fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
                return 1;
        }

        // loop through all the results and connect to the first we can
        struct addrinfo *p;
        int sockfd;
        for(p = servinfo; p != NULL; p = p->ai_next) {
                sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
                if (sockfd == -1) {
                        perror("client: socket");
                        continue;
                }

                if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
                        close(sockfd);
                        perror("client: connect");
                        continue;
                }

                break;
        }

        if (p == NULL) {
                fprintf(stderr, "client: failed to connect\n");
                return 2;
        }

        char s[INET6_ADDRSTRLEN];
        inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
                        s, sizeof s);
        printf("client: connecting to %s\n", s);

        freeaddrinfo(servinfo); // all done with this structure

        const int MAX_RECV_SIZE = 1024;
        char recv_buf[MAX_RECV_SIZE];
        int numbytes;

        const int BUF_SIZE = 1024;
        char *buf = malloc(BUF_SIZE);

        while(1) {
                // Receive from server
                if ((numbytes = recv(sockfd, recv_buf, MAX_RECV_SIZE-1, 0)) == -1) {
                        perror("recv");
                        exit(1);
                }

                recv_buf[numbytes] = '\0';
                printf("client: received '%s'\n", recv_buf);

                // Send input to server
                print_prompt();
                if (_getline(buf, BUF_SIZE) == -1)
                        printf("Command too long, cannot be more than %d chars\n", BUF_SIZE);

                send_to_server(buf, sockfd);
        }

        close(sockfd);
        return 0;
}

void send_to_server(char *msg, int sockfd) {
        printf("Sending the following message to the "
                        "server: %s\n", msg);

	if(send(sockfd, msg, strlen(msg), 0))
		perror("send");
	
}
