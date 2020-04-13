#ifndef STATE_H_
#define STATE_H_

#include "position.h"

class state : public positions_t
{
  public:
	using index_type = uint8_t;

	state (positions_t &ps, index_type index)
	  : positions_t (ps), m_index (index)
	{ }

	index_type index () const
	{
	  return m_index;
	}

	positions_t follow_by_sym (char symbol);

	bool check_sym (char symbol) const;

  private:
	index_type m_index;
};

#endif // STATE_H_
