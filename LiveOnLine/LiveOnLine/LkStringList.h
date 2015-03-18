#ifndef _LK_STRINGLIST_H_
#define _LK_STRINGLIST_H_

#include <list>
#include "LkString.h"

using namespace std;

class LkStringList : public list<LkString>
{
public:
	explicit LkStringList();
	~LkStringList();

	bool isEmpty() const;
	int length();

	LkString &operator[](int i);
	const LkString& operator[](int i) const;

	LkStringList &operator<<(const LkString &str);
	LkStringList &operator<<(const LkStringList &other);
	LkStringList &operator=(const LkStringList &other);

	LkString &at(int pos);
	const LkString& at(int pos) const;

	LkString join(const LkString &sep);

	LkStringList mid(int start, int length);

public:
	friend ostream & operator<<(ostream &o, const LkStringList& a);
};

typedef LkStringList::iterator LkStringListItor;
typedef LkStringList::const_iterator LkStringListConstItor;

#endif // LkStringLIST_HPP
