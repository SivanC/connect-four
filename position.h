#ifndef c4_position_h
#define c4_position_h

#include <stdint.h>

#define WIDTH 7
#define HEIGHT 6

typedef struct position {
	uint_fast64_t pos; // width * (height + 1) size bit mask containing one player's moves
	uint_fast64_t mask; // contains both players' moves, used with pos to get the position
	int width;
	int height;
} position;

/*
 * checks if a column can be played
 * column: 0-indexed column number from the left to play
 * position: position to play in
 */
int playable(int column, position *pos);

/*
 * plays a piece in the given column for the current player
 * column: 0-indexed column number from the left to play
 * position: position to play in
 */
void play(int column, position **pos);

/*
 * checks if a position has been won 
 * position: position to play in
 */
int check_win(position *pos);

/*
 * Checks if playing a move in a given column will win the game
 * column: the column to play the move in
 * position: the position to evaluate
 */
int check_will_win(int column, position *pos);

/*
 * checks the number of moves played so far
 * position: position to check
 */
int num_moves(position *pos);

/*
 * Generates the best order in which to check columns for good moves
 * Example output with width of 7: [3, 2, 4, 1, 5, 0, 6]
 * width: number of columns to arrange
 */
int * generate_column_order(int width);

uint_fast64_t top_mask();
uint_fast64_t bottom_mask();
#endif
