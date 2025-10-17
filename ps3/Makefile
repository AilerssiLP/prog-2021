CC=gcc
CFLAGS=-std=c11 -Wall -Werror
LDLIBS=-lm
OUTPUT=game

all: $(OUTPUT)

$(OUTPUT): k.o hof.o ui.o main.o
	cppcheck --enable=performance,unusedFunction --error-exitcode=1 *.c
	gcc $(CFLAGS) k.o hof.o ui.o main.o $(LDLIBS) -o $(OUTPUT)

main.o: main.c
	gcc $(CFLAGS) -c main.c -o main.o
k.o: k.c k.h
	gcc $(CFLAGS) -c k.c -o k.o
hof.o: hof.c hof.h
	gcc $(CFLAGS) -c hof.c -o hof.o
ui.o: ui.c ui.h
	gcc $(CFLAGS) -c ui.c -o ui.o
clean:
	rm -rf $(OUTPUT) *.o