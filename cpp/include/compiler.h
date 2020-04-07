#ifndef COMPILER_H_
#define COMPILER_H_

#include <string>
#include <vector>
#include <array>

class iregex_compiler
{
  public:
	enum {UNMATCHED_SYM_STATE = 254, HOST_STATE};

	iregex_compiler () = default;

	virtual std::vector <std::array <uint8_t, 128> >
	compile (const std::string &src) const = 0;
};

class isingle_regex_compiler : public virtual iregex_compiler
{
  public:
	isingle_regex_compiler () = default;

	virtual std::vector <std::array <uint8_t, 128> >
	compile (const std::string &src) const override;
};

#endif // COMPILER_H_
