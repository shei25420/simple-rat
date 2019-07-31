#include "stub.h"

void SendData(SOCKET sock_fd, char *data){

	char bytesToSend[7];

	memset(bytesToSend, 0, sizeof(bytesToSend));

	snprintf(bytesToSend, sizeof(bytesToSend), "%d", strlen(data));

	MessageBox(NULL, bytesToSend, "Bytes To Send", NULL);

	//Send Number Of Bytes TO send
	if(send(sock_fd, bytesToSend, 7, 0) == SOCKET_ERROR){
		CloseSocket();
	}

	if(send(sock_fd, data, strlen(data), 0) == SOCKET_ERROR){
		CloseSocket();
	}

}

void RecvData(SOCKET sock_fd, char *buffer){

	char bytes_left[7];

	memset(buffer, 0, sizeof(buffer));

	memset(bytes_left, 0, sizeof(bytes_left));

	//Recieve Number Of Bytes Expected
	if(recv(sock_fd, bytes_left, 7, 0) == SOCKET_ERROR){
		CloseSocket();
	}

	//Retrive Data Received
	if(recv(sock_fd, buffer, atoi(bytes_left), 0) == SOCKET_ERROR){
			CloseSocket();
	}


}
