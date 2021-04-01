#ifndef c4_transtable_h
#define c4_transtable_h

#include <stdint.h>

typedef struct entry {
	uint_fast64_t key;
	uint_fast8_t val;
} entry;

/*
 * Assigns an index to a key-value pair through a simple modulus hash.
 * key: key to hash
 * table: table to hash with
 */
unsigned int transtable_index(uint_fast64_t key, entry *table);

/*
 * Stores an 8-bit value for agiven 56-bit key
 * key: 56-bit key
 * value: 8-bit non-null value
 * table: table to insert into
 */
void transtable_put(uint_fast64_t key, uint_fast8_t val, entry **table);

/*
 * Gets an 8-bit value with a 56-bit key
 * key: 56-bit key
 * table: table to get from
 * return: value if present, otherwise 0
 */
uint_fast8_t transtable_get(uint_fast64_t key, entry *table);

/*
 * Fills the table with zeroes
 * table: table to erase
 */
void transtable_clear(entry **table);

#endif
