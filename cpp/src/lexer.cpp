#include "lexer.h"

std::shared_ptr <token>
lexer::scan ()
{
  std::shared_ptr <token> ptr = nullptr;

  if (*m_peek == '\0')
	ptr = std::shared_ptr <token> (new token (*m_peek))
  else
  {
	ptr = std::shared_ptr <token> (new sym (*m_peek))
	++m_peek;
  }

  return ptr;
}
