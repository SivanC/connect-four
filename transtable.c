#include <stdint.h>
#include <string.h>
#include "transtable.h"

unsigned int transtable_index(uint_fast64_t key, entry *table) {
	return key % (sizeof(*table) / sizeof(entry));
}

void transtable_put(uint_fast64_t key, uint_fast8_t val, entry **table) {
	unsigned int i = transtable_index(key, *table);
	(*table + i)->key = key;
	(*table + i)->val = val;
}

uint_fast8_t transtable_get(uint_fast64_t key, entry *table) {
	unsigned int i = transtable_index(key, table);
	if ((table + i)->key == key) {
		return (table + i)->val;
	} else {
		return 0;
	}
}

void transtable_clear(entry **table) {
	memset(*table, 0, sizeof(**table) * sizeof(entry));
}
