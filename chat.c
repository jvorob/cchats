#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

#define BUFF_SIZE 256;

int client();
int server();

int main() {
	char command[BUFF_SIZE];
	
	printf("Client or server? (c/s)\n");

}


int client() {
	char command[BUFF_SIZE];
	char exit_flag = 0;
	int count, i;
	int file;

	int argc = 0;
	char *argv[MAX_ARGS];

	printf("Starting client\n");

	while(!exit_flag) {
		print_prompt();

		if((count = _getline(command, BUFF_SIZE)) == -1) { //getline
			printf("Command too long, cannot be more than %d chars\n", BUFF_SIZE);
		} else {

		}
	}

	return 0;
}
