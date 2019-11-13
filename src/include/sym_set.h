#ifndef SYM_SET_H_
#define SYM_SET_H_

#include <stdint.h>

/*
 * Inline attribute for set interfaces
 */
#ifndef _inline
#define _inline __attribute__ ((always_inline))
#endif // _inline

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
void free_sym_set (sym_set_t *__sym_set);

/*
 * Fucntion add symbol
 */
inline _inline void add_symbol (sym_set_t *__sym_set, char __sym);

/*
 * Funcion for check symbol in set
 * 0 - not found, 1 - exists
 */
inline _inline int check_symbol (sym_set_t *__sym_set, char __sym);

#endif // SYM_SET_H_
