#ifndef c4_solver_h
#define c4_solver_h

#include "position.h"

/*
 * Uses the Negamax variant of a min-max scoring algorithm 
 * to assign a score to a position.
 * position: a position to be scored
 */
int negamax(position *pos, int alpha, int beta);

#endif
