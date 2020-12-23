#ifndef _position_h
#define _position_h

#include "solver.h"

#include <stdint.h>

uint_fast64_t bottom;
uint_fast64_t board_mask;

// struct used to store a board position
struct Position {
    uint_fast64_t cur_pos: BOARD_WIDTH * BOARD_HEIGHT;
    uint_fast64_t mask: BOARD_WIDTH * BOARD_HEIGHT;
    int moves;
};

// returns masks used in calculations
uint_fast64_t top_mask(int col);
uint_fast64_t bottom_mask(int col);
uint_fast64_t column_mask(int col);

// buildup and teardown of Position structs
struct Position *Position_create(void);
struct Position *Position_create_from_pos(struct Position *pos);
struct Position *Position_create_from_str(const char *posstr);
int Position_destroy(struct Position *pos);

// functions that take/return a board position
int play(int col, struct Position *pos);
int can_play(int col, uint_fast64_t mask);
int will_win(int col, struct Position *pos);
int check_win(uint_fast64_t pos);
int score_move(uint_fast64_t move);

// functions that return masks and take board positions
uint_fast64_t possible_mask(struct Position *pos);
uint_fast64_t winning_positions(struct Position *pos);
uint_fast64_t opponent_winning_positions(struct Position *pos);
uint_fast64_t non_losing_positions(struct Position *pos);

// misc functions
int get_moves(struct Position *pos);
unsigned int count(uint_fast64_t n);

#endif
