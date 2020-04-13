#include "compiler.h"
#include "state.h"
#include "parser.h"
#include "position.h"
#include <list>
#include <algorithm>

using states_t = std::list <state>;
using dtran_t = std::vector <std::array <uint8_t, 128> >;

states_t::iterator
find_in_states (states_t &s, positions_t &key)
{
  return std::find (s.begin (), s.end (), key);
}

static
bool
check_sym_in_state (state &s, char c)
{
  for (auto i : s)
  {
	if (i->check_symbol (c))
	  return true;
  }

  return false;
}

dtran_t
isingle_regex_compiler::compile (const std::string &src) const
{
  parser pr (src);

  auto ptr = pr.parse ();
  
  ptr->gen_follow_pos ();

  states_t states ({state (ptr->first_pos (), 0)});

  std::array<uint8_t, 128> arr;
  std::fill_n (arr.begin (), 128, iregex_compiler::UNMATCHED_SYM_STATE);
  dtran_t dtran {arr};

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
		auto s1 = state (u, ++index);
		states.push_back (s1);

		std::cout << (int) c << std::endl;
		if (check_sym_in_state (s1, parser::LIMITER))
		{
		  std::fill_n (arr.begin (), 128, iregex_compiler::HOST_STATE);
		}
		else
		{
		  std::fill_n (arr.begin (), 128, iregex_compiler::UNMATCHED_SYM_STATE);
		}
		dtran.push_back (arr);
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
