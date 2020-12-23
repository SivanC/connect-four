#include "position.h"
#include "solver.h"
#include "sorter.h"

#include "../lib/dbg.h"
#include "../lib/bstrlib.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int BOARD_WIDTH = 7;
int BOARD_HEIGHT = 6;

int gen_order() {
    int column_order[BOARD_WIDTH];
    for (int i = 0; i < BOARD_WIDTH; i++) {
        column_order[i] = BOARD_WIDTH / 2 + (1 - 2 * (i % 2)) * (i + 1) / 2;
    }

    return 0;
}

/**
 * Solves a connect 4 board position. First, the function checks if the game is
 * a draw; if not, it checks if any of the next moves are winning moves, and if
 * they are not, recursively checks each of those moves for a win, and so on.
 *
 * @param pos A Position struct containing the board position to be analyzed
 * in the form of a mask + the current player's pieces' bitboard.
 * @param alpha The lower bound of the score window. Window [alpha:beta] can be set to
 * [-inf:inf] in order to find an actual score, or [-1:1] to provide only
 * win/loss/draw information.
 * @param beta The upper bound of the score window. See alpha for suggested usage.
 * @param column_order Because C can be...frustrating and I don't quite know how
 * else to give the function this array, negamax() takes an array of size BOARD_WIDTH
 * that tells it what order to check the moves in.
 *
 * @return The score of the current move for the player. A positive score means
 * the current player will win with his nth to last stone, and negative score
 * means the opponent will win with their nth to last stone.
 */
int negamax(struct Position *pos, int alpha, int beta, int column_order[]) {
    int i = 0;

    uint_fast64_t next = opponent_winning_positions(pos) & UINT64_C(0);

    // check for draw
    if (get_moves(pos) == BOARD_HEIGHT * BOARD_WIDTH ) return 0;

    // otherwise, initiate best score as taking half the remaining moves in the
    // game (aka the rest of the current player's stones).
    int max = (BOARD_WIDTH * BOARD_HEIGHT - get_moves(pos) - 1)/2;

    // our upper bound has no reason to be bigger than our max score
    if (beta > max) {
        beta = max;
        // If our score window is empty no need to continue
        if (alpha >= beta) return beta;
    }

    struct Sorter *sorter = Sorter_create();
    for (i = 0; i < BOARD_WIDTH; i++) {
        if (uint_fast64_t move = next & column_mask(column_order[i])) {
            add(sorter, move, score_move(move));
        }
    }

    // get scores of all next moves and adjust score window
    while(uint_fast64_t next = get_next(sorter->moves)) {
        struct Position *next_pos = Position_create_from_pos(pos);
        play(next);

        int score = -negamax(next_pos, -alpha, -beta, column_order);

        // If the score we find is better than our upper bound we should return it
        if (score >= beta) return score;
        // Else if we find something better than our lower bound we should adjust our lower bound.
        if (score > alpha) alpha = score;
    }

    return alpha;
}

int solve(struct Position *pos, int weak = 0) {

    if (winning_positions(pos) != 0) {
        return (BOARD_WIDTH * BOARD_HEIGHT + 1 - get_moves(pos)) / 2;
    }

    int min = -(BOARD_WIDTH * BOARD_HEIGHT - get_moves(pos)) / 2;
    int max = (BOARD_WIDTH * BOARD_HEIGHT + 1 - get_moves(pos)) / 2;

    if (weak) {
        min = -1;
        max = 1;
    }

    while (min < max) {
        int mid = min + (max - min) / 2;
        if (mid <= 0 && min/2 < mid) {
            mid = min / 2;
        } else if (mid >= 0 && max/2 > mid) {
            mid = max / 2;
        }

        int r = negamax(pos, mid, mid + 1);

        if (r <= mid) {
            max = r;
        } else {
            min = r;
        }
    }

    return min;
}