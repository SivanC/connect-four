//
// Created by sivancooperman on 12/22/20.
//

#include "sorter.h"

#include <stdlib.h>

struct Sorter Sorter_create() {
    struct Sorter *sorter = malloc(sizeof(struct Sorter));
    sorter->size = BOARD_WIDTH;

    return sorter;
}

void Sorter_destroy(struct Sorter *sorter) {
    free(sorter);
}

void add(struct Sorter *sorter, uint_fast64_t move, int score) {
    int pos = sorter->size++;

    for (; pos && sorter->moves[pos - 1]->score > score; --pos) {
        sorter->moves[pos] = sorter->moves[pos - 1];
    }

    sorter->moves[pos]->move = move;
    sorter->moves[pos]->score = score;
}

uint_fast64_t get_next_move(struct Sorter *sorter) {
    if (size) {
        return sorter->moves[--size]->move;
    } else {
        return 0;
    }
}