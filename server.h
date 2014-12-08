#ifndef SERVER_H
#define SERVER_H

#include "util.h"

//PORT defined in util.h

int start_server();
void sigchld_handler(int s);

#endif
