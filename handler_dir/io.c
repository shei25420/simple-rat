#include "handler.h"

void SendData(int sock_fd, char *data){

	int bytes_left = strlen(data), bytes_written = 0;

	char no_bytes[7];

	snprintf(no_bytes, sizeof(no_bytes), "%d", bytes_left);

	//Send number of expected bytes
	write(sock_fd, no_bytes, bytes_left);

	//Send Data Now
	while(bytes_left > 0){

		if((bytes_written = write(sock_fd, data, bytes_left)) < 0){

			if(errno == EINTR){

				bytes_written = 0;
				continue;

			} else {
				ErrorMessage("	[!!] Error Sending Data");
			}
		}

		bytes_left -= bytes_written;

		data += bytes_written;
	}

	printf("	[DEBUG] Data Send Succesfully\n");

}

void RecvData(int sock_fd, char *buffer){

	int bytes_left = 0, bytes_read = 0;

	char bytes_to_read[7];

	char *p;

	//Get Number Of Bytes To Read
	if(read(sock_fd, bytes_to_read, 7) < 0){
		ErrorMessage("	[!!] Error Reading Data From Target");
	}

	printf("	[DEBUG:49:io.c] About to read %d bytes\n ", atoi(bytes_to_read));

	bytes_left = atoi(bytes_to_read);

	memset(buffer, 0, sizeof(buffer));

	p = buffer;

	while(bytes_left > 0) {

		if((bytes_read = read(sock_fd, p, bytes_left)) < 0){

			if(errno == EINTR){

				bytes_read = 0;

				continue;

			} else {
				ErrorMessage("	[!!] Error Reading Data From Target");
			}

		}

		bytes_left -= bytes_read;

		p += bytes_read;

	}

	buffer[atoi(bytes_to_read)];

	printf("	[DEBUG:79:io.c] Buffer Read is: %s\n", buffer);

}
