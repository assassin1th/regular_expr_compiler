#ifndef LEXER_H_
#define LEXER_H_

#include "token.h"
#include <memory>
#include <string>
#include <istream>

class token_stream : public std::istream
{
  public:
	token_stream (std::streambuf *buf) : std::istream (buf)
	{ }

	friend token_stream &operator>> (token_stream &in,
	    std::shared_ptr <const token> &ptr);
};

#endif // LEXER_H_
