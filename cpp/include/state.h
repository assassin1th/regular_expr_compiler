#ifndef STATE_H_
#define STATE_H_

#include "position.h"

class state : public positions_t
{
  public:
	using index_type = uint8_t;

	state (positions_t &ps, index_type index)
	  : positions_t (ps), m_index (index), m_marked (false)
	{ }

	index_type index () const
	{
	  return m_index;
	}

	bool is_marked () const
	{
	  return m_marked;
	}

	void mark ()
	{
	  m_marked = true;
	}

	positions_t follow_by_sym (char symbol);

	bool check_sym (char symbol) const;

  private:
	index_type m_index;
	bool m_marked;
};

#endif // STATE_H_
