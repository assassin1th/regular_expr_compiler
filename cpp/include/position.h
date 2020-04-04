#ifndef POSITION_H_
#define POSITION_H_

#include <set>
#include <memory>

using positions_t = std::set <const std::shared_ptr <position>>;

class position
{
  public:
	position (const std::set <char> &abc) : m_abc (abc), m_followpos ()
	{
	};

	void add_followpos (positions_t &positions)
	{
	  m_followpos.merge (positions);
	};

	bool check_symbol (char symbol)
	{
	  return m_abc.find (symbol) != m_abc.end ();
	};

	const std::set<position> &followpos ()
	{
	  return m_followpos;
	};

  private:
	positions_t m_followpos;
	std::set <char> m_abc;
}
#endif // POSITION_H_
