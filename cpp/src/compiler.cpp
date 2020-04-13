#include "compiler.h"
#include "state.h"
#include "parser.h"
#include "position.h"
#include <list>
#include <algorithm>
#include <iostream>

using states_t = std::list <state>;

states_t::iterator
find_in_states (states_t &s, positions_t &key)
{
  return std::find (s.begin (), s.end (), key);
}

dtran
isingle_regex_compiler::compile (const std::string &src) const
{
  std::stringstream in (src);
  std::shared_ptr <node> ptr;

  in >> ptr;
  
  ptr->gen_follow_pos ();

  states_t states ({state (ptr->first_pos (), 0)});

  dtran tab;

  uint8_t index=0;
  for (auto s : states)
  {
	s.mark ();

	for (int c = 0; c < 128; ++c)
	{
	  auto u = s.follow_by_sym (c);

	  if (u.size () == 0)
	  {
		continue;
	  }

	  auto it = find_in_states (states, u);
	  if (it == states.end ())
	  {
		states.push_back (state (u, ++index));
		tab.add_transition (s, states.back (), c);
	  }
	  else
	  {
		tab.add_transition (s, *it, c);
	  }
	}
  }

  return tab;
}
