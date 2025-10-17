CC = gcc
CFLAGS = -std=c11 -Werror -Wall -g -lm

all: main

main: main.o bmp.o transformations.o
	$(CC) $(CFLAGS) -o bmp main.o bmp.o transformations.o

main.o: main.c bmp.h transformations.h
	$(CC) $(CFLAGS) -c main.c

transformations.o: transformations.c
	$(CC) $(CFLAGS) -c transformations.c

bmp.o: bmp.c
	$(CC) $(CFLAGS) -c bmp.c

clean:
	rm bmp *.o
