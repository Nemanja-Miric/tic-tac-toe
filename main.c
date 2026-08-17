/*
** main.c
**
** Usage: <bin> [[-c, --computer {O|X|o|x}] [-p, --player {O|X|o|x}] [-h, --help]]
**
** Tic Tac Toe game for the terminal against a friend, or the computer
*/

#include "tic-tac-toe.h"

int main(int argc, char *argv[])
{
    /*
    ** Flags:
    **
    ** Is(C)omputer, Is(X), Is(O)Turn, Is(G)ameOver, IsX(W)inner, Is(D)raw
    **
    ** CXOGWD--
    */
    unsigned char board[3] = {}; // Set O, G, and D Flags
    char move;

    if (argc == 3) {
        if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "--computer") == 0)
            board[2] |= 0b10000000; // Set C Flag
        else if (strcmp(argv[1], "-p") != 0 && strcmp(argv[1], "--player") != 0)
            goto help;

        if (strcmp(argv[2], "X") == 0 || strcmp(argv[2], "x") == 0)
            board[2] |= 0b01000000; // Set X Flag
        else if (strcmp(argv[2], "O") != 0 && strcmp(argv[2], "o") != 0)
            goto help;
    } else {
help:
        if (argv[0][0] == '\0')
            display_help("<UNKNOWN>");
        else
            display_help(argv[0]);

        return EXIT_SUCCESS;
    }

    while (!IS_GAME_OVER) {
        display_board(board);
        (void)puts("");

        if (IS_X != IS_O_TURN) {
            if (IS_COMPUTER) {      // Computer's turn
                move = (char)(best_move(board) >> 8);
                (void)puts("Computer's turn");
                (void)printf("%c%c\n\n", IS_X ? 'X' : 'O', move);
                
                set_move(board, move);
            } else {                // Friend's turn
                while (true) {
                    (void)puts("Guest's turn");
                    (void)putchar(IS_X ? 'X' : 'O');
                    (void)fflush(stdout);
                    move = (char)getchar();
                    while (getchar() != '\n');
                    
                    if (is_invalid_move(board, move)) {
                        (void)puts("Invalid move, try again...\n");
                        continue;
                    }

                    (void)puts("");
                    break;
                }
            
                set_move(board, move);
            }
        } else {                    // Your turn
            while (true) {
                (void)puts("Host's turn");
                (void)putchar(IS_X ? 'O' : 'X');
                (void)fflush(stdout);
                move = (char)getchar();
                while (getchar() != '\n');

                if (is_invalid_move(board, move)) {
                    (void)puts("Invalid move, try again...\n");
                    continue;
                }

                (void)puts("");
                break;
            }

            set_move(board, move);
        }
        
        board[2] ^= 0b00100000; // Flip O Flag

        update_GWD_flags(board);
    }

    display_board(board);

    if (IS_DRAW)
        (void)puts("\nIt's a draw!");
    else
        (void)printf("\n'%c' won!\n", (IS_X_WINNER ? 'X' : 'O'));
}

