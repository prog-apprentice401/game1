CFLAGS=-Wall -lncurses
FILES=main.o ship.o colorPairs.o window.o

all: ${FILES}
	gcc ${CFLAGS} ${FILES} -o game.out

main.o: main.c ship.o colorPairs.o global.h window.o
	gcc main.c -c ${CFLAGS}

ship.o: ship.c ship.h colorPairs.o global.h window.o
	gcc ship.c -c ${CFLAGS}

colorPairs.o: colorPairs.c colorPairs.h
	gcc colorPairs.c -c ${CFLAGS}

window.o: window.c window.h
	gcc window.c -c ${CFLAGS}

clean:
	rm *.out *.o
