options = -std=c23 --pedantic -Wall -Wextra -Werror -O3

tic-tac-toe : main.o tic-tac-toe.o
	gcc $(options) -o tic-tac-toe main.o tic-tac-toe.o

main.o : main.c tic-tac-toe.o tic-tac-toe.h
	gcc $(options) -c -o main.o main.c

tic-tac-toe.o : tic-tac-toe.c tic-tac-toe.h
	gcc $(options) -c -o tic-tac-toe.o tic-tac-toe.c

.PHONY : clean
clean :
	-rm tic-tac-toe main.o tic-tac-toe.o
