#ifndef ALLOC_H_
#define ALLOC_H_

#include <stddef.h>
#include <stdint.h>

/*
 * This module helps in memory managment in compile phase.
 * After all compile steps must be called clean_up function
 * This function freed all mem, used in alloc and zalloc allocators.
 *
 * I think this strategy take place because result of compile phaze is
 * jump table, memory for which allocates with standart allocator, like malloc,
 * realy idk.
 */

/*
 * Allocator structure
 */
typedef struct __allocator
{
	uint8_t *mem;
} allocator_t;

/*
 * Alloc memory block with __n_bytes size
 */
void *alloc (size_t __n_bytes, allocator_t *__alloc);

/*
 * Alloc memory block with __n_bites size and fills it with zero values
 */

void *zalloc (size_t __n_bytes, allocator_t *__alloc);

/*
 * Free all memory, used in alloc and zalloc alocators
 */
void clean_up (allocator_t *__alloc);

#endif // ALLOC_H_
