#ifndef PARSER_H_
#define PARSER_H_

#include "token_stream.h"
#include "AST.h"
#include <sstream>

class parser
{
  public:
	parser (const parser &) = delete;

	friend std::stringstream &
	operator>> (std::stringstream &in, std::shared_ptr <node> &ptr);
  protected:
	parser (std::stringstream &in) : m_in (in)
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

	std::stringstream &m_in;
	std::shared_ptr <const token> m_top;
};

std::stringstream &
operator>> (std::stringstream &in, std::shared_ptr <node> &ptr);

#endif // PARSER_H_
