#include <algorithm>
#include "state.h"

positions_t
state::follow_by_sym (char symbol)
{
  positions_t res;

  for (auto pos : *this)
	if (pos->check_symbol (symbol))
	  sunion (res, pos->follow_pos (), res);

  return res;
}

bool
state::check_sym (char symbol) const
{
  for (auto pos : *this)
	if (pos->check_symbol (symbol))
	  return true;
  
  return false;
}

