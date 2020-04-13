#ifndef TOKEN_H_
#define TOKEN_H_

#include "set.h"
enum token_type {END_OF_PAT = '\0', SYM = 256};

class token
{
  public:
	token (int tag) : m_tag (tag)
	{ }

	int tag () const
	{
	  return m_tag;
	}

	virtual set <char> val () const = 0;
  private:
	int m_tag;
};

class meta : public token
{
  public:
	meta (char c) : token (c)
	{ }

	virtual set <char> val () const
	{
	  return set <char> ((char) this->tag ());
	}
};

class sym : public token
{
  public:
	sym (char c) : token (SYM), m_c (c)
	{ }

	virtual set <char> val () const
	{
	  return set <char> (m_c);
	}

  private:
	char m_c;
};

#endif // TOKEN_H_
