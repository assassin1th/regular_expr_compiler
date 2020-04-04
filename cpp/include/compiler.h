#ifndef COMPILER_H_
#define COMPILER_H_

#include <string>
#include <vector>

class iregex_compiler
{
  public:
	iregex_compiler () = default;

	virtual std::vector <unit8_t [128]> compile (const std::string &src);
};

class isingle_regex_compiler : public iregex_compiler
{
  public:
	isingle_regex_compiler () = default;

	virtual std::vector <uint8_t [128]>
	compile (const std::string &src) override;
};

#endif // COMPILER_H_
