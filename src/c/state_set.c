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
 * Cmp node: __l_node value - __r_node value
 */
inline static _inline int __cmp_node (const _list_node_t *__l_node, const _list_node_t *__r_node)
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
 * _insert Function insert a _list_node_t with __state value before __next node
 */
inline _inline static void _insert (_list_node_t **__next, unsigned __state)
{
	*__next = __new_list_node (__state, *__next);
}

/*
 * _copy_list Function copied __src_list to __new_list
 */
inline _inline static void _copy_list (_list_node_t **__new_list_head, const _list_node_t *__src_list_head)
{
	for (; __src_list_head; __new_list_head = (_list_node_t **) *__new_list_head, __src_list_head = __src_list_head->next)
		*__new_list_head = __new_list_node (__src_list_head->state, NULL); 
}

/*
 * _cmp_list Function works like strcmp: __l_list - __r_list
 */
inline _inline static int _cmp_list (const _list_node_t *__l_list, const _list_node_t *__r_list)
{
	register int res;
	for (; !(res = __cmp_node (__l_list, __r_list)); __l_list = __l_list->next, __r_list = __r_list->next)
		;
	return res;
}

typedef struct __s_set
{
	_list_node_t *head;
} state_set_t;

/*
 * Return mem chunk with size equal sizeof (state_set_t)
 */
state_set_t *new_state_set ()
{
	return (state_set_t *) calloc (1, sizeof (state_set_t));
}

/*
 * Free mem from __set
 */
void free_state_set (state_set_t *__set)
{
	_free_list (&__set->head);
	free (__set);
}

/*
 * Copy __src_set to existing, but empty __dest_set
 */
void copy_state_set (state_set_t *__dest_set, const state_set_t *__src_set)
{
	_copy_list (&__dest_set->head, __src_set->head);
}

/*
 * Add new __state value to __dest set
 */
void update_state_set (void *__dest, unsigned __state)
{
	__dest = &((state_set_t *) __dest)->head; // For memory saving
	
	/*
	 * __dest contains a address to pointer on pointer on node
	 * At each iteration value in node compares with __state value
	 * If NODE value < __state value then continue cycle
	 * Else IF NODE value == __state value we going to exit
	 * Else (NODE value > __state value) we exit the cycle
	 */
	for (; *(_list_node_t **) __dest; __dest = &(*(_list_node_t **) __dest)->next)
		if ((*(_list_node_t **) __dest)->state < __state)
			continue;
		else if ((*(_list_node_t **) __dest)->state == __state)
			goto EXIT;
		else 
			break;
	// Insert value in linst (see _insert description)
	_insert (__dest, __state);
EXIT:
	return;
}

/*
 * Cmp to sets like strcmp: ret __l_set - __r_set
 */
int cmp_state_set (const state_set_t *__l_set, const state_set_t *__r_set)
{
	return _cmp_list (__l_set->head, __r_set->head);
}

/*
 * Union two sets to existing, but empty __dest set
 */
void union_state_set (void *__dest, const void *__first, const void *__second)
{
	// For saving memory
	__dest = &((state_set_t *) __dest)->head;
	__first = ((state_set_t *) __first)->head;
	__second = ((state_set_t *) __second)->head;

	/*
	 * At each iteration we compare __first value and __second value
	 * IF __first value < __second value use _insert methon to __dest list
	 * ELIF __first value == __second value use _insert method to __dest list and go to new __second node
	 * ELSE SWAP __first and __second for change iterable list and _insert __first value to __dest list
	 */
	for (; __first; __first = ((_list_node_t *) __first)->next, __dest = &(*(_list_node_t **) __dest)->next)
	{
		if (((_list_node_t *) __first)->state > ((_list_node_t *) __second)->state)
		{
			const void *tmp = __first;
			__first = __second;
			__second = tmp;
		}
		else if (((_list_node_t *) __first)->state == ((_list_node_t *) __second)->state)
		{
			__second = ((_list_node_t *) __second)->next;
		}
		_insert (__dest, ((_list_node_t *) __first)->state);
	}
		
	/*
	 * _insert ramaining values to __dest list
	 */
	for (; __second; __second = ((_list_node_t *) __second)->next, __dest = &(*(_list_node_t **) __dest)->next)
		_insert (__dest, ((_list_node_t *) __second)->state);
}

/*
 * Intersection two sets to existing, but empty __dest set
 */
void intersection_state_set (void *__dest, const void *__first, const void *__second)
{
	// For memory saving
	__dest = &((state_set_t *) __dest)->head;
	__first = ((state_set_t *) __first)->head;
	__second = ((state_set_t *) __second)->head;

	/*
	 * At each iteration we compare __first value and __second value
	 * IF __first value > __second value SWAP __first and __second for change iterable list
	 * ELIF __fist value == __second value _insert value to __dest list and move __first and __second iterators to new node
	 * ELSE continue list
	 */
	for (; __first; __first = ((_list_node_t *) __first)->next)
		if (((_list_node_t *) __first)->state > ((_list_node_t *) __second)->state)
		{
			const void *tmp = __first;
			__first = __second;
			__second = tmp;
		} 
		else if (((_list_node_t *) __first)->state == ((_list_node_t *) __second)->state)
		{
			_insert (__dest, ((_list_node_t *) __first)->state);
			__dest = &(*(_list_node_t **) __dest)->next;

			__second = ((_list_node_t *) __second)->next;
		}
}

#ifdef TEST
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void print_list (const _list_node_t *__head)
{
	if (!__head)
		printf ("empty\n");
	for (; __head; __head = __head->next)
		printf ("%d%c", __head->state, (__head->next) ? ' ' : '\n');
}

void set_from_str (state_set_t *__set, const char *__src)
{
	char val[256];
	while (sscanf (__src, "%s", val) > 0)
	{
		__src += strlen (val);
		while (isspace (*__src))
			++__src;
		update_state_set (__set, atoi (val));
	}
}

int main (int argc, char *argv[])
{
	if (argc != 3) {
		printf ("%d\n" , argc);
		return 1;
	}

	state_set_t *sets[--argc];
	++argv;
	for (int i = 0; i < argc; ++i)
	{
		sets[i] = new_state_set ();
		set_from_str (sets[i], argv[i]);

		print_list (sets[i]->head);
	}

	// Copy test
	state_set_t *res = new_state_set ();

	copy_state_set (res, sets[0]);
	print_list (res->head);

	free_state_set (res);

	// Union test
	res = new_state_set ();

	union_state_set (res, sets[0], sets[1]);
	print_list (res->head);

	free_state_set (res);

	// Intersection test
	res = new_state_set ();

	intersection_state_set (res, sets[0], sets[1]);
	print_list (res->head);

	free_state_set (res);

	// Cmp test
	printf ("%d\n", cmp_state_set (sets[0], sets[1]));

	for (int i = 0; i < argc; ++i)
	{
		free_state_set (sets[i]);
	}
	return 0;
}
#endif // TEST
			
