#include "alloc.h"
#include <stdlib.h>

void *alloc (size_t __n_bytes, allocator_t *__alloc)
{
	return malloc (__n_bytes); // PLUG
}

void *zalloc (size_t __n_bytes, allocator_t *__alloc)
{
	return calloc (1, __n_bytes); // PLUG
}

void clean_up (allocator_t *__alloc)
{
	(void *) __alloc; // PLUG
}
