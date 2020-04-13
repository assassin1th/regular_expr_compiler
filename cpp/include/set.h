#ifndef SET_H_
#define SET_H_

#include <set>
#include <algorithm>
#include <iostream>

template <class T>
class set : public std::set <T>
{
  public:
	set () = default;
	set (T &elem) : std::set<T> ({elem})
	{ }

	friend void
	sunion (const set &s1, const set &s2, set &dest)
	{
	  std::set_union (s1.begin (), s1.end (),
	      s2.begin (), s2.end (), std::inserter (dest, dest.end ()));
	}
};

template <>
class set <char>
{
  public:
	set ()
	{
	  std::fill_n (m_tab, sizeof (m_tab) >> 3, 0);
	}
	set (char c) : set ()
	{
	  insert (c);
	}

	friend void
	sunion (const set<char> &s1, const set<char> &s2, set<char> &dest)
	{
	  for (int i = 0; i < sizeof (m_tab) >> 3; ++i)
	  {
		dest.m_tab[i] = s1.m_tab[i] | s2.m_tab[i];
	  }
	}

	void
	insert (char c)
	{
	  m_tab[(uint8_t) c >> 6] |= (uint64_t) 1 << (c & (0x3F));
	}

	bool
	find (char c)
	{
	  return m_tab[(uint8_t) c >> 6] & ((uint64_t) 1 << (c & (0x3F)));
	}
  private:
	uint64_t m_tab[4];
};

#endif // SET_H_
