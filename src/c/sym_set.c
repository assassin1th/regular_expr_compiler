#include <stdlib.h>
#include "sym_set.h"

/*
 * Create empty symbol set (all bits set to 0)
 */
sym_set_t *new_sym_set ()
{
	sym_set_t *sym_set = calloc (1, sizeof (sym_set_t));
	return sym_set;
}

/*
 * Delete symbol set
 */
void free_sym_set (sym_set_t *__sym_set)
{
	free (__sym_set);
}
