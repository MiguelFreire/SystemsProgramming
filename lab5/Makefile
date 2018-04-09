all: cliente servidor

cliente: app_teste.o library.o
			gcc -o client app_teste.o library.o
servidor: clipboard.o library.o
			gcc -o server clipboard.o library.o
app_teste.o: app_teste.c clipboard.h
			gcc -c app_teste.c -Wall
library.o: library.c clipboard.h
			gcc -c library.c -Wall
clipboard.o: clipboard.c clipboard.h
			gcc -c clipboard.c -Wall
clean:
			rm -rf *.o
			rm client
			rm server