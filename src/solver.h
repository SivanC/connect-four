#ifndef _solver_h
#define _solver_h_

int negamax(struct Position *pos, int alpha, int beta, int column_order[]);

extern int BOARD_WIDTH;
extern int BOARD_HEIGHT;

#endif
