#include <stdio.h>
#include <stdlib.h>



char *concatenateStrings(char *src, char *dest) {
    int j = 0 ,i = 0;

    while (dest[j] != '\0') j++;
    for(i = 0; src[i] != '\0'; i++) dest[i+j] = src[i];

    dest[i+j] = '\0';

    return dest;
}


int main(int argc, char **argv) {
    if(argc == 0) return 0;

    int size = 0;
    char *args = NULL;

    for(int i = 1; i < argc; i++) {
       
        size += sizeof(argv[i]);

        if(args == NULL) {
            args = (char *) malloc(size*sizeof(int));
            
            if(args == NULL) exit(0);

            args[0] = '\0';
        }
        else args = (char *)realloc(args, size*sizeof(int));

        args = concatenateStrings(argv[i], args);

        
    }
    
    printf("%s\n", args);

    free(args);

    return 0;   
}