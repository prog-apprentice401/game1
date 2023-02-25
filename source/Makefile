CFLAGS=-Wall -lncurses -g

all: main.o ship.o colorPairs.o window.o
	gcc ${CFLAGS} main.o ship.o colorPairs.o window.o -o game.out

main.o: main.c ship.o colorPairs.o global.h window.o
	gcc -c ${CFLAGS} main.c 

ship.o: ship.c ship.h colorPairs.o global.h window.o
	gcc -c ${CFLAGS} ship.c 

colorPairs.o: colorPairs.c colorPairs.h
	gcc -c ${CFLAGS} colorPairs.c 

window.o: window.c window.h
	gcc -c ${CFLAGS} window.c 

clean:
	rm *.out *.o
