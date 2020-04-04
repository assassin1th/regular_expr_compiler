#ifndef TOKEN_H_
#define TOKEN_H_

enum token_type {SYM = 256}

class token
{
  public:
	token (int tag) : m_tag (tag)
	{ }

	int tag ()
	{
	  return m_tag;
	}

	virtual const std::set <char> &&val () const = 0;
  private:
	int m_tag;
}

class sym : public token
{
  public:
	sym (char c) : node (SYM), m_c (c)
	{ }

	virtual const std::set <char> &&val () const
	{
	  return std::move (std::set (m_c));
	}

  private
	char m_c;
}

#endif // TOKEN_H_
