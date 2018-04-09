#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "clipboard.h"

 
int main(){
	char file_name[100];
	
	char store[10][MESSAGE_MAX_SIZE]; //dont forget to free it at the end

	sprintf(file_name, "./%s", OUTBOUND_FIFO);
	unlink(file_name);
	if(mkfifo(file_name, 0666)==-1){
		printf("Error creating out fifo\n");
		exit(-1);
	}
	int fifo_out = open(file_name, O_RDWR);
	if(fifo_out == -1){
		printf("Error opening in fifo\n");
		exit(-1);
	}
	
	
	
	sprintf(file_name, "./%s", INBOUND_FIFO);
	unlink(file_name);
	if(mkfifo(file_name, 0666)==-1){
		printf("Error creating in fifo\n");
		exit(-1);
	}
	int fifo_in = open(file_name, O_RDWR);
	if(fifo_in == -1){
		printf("Error opening in fifo\n");
		exit(-1);
	}

	//criar FIFOS
	
	//abrir FIFOS
	char data[MESSAGE_MAX_SIZE];

	Message msg;

	while(1){
		printf(".\n");
		read(fifo_in, &msg, sizeof(msg));

		switch(msg.type) {
			case COPY:
				printf("COPY REQUEST: \n");
				strcpy(data, msg.data);
				printf("Data received: %s\n", data);
				strcpy(store[msg.region], data);
				printf("Data stored in region: %d \n", msg.region);
				write(fifo_out, &(msg.size), sizeof(int));
				printf("END REQUEST\n");
				break;
			case PASTE:
				printf("PASTE REQUEST: \n");
				int size = strlen(store[msg.region]);
				printf("Data sent: %s\n", store[msg.region]);
				printf("Data sent from region : %d\n", msg.region);
				write(fifo_out, store[msg.region], size+1);
				printf("END REQUEST\n");
				break;
		}

	}
		
	exit(0);
	
}
