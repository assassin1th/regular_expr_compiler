#include "lexer.h"

token_stream &
operator>> (token_stream &in, std::shared_ptr <const token> &ptr)
{
  int c = in.get ();
  if (c == '\0' || c == EOF)
	ptr = std::shared_ptr <const token> (new meta (END_OF_PAT));
  else
  {
	ptr = std::shared_ptr <const token> (new sym (c));
  }

  return in;
}
