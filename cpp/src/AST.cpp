#include <algorithm>
#include "AST.h"
#include <iostream>

cat::cat (const std::shared_ptr <node> &left,
          const std::shared_ptr <node> &right)
  : node (left->first_pos (), right->last_pos ()),
    m_left (left), m_right (right)
{
  auto &right_first_pos = right->first_pos ();
  auto &left_last_pos = left->last_pos ();

  if (left->nullable ())
    sunion (m_first_pos, right_first_pos, m_first_pos);
  
  if (right->nullable ())
	sunion (m_last_pos, left_last_pos, m_last_pos);
}

void
cat::calc_follow_pos ()
{
  m_left->gen_follow_pos ();
  m_right->gen_follow_pos ();

  auto afp = m_right->first_pos ();
  for (auto ptr : m_left->last_pos ())
  {
	ptr->add_follow_pos (afp);
  }
}

void
literal::calc_follow_pos ()
{ }


