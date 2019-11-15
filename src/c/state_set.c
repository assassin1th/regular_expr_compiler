#include <stdint.h>
#include <stdlib.h>
#ifndef _inline
#define _inline __attribute__ ((always_inline))
#endif // _inline

typedef struct __l_node
{
	struct __l_node *next;
	unsigned state;
} _list_node_t;

/*
 * Function _new_list_node create new list node and initialize it with
 * __state argument
 */
static _list_node_t *_new_list_node (unsigned __state)
{
	_list_node_t *node = (_list_node_t *) malloc (sizeof (_list_node_t));
	
	if (!node)
		goto EXIT;

	node->next = NULL;
	node->state = __state;
EXIT:
	return node;
}

/*
 * Function _free_list_node delete all nodes in list where __list_node is a head
 */
static void _free_list_node (_list_node_t *__list_node)
{
	if (__list_node->next)
		free_list_node (__list_node->next);
	
	free (__list_node);
}

inline _inline static _list_node_t *_copy_list_node (_list_node_t *__src_list_node)
{
	return _new_list_node (__src_list_node->state);
}
