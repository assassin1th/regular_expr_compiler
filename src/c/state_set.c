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
inline static _list_node_t *__new_list_node (unsigned __state, _list_node_t *__next) _inline 
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
inline static void _free_list_node (_list_node_t *__list_node) _inline
{
	if (__list_node->next)
		free_list_node (__list_node->next);
	
	free (__list_node);
}

inline static _list_node_t *_copy_list_node (const _list_node_t *__src_list_node) _inline
{
	return _new_list_node (__src_list_node->state, __src_list_node->next);
}

inline static void _insert_by_order (_list_node_t **__head, unsigned __state) _inline
{
	register _list_node_t **it_node = __head;
	for (;*it_node; it_node = (_list_node_t **) (*it_node)->next)
		if ((*it_node)->state < __state)
			continue;
		else if ((*it_node)->state == __state)
			goto EXIT;
		else
			break;
	
	*it_node = __new_list_node (__state, *it_node);
EXIT:
	return;
}
