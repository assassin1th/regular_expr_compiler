#include <stdint.h>
#include <stdlib.h>
#ifndef _inline
#define _inline __attribute__ ((always_inline))
#endif // _inline
#ifndef _fastcall
#define _fastcall __attribute__ ((fastcall))

/*
 * This module consists of few primitives:
 * 	1) base container structure - linked list
 * 	2) set structure
 * Basicly linked list is already sorted, for quick insert and search
 * Set interfaces must perform operations on a list (like as delete and insert node)
 * only with list interfaces
 */

typedef struct __l_node
{
	struct __l_node *next;
	unsigned state;
} _list_node_t;

/*
 * Function _new_list_node create new list node and initialize it with
 * __state and __next argument
 */
inline _inline static _list_node_t *__new_list_node (unsigned __state, _list_node_t *__next)
{
	_list_node_t *node = (_list_node_t *) malloc (sizeof (_list_node_t));
	
	if (node)
	{
		node->next = __next;
		node->state = __state;
	}
	// Return NULL if no mem
	return node;
}

/*
 * Function _free_list_node delete all nodes in list where __list_node is a head
 */
inline _inline static void _free_list_node (_list_node_t *__list_node)
{
	if (__list_node->next)
		free_list_node (__list_node->next);
	
	free (__list_node);
}

inline _inline static _list_node_t *_copy_list_node (const _list_node_t *__src_list_node)
{
	return _new_list_node (__src_list_node->state, __src_list_node->next);
}

inline _inline static void _insert_by_order (_list_node_t **__head, unsigned __state)
{
	register _list_node_t **tmp = __head;
	for (;*tmp; tmp = (_list_node_t **) (*tmp)->next)
		if ((*tmp)->state < __state)
			continue;
		else if ((*tmp)->state == __state)
			goto EXIT;
		else
			break;
	
	*tmp = __new_list_node (__state, *tmp);
EXIT:
	return;
}
