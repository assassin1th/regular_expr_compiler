#ifndef COMPILER_H_
#define COMPILER_H_

#include <string>
#include <vector>
#include <array>
#include "dtran.h"

class iregex_compiler
{
  public:
	enum {LIMITER = '\0'};
	iregex_compiler () = default;

	virtual dtran
	compile (const std::string &src) const = 0;
};

class isingle_regex_compiler : public virtual iregex_compiler
{
  public:
	isingle_regex_compiler () = default;

	virtual dtran
	compile (const std::string &src) const override;
};

#endif // COMPILER_H_
