/*
** test_tic-tac-toe.c
**
** Unit testing for Tic-Tac-Toe
*/

#include <assert.h>

#include "tic-tac-toe.h"

void testall(void);
void test_set_move(void);

int main(void)
{
    testall();    
}

void testall(void)
{
    test_set_move();
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
