#include "clipboard.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Message new_copy_message(int region, char *data) { return new_message(region, data, COPY); } 

Message new_paste_message(int region) { return new_message(region, NULL, PASTE); } 

Message new_message(int region, char* data, int type) {
	
	Message msg;

	msg.region = region;
	msg.type = type;

	if(data == NULL) {
		msg.size = 0;
		msg.data[0] = '\0';

		return msg;
	}

	msg.size = strlen(data);
	strcpy(msg.data, data);

	return msg;
} 

int clipboard_connect(char * clipboard_dir){
	char fifo_name[100];
	
	sprintf(fifo_name, "%s%s", clipboard_dir, INBOUND_FIFO);
	int fifo_send = open(fifo_name, O_WRONLY);
	sprintf(fifo_name, "%s%s", clipboard_dir, OUTBOUND_FIFO);
	int fifo_recv = open(fifo_name, O_RDONLY);
	if(fifo_recv < 0)
		return fifo_recv;
	else
		return fifo_send;
}

int clipboard_copy(int clipboard_id, int region, void *buf, size_t count){
		if(region > 9 || region < 0) 
			return 0;

		Message msg = new_copy_message(region, (char *) buf); //force buffer a string

		write(clipboard_id, &msg, sizeof(msg));

		int result = 0;
		
		read(clipboard_id+1, &result, sizeof(int)); 

		return result;
		
}

int clipboard_paste(int clipboard_id, int region, void *buf, size_t count){
	if (region > 9 || region < 0)
		return 0;
	//Lets send a message to the clipboard requesting the data o region X
	Message msg = new_paste_message(region); //create message request

	write(clipboard_id, &msg, sizeof(msg));

	char data[MESSAGE_MAX_SIZE];

	if(read(clipboard_id+1, data, count) == 0) return 0;

	strcpy((char*) buf, data);

	return strlen(data);
}
