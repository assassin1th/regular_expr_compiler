#include "compiler.h"
#include "state.h"
#include "parser.h"
#include "lexer.h"
#include "position.h"
#include <list>
#include <algorithm>

using states_t = std::list <state>;
using dtran_t = std::vector <uint8_t [128]>;

states_t::iterator
find_in_states (states_t &s, positions_t &key)
{
  return std::find (s.begin (), s.end (), key);
}

dtran_t
isingle_regex_compiler::compile (const std::string &src)
{
  parser pr (src);

  auto ptr = pr.parse ();
  
  ptr->gen_follow_pos ();
  states_t states ({state (ptr->first_pos (), 0)});
  dtran_t dtran;

  uint8_t index=0;
  for (auto s : states)
  {
	s.mark ();

	for (int c = 0; c < 128; ++c)
	{
	  auto u = s.follow_by_sym (c);

	  auto it = find_in_states (states, u);
	  if (it == states.end ())
	  {
		states.push_back (state (u, ++index));
		dtran[s.index ()][c] = index;
	  }
	  else
	  {
		dtran[s.index ()][c] = it->index ();
	  }
	}
  }
  
  return dtran;
}
