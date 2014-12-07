#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include "util.h"
#include "client.h"

int start_client() {
        const int PORT = 10000;
        char *port_string;
        sprintf(port_string, "%d", PORT);

        printf("Starting client\n");

        // Open connection to server here
        struct addrinfo hints, *res, *res0;
        hints.ai_family = PF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        memset(&hints, 0, sizeof(hints));

        int error = getaddrinfo("107.170.106.89", port_string, &hints, &res0);

        const int BUF_SIZE = 1024;
        char *buf = malloc(BUF_SIZE);

        while(1) {
                print_prompt();

                if (_getline(buf, BUF_SIZE) == -1)
                        printf("Command too long, cannot be more than %d chars\n", BUF_SIZE);

                send_to_server(buf);
        }

        return 0;
}

void send_to_server(char *msg) {
}
