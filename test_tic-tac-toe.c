/*
** test_tic-tac-toe.c
**
** Unit testing for Tic-Tac-Toe
*/

#include <assert.h>

#include "tic-tac-toe.h"

void testall(void);
void test_set_move(void);
void test_is_invalid_move(void);
void test_update_GWD_flags(void);

int main(void)
{
    testall();    
}

void testall(void)
{
    test_set_move();
    test_is_invalid_move();
    test_update_GWD_flags();
}

void test_set_move(void)
{
    unsigned char board[3] = {};
    
    // Test invalid position '0'
    set_move(board, '0');
    assert(board[0] == 0b00000000 &&
           board[1] == 0b00000000 &&
          (board[2] & 0b00000011) == 0b00000000);

    // Test valid position as X (case 1,5,9)
    set_move(board, '1');
    assert((board[0] & 0b00000011) == 0b00000001);

    // Test valid position as O (case 1,5,9)
    board[2] ^= 0b00100000;
    set_move(board, '9');
    assert((board[2] & 0b00000011) == 0b00000010);

    // Test valid position (case 2,6)
    set_move(board, '6');
    assert((board[1] & 0b00001100) == 0b00001000);

    // Test valid position (case 3,7)
    set_move(board, '3');
    assert((board[0] & 0b00110000) == 0b00100000);

    // Test valid position (case 4,8)
    set_move(board, '8');
    assert((board[1] & 0b11000000) == 0b10000000);
}

void test_is_invalid_move(void)
{
    /*
    ** board
    **
    ** O| |X
    ** -+-+-
    **  | |O
    ** -+-+-
    ** O|X|O
    */
    const unsigned char board[3] = {0b00000010, 0b01101000, 0b00010010};
    bool test;    
    
    // Test invalid position '0'
    test = is_invalid_move(board, '0');
    assert(test);

    // Test valid position (case 1,5,9)
    test = is_invalid_move(board, '5');
    assert(!test);

    // Test invalid position (case 1,5,9)
    test = is_invalid_move(board, '9');
    assert(test);

    // Test valid position (case 2,6)
    test = is_invalid_move(board, '2');
    assert(!test);

    // Test invalid position (case 2,6)
    test = is_invalid_move(board, '6');
    assert(test);

    // Test valid position (case 3,7)
    test = is_invalid_move(board, '3');
    assert(!test);

    // Test invalid position (case 3,7)
    test = is_invalid_move(board, '7');
    assert(test);

    // Test valid position (case 4,8)
    test = is_invalid_move(board, '4');
    assert(!test);

    // Test invalid position (case 4,8)
    test = is_invalid_move(board, '8');
    assert(test);
}

void test_update_GWD_flags(void)
{
    unsigned char board[3] = {};

    // Test no win or draw
    update_GWD_flags(board);
    assert((board[2] & 0b00011100) == 0b00000000);

    // Test draw
    /*
    ** board
    **
    ** X|X|O
    ** -+-+-
    ** O|X|X
    ** -+-+-
    ** X|O|O
    */
    board[0] = 0b10100101;
    board[1] = 0b10010101;
    board[2] = 0b00000010;
    update_GWD_flags(board);
    assert((board[2] & 0b00010100) == 0b00010100);

    // Test X win 123
    board[0] = 0b00010101;
    board[1] = 0b00000000;
    board[2] = 0b00000000;
    update_GWD_flags(board);
    assert((board[2] & 0b00011000) == 0b00011000);

    // Test O win 147
    board[0] = 0b10000010;
    board[1] = 0b00100000;
    board[2] = 0b00000000;
    update_GWD_flags(board);
    assert((board[2] & 0b00011000) == 0b00010000);

    // Test X win 258
    board[0] = 0b00000100;
    board[1] = 0b01000001;
    board[2] = 0b00000000;
    update_GWD_flags(board);
    assert((board[2] & 0b00011000) == 0b00011000);

    // Test O win 357
    board[0] = 0b00100000;
    board[1] = 0b00100010;
    board[2] = 0b00000000;
    update_GWD_flags(board);
    assert((board[2] & 0b00011000) == 0b00010000);

    // Test X win 456
    board[0] = 0b01000000;
    board[1] = 0b00000101;
    board[2] = 0b00000000;
    update_GWD_flags(board);
    assert((board[2] & 0b00011000) == 0b00011000);

    // Test O win 159
    board[0] = 0b00000010;
    board[1] = 0b00000010;
    board[2] = 0b00000010;
    update_GWD_flags(board);
    assert((board[2] & 0b00011000) == 0b00010000);

    // Test X win 369
    board[0] = 0b00010000;
    board[1] = 0b00000100;
    board[2] = 0b00000001;
    update_GWD_flags(board);
    assert((board[2] & 0b00011000) == 0b00011000);

    // Test O win 789
    board[0] = 0b00000000;
    board[1] = 0b10100000;
    board[2] = 0b00000010;
    update_GWD_flags(board);
    assert((board[2] & 0b00011000) == 0b00010000);
}
