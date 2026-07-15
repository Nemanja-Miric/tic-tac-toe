/*
** main.c
**
** Usage: <bin> [[-c, --computer {O|X|o|x}] [-p, --player {O|X|o|x}] [-h, --help]]
**
** Tic Tac Toe game for the terminal against a friend, or the computer
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BINARY_LEN 128

void display_help(char * restrict);

void init_board(unsigned char ** restrict);
void free_board(unsigned char ** restrict);

int main(int argc, char *argv[])
{
    /*
    ** Flags:
    **
    ** Is(C)omputer, Is(X)
    **
    ** 00CX0000
    */
    unsigned char flags = 0x0;

    if (argc == 3) {
        if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--computer") == 0)
            flags |= 0x20; // Set C Flag
        else if (strcmp(argv[1], "-p") != 0 && strcmp(argv[1], "--player") != 0)
            goto help;

        if (strcmp(argv[2], "X") == 0 || strcmp(argv[2], "x") == 0)
            flags |= 0x10; // Set X Flag
        else if (strcmp(argv[2], "O") != 0 && strcmp(argv[2], "o") != 0)
            goto help;
    } else {
help:
        display_help(argv[0]);
        return 0;
    }

    unsigned char *board;

    init_board(&board);

    free_board(&board);
}

void display_help(char * restrict bin_name)
{
    size_t binary_len;
    for (binary_len = 0; binary_len < MAX_BINARY_LEN && bin_name[binary_len] != '\0'; binary_len++);
    if (binary_len == MAX_BINARY_LEN) {
        (void)fputs("ERROR:display_help:Length of binary path is over the limit\n", stderr);
        exit(1);
    }

    (void)printf("Usage: %.128s [[-c, --computer={O|X|o|x}] [-p, --player={O|X|o|x}] [-h, --help]]\n", bin_name);
}

void init_board(unsigned char ** restrict board)
{
    if ((*board = calloc(3, sizeof(unsigned char))) == nullptr) {
        (void)fputs("ERROR:init_board: Failed to initialize board\n", stderr);
        exit(2);
    }
}

void free_board(unsigned char ** restrict board)
{
    free(*board);
}
