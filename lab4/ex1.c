#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
//#include <string.h>
//#include <signal.h>

int generateRandomNumber(int max) {
    
    return rand() % max;
}

int isPair(int number) {
    return (number % 2) == 0;
}


int main(int argc, char **argv) {
    //srand(time(NULL));
    int numSlaves = atoi(argv[1]);

    int numNumbers = atoi(argv[2]);
    
    if(argc < 3 || numSlaves <= 0 || numNumbers <= 0 ) exit(-1);

    int fileDescriptor[2];

    pipe(fileDescriptor);



    int i = 0;
    for(i = 0; i < numSlaves; i++) {
        if(fork() == 0) break;
    }

    if(i == numSlaves) {
        close(fileDescriptor[0]);
        for (int j = 0; j < numNumbers; j++) {
            int randNumber = generateRandomNumber(99999);
            write(fileDescriptor[1], &randNumber, sizeof(int));
        }
        close(fileDescriptor[1]);
    } else {
        close(fileDescriptor[1]); //close for writing
        int number = 0;
        while(read(fileDescriptor[0], &number, sizeof(number)) > 0) {
            printf("%d is %s pair\n", number, isPair(number) ? "" : "not");
        }
        
    }

    

    return 0;
}
