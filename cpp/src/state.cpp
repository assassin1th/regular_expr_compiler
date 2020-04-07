#include <algorithm>
#include "state.h"

positions_t
state::follow_by_sym (char symbol)
{
  positions_t res;

  for (auto pos : *this)
	if (pos->check_symbol (symbol))
	  std::set_union (res.begin (), res.end (),
	                  pos->follow_pos().begin (), pos->follow_pos ().end (),
					  std::inserter (res, res.end ()));
  
  return res;
}
