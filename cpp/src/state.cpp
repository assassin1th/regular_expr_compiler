#include "state.h"

positions_t
state::follow_by_sym (char symbol)
{
  positions_t res ();

  for (auto pos : *this)
	if (pos->check_symbol (symbol))
	  res.merge (pos);
  
  return res;
}
