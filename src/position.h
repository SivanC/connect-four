#ifndef _position_h
#define _position_h

#include <stdint.h>

// struct used to store a board position
struct Position {
    uint_fast64_t cur_pos;
    uint_fast64_t mask;
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

int get_moves(struct Position *pos);

#endif
