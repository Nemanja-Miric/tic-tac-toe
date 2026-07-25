#include "tic-tac-toe.h"

short int best_move(const unsigned char board[restrict 3])
{
    /*
    ** eval
    **
    ** (B)est(M)ove, (B)est(E)val
    **
    ** BM BE
    */
    unsigned char board_cpy[3];
    board_cpy[2] = board[2];

    short int eval = (IS_X_CPY != IS_O_TURN_CPY) ? 0x0000 : 0x0004;
    short int temp_eval;

    for (char move = '1'; move <= '9'; move++) {
        (void)memcpy(board_cpy, board, 3);

        if (!is_invalid_move(board_cpy, move))
            set_move(board_cpy, move);
        else
            continue;

        update_GWD_flags(board_cpy);

        if (IS_GAME_OVER_CPY) {
            if (IS_DRAW_CPY) {
                if ((IS_X_CPY != IS_O_TURN_CPY) ? (eval & 0x00ff) < 2 : (eval & 0x00ff) > 2) {                                      // If best move is a draw
                    eval = move;
                    eval <<= 8;
                    eval |= 2;
                }
            } else if (IS_X_WINNER_CPY == IS_X_CPY && ((IS_X_CPY != IS_O_TURN_CPY) ? true : (eval & 0x00ff) > 3)) {                 // If best move is a win
                eval = move;
                eval <<= 8;
                eval |= 3;
            } else if (IS_X_WINNER_CPY != IS_X_CPY && ((IS_X_CPY != IS_O_TURN_CPY) ? (eval & 0x00ff) < 1 : true)) {                 // If best move is a loss
                eval = move;
                eval <<= 8;
                eval |= 1;
            } 
        } else {
            board_cpy[2] ^= 0x20; // Flip copy's O Flag

            temp_eval = best_move(board_cpy);

            board_cpy[2] ^= 0x20; // Unflip copy's O Flag

            if ((IS_X_CPY != IS_O_TURN_CPY) ? (eval & 0x00ff) < (temp_eval & 0x00ff) : (eval & 0x00ff) > (temp_eval & 0x00ff)) {    // If temp_eval is more optimal
                eval = move;
                eval <<= 8;
                eval |= (temp_eval & 0x00ff);
            }
        }

        if ((IS_X_CPY != IS_O_TURN_CPY) ? (eval & 0x00ff) == 3 : (eval & 0x00ff) == 1)                                              // If eval is optimal
            return eval;
    }
    return eval;
}

void update_GWD_flags(unsigned char board[restrict 3])
{
    // Xs
    if ((board[0] & 0x3f) == 0b00010101 ||                                                                              // 123
       ((board[0] & 0xc3) == 0b01000001 && (board[1] & 0x30) == 0b00010000) ||                                          // 147
       ((board[0] & 0x0c) == 0b00000100 && (board[1] & 0xc3) == 0b01000001) ||                                          // 258
       ((board[0] & 0x30) == 0b00010000 && (board[1] & 0x33) == 0b00010001) ||                                          // 357
       ((board[0] & 0xc0) == 0b01000000 && (board[1] & 0x0f) == 0b00000101) ||                                          // 456
     ((((board[0] & 0x03) == 0b00000001 && (board[1] & 0x03) == 0b00000001) ||                                          // 159
       ((board[0] & 0x30) == 0b00010000 && (board[1] & 0x0c) == 0b00000100) ||                                          // 369
                                           (board[1] & 0xf0) == 0b01010000) && (board[2] & 0x03) == 0b00000001))        // 789
        board[2] |= 0x18; // Set G and W Flags
    // Os
    else if ((board[0] & 0x3f) == 0b00101010 ||                                                                         // 123
            ((board[0] & 0xc3) == 0b10000010 && (board[1] & 0x30) == 0b00100000) ||                                     // 147
            ((board[0] & 0x0c) == 0b00001000 && (board[1] & 0xc3) == 0b10000010) ||                                     // 258
            ((board[0] & 0x30) == 0b00100000 && (board[1] & 0x33) == 0b00100010) ||                                     // 357
            ((board[0] & 0xc0) == 0b10000000 && (board[1] & 0x0f) == 0b00001010) ||                                     // 456
          ((((board[0] & 0x03) == 0b00000010 && (board[1] & 0x03) == 0b00000010) ||                                     // 159
            ((board[0] & 0x30) == 0b00100000 && (board[1] & 0x0c) == 0b00001000) ||                                     // 369
                                                (board[1] & 0xf0) == 0b10100000) && (board[2] & 0x03) == 0b00000010))   // 789
        board[2] |= 0x10; // Set G Flag
    // Draw
    else {
        for (size_t i = 0; i < 2; i++)
            if (!(board[i] & 0x03) || !(board[i] & 0x0c) || !(board[i] & 0x30) || !(board[i] & 0xc0))
                return;
        
        if (board[2] & 0x03)                                                                                            // Draw
            board[2] |= 0x14; // Set G and D Flags
    }
}

bool is_invalid_move(const unsigned char board[restrict 3], const char position)
{
    switch (position) {
        case '1':
        case '5':
        case '9':
            return board[(position - '1') / 4] & 0x03;
        case '2':
        case '6':
            return board[(position - '1') / 4] & 0x0c;
        case '3':
        case '7':
            return board[(position - '1') / 4] & 0x30;
        case '4':
        case '8':
            return board[(position - '1') / 4] & 0xc0;
        default:
            return true;
    }
}

void set_move(unsigned char board[restrict 3], const char position)
{
    switch (position) {
        case '1':
        case '5':
        case '9':
            board[(position - '1') / 4] |= (IS_O_TURN ? 0x02 : 0x01);
            break;
        case '2':
        case '6':
            board[(position - '1') / 4] |= (IS_O_TURN ? 0x08 : 0x04);
            break;
        case '3':
        case '7':
            board[(position - '1') / 4] |= (IS_O_TURN ? 0x20 : 0x10);
            break;
        case '4':
        case '8':
            board[(position - '1') / 4] |= (IS_O_TURN ? 0x80 : 0x40);
     }
}

void display_help(const char *restrict bin_name)
{
    size_t binary_len;
    for (binary_len = 0; binary_len < MAX_BINARY_LEN && bin_name[binary_len] != '\0'; binary_len++);
    if (binary_len == MAX_BINARY_LEN) {
        (void)fputs("ERROR:display_help:Length of binary path is over the limit\n", stderr);
        exit(EXIT_FAILURE);
    }

    (void)printf("Usage: %.128s [[-c, --computer={O|X|o|x}] [-p, --player={O|X|o|x}] [-h, --help]]\n", bin_name);
}

void display_board(const unsigned char board[restrict 3])
{
    unsigned char board_cpy[3] = {};

    (void)memcpy(board_cpy, board, 3);

    for (size_t i = 0; i < 9; i++) {
        switch (board_cpy[i / 4] & 0x03) {
            case 0:
                (void)putchar(' ');
                break;
            case 1:
                (void)putchar('X');
                break;
            case 2:
                (void)putchar('O');
        }

        board_cpy[i / 4] >>= 2;      

        switch (i) {
            case 2:
            case 5:
                (void)puts("\n-+-+-");  // Horizontal separator
                break;
            case 8:
                (void)putchar('\n');    // End
                break;
            default:
                (void)putchar('|');     // Vertical separator
        }
    }
}

