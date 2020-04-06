#ifndef STATE_H_
#define STATE_H_

#include "position.h"

class state : public positions_t
{
  public:
	state (positions_t &ps, int index)
	  : positions_t (ps), m_index (index), m_marked (false)
	{ }

	int index () const
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

  private:
	int m_index;
	bool m_marked;
};

#endif // STATE_H_
