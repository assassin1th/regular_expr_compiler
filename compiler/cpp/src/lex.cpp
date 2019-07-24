#include "compiler/cpp/include/lex.h"

using namespace compiler;

token::token (token::tag_type tag) :
    m_tag (tag)
{
}

token::~token ()
{
}

token::tag_type
token::tag () const
{
    return m_tag;
}

std::ostream &
compiler::operator << (std::ostream &out, const token &tok)
{
    out << "<'" << tok.m_tag << "' | " << tok.m_tag << ">";
    return out;
}

lex::lex (const std::string &src_str) :
    m_src_str (src_str), m_peek (m_src_str.begin ())
{
}

lex::~lex ()
{
}

std::unique_ptr<const token>
lex::scan ()
{
    token *tok = new token (*m_peek);

    read_char();

    return std::unique_ptr<const token> (tok);
}

void
lex::read_char ()
{
    ++m_peek;
}
