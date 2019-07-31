#include "handler.h"

extern int serv_fd;
extern int cli_fd;

void ErrorQuit(char *msg){

	printf("	[!!] %s\n", msg);

	if(serv_fd > 0) close(serv_fd);

	if(cli_fd > 0) close(cli_fd);

	exit(-1);
}

void ErrorMessage(char *msg){

	if(serv_fd > 0) close(serv_fd);

	if(cli_fd > 0) close(cli_fd);

	perror(msg);

	exit(-1);
}
