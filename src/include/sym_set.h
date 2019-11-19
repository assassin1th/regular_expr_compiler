#ifndef SYM_SET_H_
#define SYM_SET_H_

#include <stdint.h>

#include "attr.h"

/*
 * Symbol set structure
 * 4 uint64_t numbers, whose bits specify presence of a symbol
 */
typedef struct
{
	uint64_t sym_bits[4];
} sym_set_t;

/*
 * Funcition create empty set
 */
sym_set_t *new_sym_set ();

/*
 * Funciton free mem from set
 */
void free_sym_set (sym_set_t *__sym_set) _fastcall;

/*
 * Fucntion add symbol
 */
inline void add_sym (sym_set_t *__sym_set, uint8_t __sym) _inline
{
	__sym_set->sym_bits[__sym >> 6] |= ((uint64_t) 1 << (__sym & 0x3F));
}

/*
 * Funcion for check symbol in set
 * 0 - not found, 1 - exists
 */
inline uint64_t check_sym (sym_set_t *__sym_set, uint8_t __sym) _inline
{
	return __sym_set->sym_bits[__sym >> 6] & ((uint64_t) 1 << (__sym & 0x3F));
}

#endif // SYM_SET_H_
