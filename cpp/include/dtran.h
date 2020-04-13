#ifndef DTRAN_H_
#define DTRAN_H_

#include <iostream>
#include "state.h"

class dtran
{
  public:
	enum {UNMATCHED_SYM_STATE = 254, HOST_STATE};

	dtran ();

	void
	add_transition (const state &cur, const state &next, char sym);

	std::array <state::index_type, 128> &
	operator[] (state::index_type ix);

	friend std::ostream &
	operator<< (std::ostream &out, const dtran &tab);

  private:
	std::vector <std::array <state::index_type, 128> > m_tab;
};

#endif // DTRAN_H_
