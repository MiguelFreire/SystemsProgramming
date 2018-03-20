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

    int n = 0;
    
    if(argc < 3 || numSlaves <= 0 || numNumbers <= 0 ) exit(-1);

    int fileDescriptorMS[2];
    int fileDescriptorSM[2];

    pipe(fileDescriptorMS);
    pipe(fileDescriptorSM);



    int i = 0;
    for(i = 0; i < numSlaves; i++) {
        if(fork() == 0) break;
    }

    if(i == numSlaves) {
        close(fileDescriptorMS[0]); //close for reading
        close(fileDescriptorSM[1]); //close for writing
        for (int j = 0; j < numNumbers; j++) {
            int randNumber = generateRandomNumber(99999);
            write(fileDescriptorMS[1], &randNumber, sizeof(int));
        }
        close(fileDescriptorMS[1]);
        int number = 0;
     
        while (read(fileDescriptorSM[0], &number, sizeof(number)) > 0)
        {
            printf("%d is pair!\n", number);
        }
        

    } else {
        close(fileDescriptorMS[1]); //close for writing
        close(fileDescriptorSM[0]);
        int number = 0;
        while(read(fileDescriptorMS[0], &number, sizeof(number)) > 0) {
            printf("Numero: %d\n", number);
            if(isPair(number)) {
                write(fileDescriptorSM[1], &number, sizeof(int));
            }
            
        }
        close(fileDescriptorSM[1]);
    }

    
    

    return 0;
}
