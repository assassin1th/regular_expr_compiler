#include <algorithm>
#include "dtran.h"
#include "compiler.h"

dtran::dtran () : m_tab (1)
{
  std::fill_n (m_tab[0].begin (), m_tab[0].size (), dtran::UNMATCHED_SYM_STATE);
}

void
dtran::add_transition (const state &cur, const state &next, char sym)
{
  auto next_ix = next.index ();
  if (next_ix >= m_tab.size ())
  {
	m_tab.resize (next_ix + 1);
	if (next.check_sym (regex_compiler::LIMITER))
	{
	  std::fill_n (m_tab[next_ix].begin (), m_tab[next_ix].size (),
	      dtran::HOST_STATE);
	}
	else
	{
	  std::fill_n (m_tab[next_ix].begin (), m_tab[next_ix].size (),
	      dtran::UNMATCHED_SYM_STATE);
	}
  }

  m_tab[cur.index ()][sym] = next_ix;
}

std::array <state::index_type, 128> &
dtran::operator[] (state::index_type ix)
{
  return m_tab[ix];
}

std::ostream &
operator<< (std::ostream &out, const dtran &tab)
{
  for (auto arr : tab.m_tab)
  {
	for (auto elem : arr)
	{
	  out << (int) elem << ' ';
	}
	out << std::endl;
  }
  return out;
}
