#include <stdlib.h>
#include "position.h"
#include "solver.h"

int negamax(position *pos) {
	if (num_moves(pos) == WIDTH * HEIGHT) {
		return 0;
	}

	int i;
	for (i = 0; i < WIDTH; i++) {
		if (playable(i, pos) && check_will_win(i, pos)) {
			return (WIDTH + HEIGHT+1 - num_moves(pos)) / 2;
		}
	}

	int max_score = -1 * (WIDTH * HEIGHT);

	for (i = 0; i < WIDTH; i++) {
		if (playable(i, pos)) {
			position *t = malloc(sizeof(position));
			t->pos = pos->pos;
			t->mask = pos->mask;
			t->height = HEIGHT;
			t->width = WIDTH;

			play(i, &t);
			int score = -1 * negamax(t);

			max_score = score > max_score ? score : max_score;

			free(t);
		}
	}

	return max_score;
}
