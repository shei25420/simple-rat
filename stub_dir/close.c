#include "stub.h"

extern SOCKET sock_fd;

void CloseSocket(){
	closesocket(sock_fd);
}
