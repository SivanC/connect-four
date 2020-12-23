//
// Created by sivancooperman on 12/22/20.
//

#ifndef CONNECT_FOUR_SORTER_H
#define CONNECT_FOUR_SORTER_H

#include "solver.h"

#include <stdint.h>

struct Sorter {
    struct {
        uint_fast64_t move;
        int score;
    } moves[BOARD_WIDTH];
    unsigned int size;
};

// construction
struct Sorter *Sorter_create(void);
void Sorter_destroy(struct Sorter *sorter);

// add and get
void add(struct Sorter *sorter, uint_fast64_t move, int score);
uint_fast64_t get_next(struct Sorter *sorter);

#endif //CONNECT_FOUR_SORTER_H
