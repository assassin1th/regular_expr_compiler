#ifndef STATE_SET_H_
#define STATE_SET_H_

#include "attr.h"
/*
 * Simple set structure
 */
typedef struct __s_set
{
	void *head;
} state_set_t;

/*
 * Fucntion, produced empty set
 */
state_set_t *new_state_set ();

/*
 * Function, deleted set
 */
void free_state_set (state_set_t **__set);

/*
 * Function, copied set to new set
 */
void copy_state_set (const state_set_t *__src_set, state_set_t *__dest_set);

/*
 * Function, updates set with new values
 */
void update_state_set (state_set_t *__set, unsigned __state);

/*
 * Function, returns union of two sets from arguments
 */
void union_state_set (const state_set_t *__first_src_set, const state_set_t *__second_src_set, state_set_t *__dest_set);

/*
 * Function, returns intersection of two sets from arguments
 */
void intersection_state_set (const state_set_t *__first_src_set, const state_set_t *__second_src_set, state_set_t *__dest_set);

/*
 * Function, returns true if set1 == set2 else false
 */
int state_set_cmp (const state_set_t *__first_src_set, const state_set_t *__second_src_set);

#endif // STATE_SET_H_
