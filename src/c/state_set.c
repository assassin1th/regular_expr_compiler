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

inline static _inline int __node_cmp (const _list_node_t *__l_node, const _list_node_t *__r_node)
{
	if (!__l_node && !__r_node)
		return 0;
	else if (!__l_node && __r_node)
		return -1;
	else if (__l_node && !__r_node)
		return 1;
	else
		return __l_node->state - __r_node->state;
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

inline _inline static void _insert (_list_node_t **__next, unsigned __state)
{
	*__next = __new_list_node (__state, *__next);
}

inline _inline static void _copy_list (_list_node_t **__new_list_head, const _list_node_t *__src_list_head)
{
	for (; __src_list_head; __new_list_head = *__new_list_head, __src_list_head = __src_list_head->next)
		*__new_list_head = __new_list_node (__src_list_head->state, NULL); 
}

inline _inline static int _list_cmp (const _list_node_t *__l_list, const _list_node_t *_r_list)
{
	register int res;
	for (; !(res = __node_cmp (__l_list, __r_list)); __l_list = __l_list->next, __r_list = __r_list->next)
		;
	return res;
}

typedef struct __s_set
{
	_list_node_t *head;
} state_set_t;

state_set_t *new_state_set ()
{
	return (state_set_t *) calloc (1, sizeof (state_set_t));
}

void free_state_set (state_set_t *__set)
{
	_free_list (__set->head);
	free (__set);
}

void copy_state_set (const state_set_t *__src_set, state_set_t *__dest_set)
{
	_copy_list (&__dest_set->head, __src_set->head);
}

void update_state_set (state_set_t *__set, unsigned __state)
{
	_insert_by_order (&__set->head, __state);
}

int cmp_state_set (const state_set_t *__l_set, const state_set_t *__r_set)
{
	return _list_cmp (__l_set->head, __r_set->head);
}

void union_state_set (const state_set_t *__first_set, const state_set_t *__second_set, state_set_t *__dest_set)
{
	_list_node_t **tail = &__dest_set->head;
	const _list_node_t *f_list = __first_set->head;
	const _list_node_t *s_list = __second_set->head;

	for (; f_list; f_list = f_list->next, tail = (_list_node_t **) *tail;)
		if (f_list->state <= s_list->state)
		{
			_insert (tail, f_list->state);
		}
		else
		{
			_list_node_t *tmp = f_list;
			f_list = s_list;
			s_list = tmp;
			
			_insert (tail, f_list->state);
		}
		
	for (; s_list; s_list = s_list->next, tail = tail->next)
		_insert (tail, s_list->state);
}

void intersection_state_set (const state_set_t *__first_set, const state_set_t *__second_set, state_set_t *__dest_set)
{
	_list_node_t **tail = &__dest_set->head;
	const _list_node_t *f_list = __first_set->head;
	const _list_node_t *s_list = __second_set->head;

	for (; f_list; f_list = f_list->next)
		if (f_list->state > s_list->state)
		{
			_list_node_t *tmp = f_list;
			f_list = s_list;
			s_list = tmp;
		} 
		else if (f_list->state == s_list->state)
		{
			_insert (tail, f_list->state);
			tail = (_list_node_t **) *tail;

			s_list = s_list->next;
		}
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
			
