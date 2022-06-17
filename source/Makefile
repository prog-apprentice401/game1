CFLAGS=-Wall -lncurses
FILES=main.o ship.o colorPairs.o

all: ${FILES}
	gcc ${CFLAGS} ${FILES} -o game.out

main.o: main.c ship.o colorPairs.o global.h
	gcc main.c -c ${CFLAGS}

ship.o: ship.c ship.h colorPairs.o global.h
	gcc ship.c -c ${CFLAGS}

colorPairs.o: colorPairs.c colorPairs.h
	gcc colorPairs.c -c ${CFLAGS}

clean:
	rm *.out *.o
