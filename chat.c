#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

#include "util.h"

#include "client.h"
#include "server.h"

#define BUF_SIZE 256;



int main() {
	char command[BUF_SIZE];
	
	printf("Client or server? (c/s)\n");
        if(_getline(command, BUF_SIZE) == -1)
                errx(-1, "input too long");
        
        if(!strcmp(command, "c")) {
                start_client();
        } else if(!strcmp(command, "s")) {
                start_server();
        } else {
                errx(0, "put c or s");
        }
}
