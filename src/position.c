#include "position.h"
#include "solver.h"

#include "../lib/dbg.h"
#include "../lib/bstrlib.h"

#include <stdlib.h>
#include <stdint.h>

/**
 * Creates a bitmask with a 1 in the top cell of a column.
 * @param col The column to place the 1 in, from 0 to BOARD_WIDTH - 1
 * @return A bitmask with a 1 in the top cell of a column.
 */
uint_fast64_t top_mask(int col) {
    check(0 <= col && col <= (BOARD_WIDTH - 1), "Column is invalid!");

    return UINT64_C(1) << ((BOARD_HEIGHT - 1) + (BOARD_HEIGHT + 1) * col);

error:
    return 0;
}

/**
 * Creates a bitmask with a 1 in the bottom cell of a column.
 * @param col The column to place the 1 in, from 0 to BOARD_WIDTH - 1
 * @return A bitmask with a 1 in the bottom cell of a column.
 */
uint_fast64_t bottom_mask(int col) {
    check(0 <= col && col <= (BOARD_WIDTH - 1), "Column is invalid!");

    return UINT64_C(1) << (BOARD_HEIGHT + 1) * col;

error:
    return 0;
}

/**
 * Creates an empty Position struct.
 * @return An empty Position struct, or NULL if there is a memory error.
 */
struct Position *Position_create() {
    struct Position *pos = malloc(sizeof(struct Position));
    check_mem(pos);

    pos->cur_pos = 0;
    pos->mask = 0;
    pos->moves = 0;

    return pos;

error:
    return NULL;
}

/**
 * Creates a Position struct from another, useful for analyzing related or
 * hypothetical positions.
 * @param pos A Position struct to copy from.
 * @return A Position struct identical to the input, or NULL if there is
 * a memory error.
 */
struct Position *Position_create_from_pos(struct Position *pos) {
    struct Position *new_pos = Position_create();
    check_mem(new_pos);

    new_pos->cur_pos = pos->cur_pos;
    new_pos->mask = pos->mask;
    new_pos->moves = pos->moves;

    return new_pos;

error:
    return NULL;
}

/**
 * Creates a Position struct based on a position string. Position strings are valid
 * IF AND ONLY IF:
 *
 * They contain characters less than or equal to the size of the
 * board (on a standard 7x6 board, no more than 42 characters),
 *
 * They contain only non-negative integers less than the number of columns
 * the board contains.
 *
 * @param posstr A position string containing the position to give the struct.
 * @return A Position struct with the input position (cur_pos + mask), and the
 * correct number of moves. NULL if there is a memory error.
 */
struct Position *Position_create_from_str(const char *posstr) {
    struct Position *pos = Position_create();
    check_mem(pos);

    const bstring posbstr = bfromcstr(posstr);
    check_mem(posbstr);

    int i = 0;

    for (i = 0; i < blength(posbstr); i++) {
        char col = bchar(posbstr, i);
        if (isdigit(col)) {
            if (0 <= col && col <= BOARD_WIDTH - 1) {
                play(col, pos);
            } else {
                log_err("ERROR: Digit at position string index %d is not between 0 and %d",
                        i, BOARD_WIDTH);
            }
        } else {
            log_err("ERROR: Character at position string index %d is not a digit!", i);
        }
    }

    free(posbstr);

    return pos;

error:
    return NULL;
}

/**
 * Frees a Position from memory.
 * @param pos The Position struct to free from memory.
 * @return 0 on success, 1 if the Position does not exist.
 */
int Position_destroy(struct Position *pos) {
    check_mem(pos);

    free(pos);

    return 0;

error:
    return 1;
}

/**
 * Plays a stone into a column of a position.
 * @param col The 0-indexed column to play the stone in.
 * @param pos The Position struct to play in.
 * @return 0 on success.
 */
int play(int col, struct Position *pos) {
    // Flip to opposing player's position
    pos->cur_pos ^= pos->mask;
    pos->mask |= pos->mask + bottom_mask(col);
    pos->moves++;

    return 0;
}

/**
 * Checks if a column is playable on a given position.
 * @param col The 0-indexed column to check.
 * @param mask The bitmask to check against.
 * @return 1 if the column is playable, 0 otherwise.
 */
int can_play(int col, uint_fast64_t mask) {
    return (mask & top_mask(col)) == 0;
}

/**
 * Checks if the next move in a column will win.
 * @param col The 0-indexed column to check.
 * @param pos The Position struct to check.
 * @return 1 if the move will win, 0 if it will not, -1 on error.
 */
int will_win(int col, struct Position *pos) {
    // Create a new position and simulate the play there,
    // then check for a win and return
    struct Position *test = Position_create_from_pos(pos);
    check_mem(test);

    play(col, test);

    int win = check_win(test->cur_pos);

    Position_destroy(test);

    return win;

error:
    return -1;
}

/**
 * Checks if a position contains a winning series of stones.
 * @param cur_pos The position to check.
 * @return 1 if the position contains a win for the player passed in,
 * 0 if not.
 */
int check_win(uint_fast64_t cur_pos) {
    // horizontal
    uint_fast64_t a = cur_pos & (cur_pos >> (BOARD_HEIGHT + 1));
    if (a & (a >> (2 * (BOARD_HEIGHT + 1)))) return 1;

    // vertical
    a = cur_pos & (cur_pos >> 1);
    if (a & (a >> 2)) return 1;

    // top-left to bottom-right
    a = cur_pos & (cur_pos >> BOARD_HEIGHT);
    if (a & (a >> (2 * BOARD_HEIGHT))) return 1;

    // bottom-left to top-right
    a = cur_pos & (cur_pos >> (BOARD_HEIGHT + 2));
    if (a & (a >> (2 * (BOARD_HEIGHT + 2)))) return 1;

    return 0;
}

int get_moves(struct Position *pos) {
    return pos->moves;
}