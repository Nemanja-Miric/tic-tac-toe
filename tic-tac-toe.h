#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BINARY_LEN (128)

#define IS_DRAW_CPY ((bool)(board_cpy[2] & 0x04))
#define IS_X_WINNER_CPY ((bool)(board_cpy[2] & 0x08))
#define IS_GAME_OVER_CPY ((bool)(board_cpy[2] & 0x10))
#define IS_O_TURN_CPY ((bool)(board_cpy[2] & 0x20))
#define IS_X_CPY ((bool)(board_cpy[2] & 0x40))

#define IS_DRAW ((bool)(board[2] & 0x04))
#define IS_X_WINNER ((bool)(board[2] & 0x08))
#define IS_GAME_OVER ((bool)(board[2] & 0x10))
#define IS_O_TURN ((bool)(board[2] & 0x20))
#define IS_X ((bool)(board[2] & 0x40))
#define IS_COMPUTER ((bool)(board[2] & 0x80))

short int best_move(const unsigned char[restrict 3]);

void update_GWD_flags(unsigned char[restrict 3]);

bool is_invalid_move(const unsigned char[restrict 3], const char);
void set_move(unsigned char[restrict 3], const char);

void display_help(const char *restrict);
void display_board(const unsigned char[restrict 3]);

#endif
