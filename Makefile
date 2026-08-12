SHELL = /bin/sh
CFLAGS = -std=c2x -pedantic-errors -Wall -Wextra -Wconversion -Wsign-conversion -Wformat=2 -Wstrict-prototypes -Wold-style-definition -Wshadow -Wundef -Wwrite-strings -O3

.SUFFIXES = .c .h .o
.PHONY = all build test bin obj clean cleanbin cleanobj

all : build test

build : bin bin/tic-tac-toe

test : bin bin/test_tic-tac-toe
	bin/test_tic-tac-toe

bin/tic-tac-toe : bin obj obj/main.o obj/tic-tac-toe.o tic-tac-toe.h
	gcc $(CFLAGS) -o $@ obj/main.o obj/tic-tac-toe.o

bin/test_tic-tac-toe : bin obj obj/test_tic-tac-toe.o obj/tic-tac-toe.o tic-tac-toe.h
	gcc $(CFLAGS) -o $@ obj/test_tic-tac-toe.o obj/tic-tac-toe.o

obj/test_tic-tac-toe.o : obj test_tic-tac-toe.c tic-tac-toe.h
	gcc $(CFLAGS) -c -o $@ test_tic-tac-toe.c

obj/main.o : obj main.c tic-tac-toe.h
	gcc $(CFLAGS) -c -o $@ main.c

obj/tic-tac-toe.o : obj tic-tac-toe.c tic-tac-toe.h
	gcc $(CFLAGS) -c -o $@ tic-tac-toe.c

bin :
	mkdir bin

obj :
	mkdir obj

clean : cleanbin cleanobj

cleanbin :
	rm -r bin

cleanobj :
	rm -r obj
