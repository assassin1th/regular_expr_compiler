#include "AST.h"

cat::cat (const std::shared_ptr <node> &left,
          const std::shared_ptr <node> &right)
  : m_left (left), m_right (right), m_first_pos (left->first_pos ()),
    m_last_pos (right->last_pos ())
{
  if (left->nullable ())
	m_first_pos.merge (right->first_pos ());
  
  if (right->last_pos ())
	m_last_pos.merge (left->last_pos ());
}

void
cat::calc_follow_pos ()
{
  m_left->calc_follow_pos ();
  m_right->calc_follow_pos ();

  auto afp = m_right->first_pos ();
  for (auto ptr in m_left->first_pos ())
  {
	ptr->add_follow_pos (afp);
  }
}

void
symbol::calc_follow_pos ()
{ }

