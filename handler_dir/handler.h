#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

extern int errno;

extern void ErrorQuit(char *msg);
extern void ErrorMessage(char *msg);

extern void SendData(int sock_fd, char *data);
extern void RecvData(int sock_fd, char *buffer);

extern void Shell();

extern void Server();
