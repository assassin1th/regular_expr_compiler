#include "compiler.h"
#include "state.h"
#include "parser.h"
#include "lexer.h"
#include "position.h"
#include <list>
#include <algorithm>

using states_t = std::list <state>;
using dtran_t = std::vector <uint8_t [128]>;

bool
find_in_states (states_t &s, state_t &key)
{
  return std::find (s.begin (), s.end (), key);
}

std::vector <uint8_t [128]>
isingle_regexx_compiler::compile (const std::string &src)
{
  parser pr (src);

  auto ptr = pr->parse ();
  
  ptr->gen_follow_pos ();
  states_t states (ptr->first_pos ());
  dtran_t dtran ();

  for (auto s : states)
  {
	s.mark ();

	for (int a = 0; a < 128; ++a)
	{
	  auto u = s.follos_by_sym (a);

	  auto it = find_in_states (states, u);
	  if (it == states.end ())
	  {
		states.push_back (state (u, ++index));
		dtran[s.index ()][a] = index;
	  }
	  else
	  {
		dtran[s.index ()][a] = it->index ();
	  }
	}
  }
  
  return dtran;
}
