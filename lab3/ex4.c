#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>


int running = 0;

void childEndSignalHandler(int n) {
    running = 0;
}


int main(int argc, char **argv) {

    //Register Signal Handlers

    struct sigaction signalAction;

    signalAction.sa_handler = childEndSignalHandler;
    sigaction(20, &signalAction, NULL);

    FILE *file = fopen(argv[1],"r");
    char buffer[255];
    char *token;
    char child_argv[2][255];

    
    
    if(file == NULL) {
        printf("File %s not found \n", argv[1]);
        exit(0);
    }

    while(fgets(buffer, 254, file) != NULL) {
        printf("Buffer: %s\n", buffer);
        token = strtok(buffer, " \t");
        while(token) {
            printf("Token: %s\n", token);
            token = strtok(NULL, " \t");
        }

        return 0;

        running = 1;
        if(fork() == 0) {
            printf("Child Process: %s\n", buffer);
            strcpy(child_argv[0], buffer);
            execve(buffer, (char **)child_argv, NULL);
            printf("Child Process: %s is OVER!\n", buffer);
            exit(0);
        }
        else {
            while (running)
            {
                printf("Child is running...\n");
            }
        }
        
    }

    return 0;
}