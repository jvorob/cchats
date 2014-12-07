#ifndef CLIENT_H
#define CLIENT_H

void *get_in_addr(struct sockaddr*);
int start_client();
void send_to_server(char*);

#endif
