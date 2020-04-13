#include <iostream>
#include "parser.h"

std::shared_ptr <node>
parser::parse ()
{
  auto ptr = concat ();

  if (m_top->tag () != END_OF_PAT)
  {
	std::cout << "expected end of pattern string" << std::endl;
	exit (-1);
  }

  return std::shared_ptr <node> (new cat (ptr, std::shared_ptr <node> (new literal (m_top))));
}

bool
parser::is_catable ()
{
  return m_top->tag () == SYM;
}

std::shared_ptr <node>
parser::concat ()
{
  auto left = catable ();
  while (is_catable ())
  {
	left = std::shared_ptr <node> (new cat (left, catable ()));
  }
  return left;
}

std::shared_ptr <node>
parser::catable ()
{
  std::shared_ptr <node> ptr = nullptr;

  switch (m_top->tag ())
  {
	case SYM:
	  ptr = symbol ();
	  break;
	default:
	  std::cout << "expected a catable pattern" << std::endl;
	  exit (-1);
	  break;
  }

  return ptr;
}

std::shared_ptr <node>
parser::symbol ()
{
  std::shared_ptr <node> ptr (new literal (m_top));

  move ();

  return ptr;
}
	  
std::stringstream &
operator>> (std::stringstream &in, std::shared_ptr <node> &ptr)
{
  ptr = parser (in).parse ();
  return in;
}
