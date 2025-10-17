CC=gcc
CFLAGS=-std=c11 -Wall -Werror -g
LDLIBS=-lm
OUTPUT=ps1


all: bmp playfair main.c
	$(CC) $(CFLAGS) bmp.o playfair.o main.c $(LDLIBS) -o $(OUTPUT) 
	
bmp: bmp.c bmp.h
	$(CC) $(CFLAGS) -c bmp.c
	
playfair: playfair.c playfair.h
	$(CC) $(CFLAGS) -c playfair.c
		
clean:
	rm -rf playfair.o bmp.o playfair bmp ps1

