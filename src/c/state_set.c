#include <stdint.h>
#include <stdlib.h>
#include "attr.h"

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
 * Function _free_list_node free mem on __list_node pointer
 */
inline static _inline void __free_list_node (_list_node_t *__list_node)
{
	free (__list_node);
}

inline _inline static void _free_list (_list_node_t **__head)
{
	for (_list_node_t *tmp; *__head; *__head = tmp)	
	{
		tmp = (*__head)->next;
		__free_list_node (*__head);
	}
}

inline _inline static _list_node_t *_copy_list_node (const _list_node_t *__src_list_node)
{
	return __new_list_node (__src_list_node->state, __src_list_node->next);
}

inline _inline static void _insert_by_order (_list_node_t **__head, unsigned __state)
{
	register _list_node_t **it_node = __head;
	for (;*it_node; it_node = (_list_node_t **) *it_node){
		if ((*it_node)->state < __state)
			continue;
		else if ((*it_node)->state == __state)
			goto EXIT;
		else
			break;
	}

	*it_node = __new_list_node (__state, *it_node);
EXIT:
	return;
}

#ifdef TEST
#include <stdio.h>
#include <ctype.h>

void print_list (const _list_node_t *__head)
{
	for (; __head; __head = __head->next)
		printf ("%d%c", __head->state, (__head->next) ? ' ' : '\n');
}

void list_from_str (_list_node_t **__head, const char *__src)
{
	for (int len = 0, val = 0; (len = sscanf (__src, "%d", &val)) > 0;)
	{
		__src += len;
		while (isspace (*__src))
			++__src;
		_insert_by_order (__head, val);
	}
}

int main (int argc, char *argv[])
{
	if (argc != 3) {
		printf ("%d\n" , argc);
		return 1;
	}

	_list_node_t *head = NULL;
	unsigned val = 0;

	for (int i = 1, len = 0; i < argc; ++i)
	{
		list_from_str (&head, argv[i]);
		print_list (head);
		_free_list (&head);
	}
	return 0;
}
#endif // TEST
			
