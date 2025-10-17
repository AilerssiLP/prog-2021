# variables
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -g
LDLIBS=-lm
INPUT=playlist.c track.c main.c
OUTPUT=compile

all:
	$(CC) $(CFLAGS) $(INPUT) $(LDLIBS) -o $(OUTPUT)

clean: 
	rm -rf $(OUTPUT) *.o
