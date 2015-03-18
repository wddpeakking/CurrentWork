#include "LkStringList.h"
#include <iostream>

LkStringList::LkStringList()
{
}

LkStringList::~LkStringList()
{
}

bool LkStringList::isEmpty() const
{
	return empty();
}

int LkStringList::length()
{
	return size();
}

LkString &LkStringList::operator [](int i)
{
	list<LkString>::iterator iter = begin();
	for (int c = 0; c < i; ++c) {
		++iter;
	}
	return *iter;
}

const LkString &LkStringList::operator [](int i) const
{
	LkStringListConstItor iter = begin();
	for (int c = 0; c < i; ++c) {
		++iter;
	}
	return *iter;
}

LkStringList &LkStringList::operator <<(const LkString &str)
{
	this->push_back(str);
	return *this;
}

LkStringList &LkStringList::operator <<(const LkStringList &other)
{
	for (unsigned int i = 0; i < other.size(); ++i) {
		this->push_back(other.at(i));
	}

	return *this;
}

LkStringList &LkStringList::operator=(const LkStringList &other)
{
	this->clear();
	return *this << other;
}

LkString &LkStringList::at(int pos)
{
	return (*this)[pos];
}

const LkString &LkStringList::at(int pos) const
{
	return (*this)[pos];
}

LkString LkStringList::join(const LkString &sep)
{
	if (size() == 1) {
		return front();
	}

	LkString ret;
	for (list<LkString>::iterator iter = begin(); iter != end(); ++iter) {
		ret.append(*iter);
		ret.append(sep);
	}

	return ret;
}

LkStringList LkStringList::mid(int /*start*/, int /*length*/)
{
	// // TODO : imp
	LkStringList ret;

	return ret;
}

ostream & operator<<(ostream &o, const LkStringList& a)
{
	o << "(";
	for (unsigned int i = 0; i < a.size(); ++i) {
		const LkString &str = a[i];
		o << "\"" << str << "\"";
		if (i < a.size() -1) {
			o << ",";
		}
	}
	o << ")";

	return o;
}
