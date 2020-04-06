#ifndef COMPILER_H_
#define COMPILER_H_

#include <string>
#include <vector>
#include <array>

class iregex_compiler
{
  public:
	iregex_compiler () = default;

	virtual std::vector <uint8_t [128]>
	compile (const std::string &src) = 0;
};

class isingle_regex_compiler : public virtual iregex_compiler
{
  public:
	isingle_regex_compiler () = default;

	virtual std::vector <uint8_t [128]>
	compile (const std::string &src) override;
};

#endif // COMPILER_H_
