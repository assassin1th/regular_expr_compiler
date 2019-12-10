#ifndef POSITION_H_
#define POSITION_H_

#include "sym_set.h"
#include "position_set.h"

/*
 * Position structure, consists of
 * 	- ptr on sym_set for check character on this positions in syntax tree
 * 	- ptr on follow_set (type position_set) for getting information about follow
 * 	  positions in syntax tree
 * All position exemplars must be singleton objects, otherwise parser will not work
 */

typedef struct __position 
{
	sym_set_t *sym_set;
	position_set_t *follow_pos;
} position_t;

/*
 * Fabric function for position_t exemplar, single argument type is string with all 
 * characters respective this position
 */
position_t *new_position (const char *__char_range);

#endif // POSITION_H_
