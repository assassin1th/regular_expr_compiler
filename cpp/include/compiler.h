#ifndef COMPILER_H_
#define COMPILER_H_

#include <string>
#include <vector>
#include <list>
#include "dtran.h"

class regex_compiler
{
  public:
	enum {LIMITER = '\0'};
	regex_compiler () = default;

	dtran
	compile (const std::vector <std::string> &src);
  protected:
	using states_t = std::list <state>;

	virtual void
	init_states (const std::vector <std::string> &src) = 0;

	states_t m_states;
};

class single_regex_compiler : public virtual regex_compiler
{
  public:
	single_regex_compiler () = default;
  protected:
	void
	init_states (const std::vector <std::string> &src) override;
};

#endif // COMPILER_H_
