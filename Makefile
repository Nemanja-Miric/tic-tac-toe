SHELL = /bin/sh
CFLAGS = -std=c23 -pedantic-errors -Wall -Wextra -Wconversion -Wsign-conversion -Wformat=2 -O3

.SUFFIXES = .c .h .o
.PHONY = all build test cleanall cleanbin cleanobj

all : build test

build : bin/tic-tac-toe

test : bin/test_tic-tac-toe
	bin/test_tic-tac-toe

bin/tic-tac-toe : obj/main.o obj/tic-tac-toe.o tic-tac-toe.h
	gcc $(CFLAGS) -o $@ obj/main.o obj/tic-tac-toe.o

bin/test_tic-tac-toe : obj/test_tic-tac-toe.o obj/tic-tac-toe.o tic-tac-toe.h
	gcc $(CFLAGS) -o $@ obj/test_tic-tac-toe.o obj/tic-tac-toe.o

obj/test_tic-tac-toe.o : test_tic-tac-toe.c tic-tac-toe.h
	gcc $(CFLAGS) -c -o $@ test_tic-tac-toe.c

obj/main.o : main.c tic-tac-toe.h
	gcc $(CFLAGS) -c -o $@ main.c

obj/tic-tac-toe.o : tic-tac-toe.c tic-tac-toe.h
	gcc $(CFLAGS) -c -o $@ tic-tac-toe.c

cleanall : cleanbin cleanobj

cleanbin :
	rm bin/*

cleanobj :
	rm obj/*
