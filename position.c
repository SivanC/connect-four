#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "position.h"

int playable(int column, position *pos) {
	uint_fast64_t mask = 1 << (HEIGHT - 1) + (HEIGHT + 1) * column;
	return pos->pos & mask;
}

void play(int column, position **pos) {
	if (!playable(column, *pos)) {
		return;
	}
	
	uint_fast64_t column_mask = 1 << (HEIGHT + 1) * column;
	(*pos)->pos ^= (*pos)->mask;
	(*pos)->mask |= (*pos)->mask + column_mask;
}

int check_win(position *pos) {
	uint_fast64_t m = pos->pos & (pos->pos << HEIGHT + 1);
	int win = 0;

	// horizontal
	win += m & (m >> (2 * (HEIGHT + 1)));

	// diagonal
	m = pos->pos & (pos->pos >> HEIGHT);
	win += m & (m >> (2 * HEIGHT));

	// other diagonal
	m = pos->pos & (pos->pos >> (HEIGHT + 2));
	win += m & (m >> (2 * (HEIGHT + 2)));

	// vertical
	m = pos->pos & (pos->pos >> 1);
	win += m & (m >> 2);

	return win;
}

int check_will_win(int column, position *pos) {
	play(column, &pos);
	return check_win(pos);
}

int get_moves(position *pos) {
	int count = 0;
	while(pos->mask) {
		count += pos->mask & 1;
		count >>= 1;
	}
	
	return count;
}

int * generate_column_order(int width) {
	int order[width];
	int *arr = order;
		
	int tracker = width/2;
	int i;
	for (i = 0; i < width; i++) {
		*(arr + i) = tracker += i * pow(-1, i), tracker; 
	}

	return arr;
}

uint_fast64_t top_mask() {
	uint_fast64_t mask = 1 << HEIGHT - 1;
	int i;
	for (i = 1; i < WIDTH; i++) {
		mask += 1 << (HEIGHT - 1) + (HEIGHT + 1) * i;
	}

	return mask;
}

uint_fast64_t bottom_mask() {
	uint_fast64_t mask = 1;
	int i;
	for (i = 1; i < WIDTH; i++) {
		mask += 1 << (HEIGHT + 1)*i;
	}

	return mask;
}
