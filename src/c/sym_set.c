#include <stdlib.h>
#include "sym_set.h"
#include "alloc.h"

/*
 * Create empty symbol set (all bits set to 0)
 */
sym_set_t *new_sym_set (allocator_t *__alloc)
{
	sym_set_t *sym_set = zalloc (sizeof (sym_set_t), __alloc);
	return sym_set;
}

/*
 * Delete symbol set
 */
void free_sym_set (sym_set_t *__sym_set)
{
	free (__sym_set);
}

#ifdef TEST
#include <stdio.h>

int main (int argc, char *argv[])
{
	if (argc != 2)
		return 1;
	
	sym_set_t *sym_set = new_sym_set (NULL);

	for (++argv; **argv != '\0'; ++*argv){
		add_sym (sym_set, *argv[0]);
	}

	for (uint8_t c = 0; c < 128; ++c)
		if (check_sym (sym_set, c))
			printf ("%c\n", c);

	free_sym_set (sym_set);

	return 0;
}
#endif // TEST
