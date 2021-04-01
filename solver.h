#ifndef c4_solver_h
#define c4_solver_h

#include "position.h"
#include "transtable.h"

/*
 * Uses the Negamax variant of a min-max scoring algorithm 
 * to assign a score to a position.
 * position: a position to be scored
 * alpha: lower score bound, -1 for weak solve, -inf for strong solve
 * beta: upper score bound, 1 for weak solve, inf for strong solve
 * table: a transposition table that stores position keys
 */
int negamax(position *pos, int alpha, int beta, entry **table);

#endif
