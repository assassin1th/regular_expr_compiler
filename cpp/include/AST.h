#ifndef AST_H_
#define AST_H_

#include "position.h"
#include "token.h"

class node 
{
  public:
	node () = default;
	node (positions_t &first_pos, positions_t &last_pos)
	: m_first_pos (first_pos), m_last_pos (last_pos)
	{ }

	positions_t &first_pos () 
	{
	  return m_first_pos;
	}

	positions_t &last_pos () 
	{
	  return m_last_pos;
	}

	void gen_follow_pos ()
	{
	  this->calc_follow_pos ();
	}
	
	bool nullable () const 
	{
	  return this->is_nullable ();
	}

  protected:
	virtual void calc_follow_pos () = 0;
	virtual bool is_nullable () const = 0;

	positions_t m_first_pos;
	positions_t m_last_pos;
};

class cat : public virtual node
{
  public:
	cat (const std::shared_ptr <node> &left,
		 const std::shared_ptr <node> &right);

  protected:
	virtual bool is_nullable () const override
	{
	  return m_left->nullable () && m_right->nullable ();
	}

	virtual void calc_follow_pos () override;

  private:
	std::shared_ptr <node> m_left;
	std::shared_ptr <node> m_right;
};

class literal : public virtual node
{
  public:
	literal (const std::shared_ptr <const token> &tok)
	: m_position (new position (tok->val ()))
	{
	  m_first_pos.insert (m_position);
	  m_last_pos.insert (m_position);
	}

  protected:
	virtual bool is_nullable () const override
	{
	  return false;
	}

	virtual void calc_follow_pos () override;

  private:
	std::shared_ptr <position> m_position;
};

#endif // AST_H_
