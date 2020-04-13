#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include "token_stream.h"
#include "AST.h"
#include <sstream>

class parser
{
  public:
	enum {LIMITER = '\0'};
	parser (const std::string &src) : m_in (new std::stringbuf (src))
	{
	  move ();
	}

	std::shared_ptr <node> parse ();

  private:
	void move ()
	{
	  m_in >> m_top;
	}

	bool is_catable ();

	std::shared_ptr <node> concat ();
	std::shared_ptr <node> catable ();
	std::shared_ptr <node> symbol ();

	std::istream m_in;
	std::shared_ptr <const token> m_top;
};

#endif // PARSER_H_
