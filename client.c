#include <stdio.h>
#include <stdlib.h>

#include "util.h"

int start_client() {
        printf("Starting client\n");

        // Open connection to server here

        const int bufsize = 1024;
        char *buf = malloc(bufsize);

        while(1) {
                print_prompt();

                if (_getline(buf, bufsize) == -1)
                        printf("Command too long, cannot be more than %d chars\n", bufsize);

                send_to_server(buf);
        }

        return 0;
}

void send_to_server(char *msg) {
}
