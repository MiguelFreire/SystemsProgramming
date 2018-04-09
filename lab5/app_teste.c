#include "clipboard.h"
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){

		int fd = clipboard_connect("./");
		
		if(fd== -1){
			exit(-1);
		}
		char buffer[MESSAGE_MAX_SIZE];
		char dados[MESSAGE_MAX_SIZE];

		int region = 0;
		fgets(buffer, MESSAGE_MAX_SIZE, stdin);
		sscanf(buffer, "%s %d", dados, &region);
		
		int result = clipboard_copy(fd, region, dados, strlen(dados)+1);

		result ? printf("Copy successful!\n") : printf("Copy Failed\n");


		result = clipboard_paste(fd, 6, dados, strlen(dados) + 1);


		result ? printf("Paste successful: %s!\n", dados) : printf("Paste Failed\n");

		exit(0);
	}
