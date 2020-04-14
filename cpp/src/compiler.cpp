#include "compiler.h"
#include "state.h"
#include "parser.h"
#include "position.h"
#include <list>
#include <algorithm>
#include <iostream>

dtran
regex_compiler::compile (const std::vector <std::string> &src)
{
  this->init_states (src);

  dtran tab;

  for (auto s : m_states)
  {
	for (int c = 0; c < 128; ++c)
	{
	  auto u = s.follow_by_sym (c);

	  if (u.size () == 0)
	  {
		continue;
	  }

	  auto it = std::find (m_states.begin (), m_states.end (), u);
	  if (it == m_states.end ())
	  {
		m_states.push_back (state (u, m_states.size ()));
		tab.add_transition (s, m_states.back (), c);
	  }
	  else
	  {
		tab.add_transition (s, *it, c);
	  }
	}
  }

  return tab;
}

void
single_regex_compiler
    ::init_states (const std::vector <std::string> &src)
{
  std::stringstream in (src[0]);

  std::shared_ptr <node> ptr;

  in >> ptr;
  
  ptr->gen_follow_pos ();

  m_states.push_back (state (ptr->first_pos (), 0));
}













