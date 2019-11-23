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
 *
 * WARNING: I don't know how explain cases of pointer use
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

/*
 * Free mem from list where __head is pointer on poiter on first node
 * At the end in __head NULL
 */
inline _inline static void _free_list (_list_node_t **__head)
{
	for (_list_node_t *tmp; *__head; *__head = tmp)	
	{
		tmp = (*__head)->next;
		__free_list_node (*__head);
	}
}

/*
 * Function insert node in low order
 */
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

inline _inline static void _copy_list (const _list_node_t *__src_list_head, _list_node_t **__new_list_head)
{
	for (; __src_list_head; __new_list_head = *__new_list_head, __src_list_head = __src_list_head->next)
		*__new_list_head = __new_list_node (__src_list_head->state, NULL); 
}

typedef struct __s_set
{
	_list_node_t *head;
} state_set_t;

state_set_t *new_state_set ()
{
	return (state_set_t *) calloc (1, sizeof (state_set_t));
}



#ifdef TEST
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void print_list (const _list_node_t *__head)
{
	for (; __head; __head = __head->next)
		printf ("%d%c", __head->state, (__head->next) ? ' ' : '\n');
}

void list_from_str (_list_node_t **__head, const char *__src)
{
	char val[256];
	while (sscanf (__src, "%s", val) > 0)
	{
		__src += strlen (val);
		while (isspace (*__src))
			++__src;
		_insert_by_order (__head, atoi (val));
	}
}

int main (int argc, char *argv[])
{
	if (argc != 3) {
		printf ("%d\n" , argc);
		return 1;
	}

	_list_node_t *lists[--argc];

	++argv;
	for (int i = 0; i < argc; ++i)
	{
		lists[i] = NULL;
		list_from_str (&lists[i], argv[i]);
		print_list (lists[i]);
	}

	for (int i = 0; i < argc; ++i)
	{
		_free_list (&lists[i]);
	}
	return 0;
}
#endif // TEST
			
