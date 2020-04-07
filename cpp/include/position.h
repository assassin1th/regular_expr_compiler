#ifndef POSITION_H_
#define POSITION_H_

#include <set>
#include <memory>
#include <algorithm>


class position
{
  public:
	position (const std::set <char> &abc) : m_abc (abc), m_follow_pos ()
	{
	}

	void add_follow_pos (std::set<std::shared_ptr <position>> &positions)
	{
	  std::set_union (m_follow_pos.begin (), m_follow_pos.end (),
	                  positions.begin (), positions.end (),
					  std::inserter (m_follow_pos, m_follow_pos.end ()));
	}

	bool check_symbol (char symbol)
	{
	  return m_abc.find (symbol) != m_abc.end ();
	}

	const std::set<std::shared_ptr <position>> &follow_pos () const
	{
	  return m_follow_pos;
	}

  private:
	std::set <std::shared_ptr <position>> m_follow_pos;
	std::set <char> m_abc;
};

using positions_t = std::set <std::shared_ptr <position>>;

#endif // POSITION_H_
