#ifndef LEX_H_
#define LEX_H_

#include <string>
#include <memory>
#include "test/cpp/include/test.h"

namespace compiler
{

class token
{
public:
    using tag_type = char;

    token (tag_type tag);
    ~token ();
    tag_type tag () const;

#ifdef __TEST__
    friend std::ostream &operator << (std::ostream &out, const token &tok);
#endif // __TEST__

private:
    const tag_type m_tag;
};

class lex
{
public:
    lex (const std::string &src_str);
    ~lex ();
    std::unique_ptr<const token> scan ();
private:
    void read_char ();
    const std::string m_src_str;
    std::string::const_iterator m_peek;
};

}

#endif // LEX_H_
