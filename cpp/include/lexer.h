#ifndef LEXER_H_
#define LEXER_H_

#include "token.h"
#include <memory>
#include <string>

class lexer
{
  public:
	lexer (const std::string &src) : m_src (src), m_peek (m_src.begin ())
	{ }

	std::shared_ptr <token> scan ();

  private:
	std::string m_src;
	std::string::const_iterator m_peek;
};

#endif // LEXER_H_
