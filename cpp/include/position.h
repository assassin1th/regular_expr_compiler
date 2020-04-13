#ifndef POSITION_H_
#define POSITION_H_

#include "set.h"
#include <memory>
#include <algorithm>


class position
{
  public:
	position (const set <char> &abc) : m_abc (abc), m_follow_pos ()
	{
	}

	void add_follow_pos (set<std::shared_ptr <position>> &positions)
	{
	  sunion (m_follow_pos, positions, m_follow_pos);
	}

	bool check_symbol (char symbol)
	{
	  return m_abc.find (symbol);
	}

	const set<std::shared_ptr <position>> &follow_pos () const
	{
	  return m_follow_pos;
	}

  private:
	set <std::shared_ptr <position>> m_follow_pos;
	set <char> m_abc;
};

using positions_t = set <std::shared_ptr <position>>;

#endif // POSITION_H_
