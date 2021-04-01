#include <stdlib.h>
#include "position.h"
#include "solver.h"

int negamax(position *pos, int alpha, int beta, entry **table) {
	if (num_moves(pos) == WIDTH * HEIGHT) {
		return 0;
	}

	int *order = generate_column_order(WIDTH);

	int i;
	for (i = 0; i < WIDTH; i++) {
		if (playable(*(order + i), pos) && check_will_win(*(order + i), pos)) {
			return (WIDTH + HEIGHT+1 - num_moves(pos)) / 2;
		}
	}

	int max_score = (WIDTH * HEIGHT - 1 - num_moves(pos)) / 2;

	int val = transtable_get(pos->key, *table);
	if (val) {
		max_score = val + MIN;
	}

	if (beta > max_score) {
		beta = max_score;
		if (alpha >= beta) {
			return beta;
		}
	}

	for (i = 0; i < WIDTH; i++) {
		if (playable(*(order + i), pos)) {
			position *t = malloc(sizeof(position));
			t->pos = pos->pos;
			t->mask = pos->mask;
			t->height = HEIGHT;
			t->width = WIDTH;

			play(*(order + i), &t);
			int score = -negamax(t, -beta, -alpha);

			if (score >= beta) {
				return score;
			}
			if (score > alpha) {
				alpha = score;
			}

			free(t);
		}
	}

	transtable_put(pos->key, alpha - MIN + 1, table);
	return alpha;
}
