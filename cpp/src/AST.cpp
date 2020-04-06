#include "AST.h"

cat::cat (const std::shared_ptr <node> &left,
          const std::shared_ptr <node> &right)
  : node (left->first_pos (), right->last_pos ()),
    m_left (left), m_right (right)
{
  if (left->nullable ())
	m_first_pos.merge (right->first_pos ());
  
  if (right->nullable ())
	m_last_pos.merge (left->last_pos ());
}

void
cat::calc_follow_pos ()
{
  m_left->gen_follow_pos ();
  m_right->gen_follow_pos ();

  auto afp = m_right->first_pos ();
  for (auto ptr : m_left->first_pos ())
  {
	ptr->add_follow_pos (afp);
  }
}

void
literal::calc_follow_pos ()
{ }

