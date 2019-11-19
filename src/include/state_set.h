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
state_set_t *new_state_set () _fastcall;

/*
 * Function, deleted set
 */
inline void free_state_set (state_set_t *__set) _inline
{
	free (__set);
}

/*
 * Function, copied set to new set
 */
state_set_t *copy_state_set (const state_set_t *__src_set) _fastcall;

/*
 * Function, updates set with new values
 */
states_set_t *update_state_set (state_set_t *__src_set, unsigned __state) _fastcall;

/*
 * Function, returns union of two sets from arguments
 */
state_set_t *union_state_set (const state_set_t *__first_src_set, const state_set_t *__second_src_set) _fastcall;

/*
 * Function, returns intersection of two sets from arguments
 */
state_set_t *intersection_state_set (const state_set_t *__first_src_set, const state_set_t *__second_src_set) _fastcall;

/*
 * Function, returns true if set1 == set2 else false
 */
int compare_state_set (const state_set_t *__first_src_set, const state_set_t *__second_src_set) _fastcall;

#endif // STATE_SET_H_
