#include "handler.h"

int serv_fd = 0, cli_fd = 0;

char port[10];

struct sockaddr_in serv_addr, cli_addr;
socklen_t cli_len = sizeof(cli_addr);

void Server(){

	if((serv_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
		ErrorMessage("	[!!] Error Creating Server Socket");
	}

	printf("	[>>] Enter Port To Listen Connections From: ");

	if(fgets(port, sizeof(port), stdin) == NULL){
		ErrorQuit("	[!!] Error Getting Port Input");
	}

	memset(&serv_addr, 0, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(port));
	serv_addr.sin_addr.s_addr = INADDR_ANY;


	if(bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
		ErrorMessage("	[!!] Error Binding Address To Socket");
	}

	if(listen(serv_fd, 10) < 0){
		ErrorMessage("	[!!] Error Listening For Connections");
	}

	printf("	[>>] Waiting For Incoming Connections.....\n");

	if((cli_fd =  accept(serv_fd, (struct sockaddr *)&cli_addr, &cli_len)) < 0){
		ErrorMessage("	[!!] Error Accepting Connection");
	}

	printf("	[>>] Connection From: %s Successful\n", inet_ntoa(cli_addr.sin_addr));

	printf("	[>>] Starting Shell Session.....\n");

	Shell();

	if(cli_fd > 0) close(cli_fd);

	if(serv_fd > 0) close(serv_fd);

}


