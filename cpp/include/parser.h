#ifndef PARSER_H_
#define PARSER_H_

#include <iostream>
#include "lexer.h"
#include "AST.h"

class parser
{
  public:
	parser (const std::string &src) : m_lex (src)
	{
	  move ();
	}

	std::shared_ptr <node> parse ();

  private:
	void move ()
	{
	  m_top = m_lex.scan ();
	}

	bool is_catable ();

	std::shared_ptr <node> concat ();
	std::shared_ptr <node> catable ();
	std::shared_ptr <node> symbol ();

	lexer m_lex;
	std::shared_ptr <token> m_top;
};

#endif // PARSER_H_
