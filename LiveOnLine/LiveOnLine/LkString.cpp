#include "LkString.h"

#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "LkStringList.h"

LkString::LkString()
{
}

LkString::LkString(const char *str)
	: string(str)
{

}

LkString::LkString(const char *str, int n)
	: string(str, n)
{

}

LkString::LkString(const string &str)
	: string(str)
{

}


LkString::LkString(size_t n, char c)
	: string(n, c)
{

}

LkString::~LkString()
{
}

string LkString::toStdString()
{
	return string(c_str());
}

void LkString::chop(int n)
{
	if ((muint32)n >= size()) {
		clear();

		return;
	}

	erase(size() - n, n);
}

// '\t', '\n', '\v', '\f', '\r', and ' '
LkString LkString::trimmed() const
{
	int beginIndex = 0;
	int endIndex = 0;

	// find beginIndex
	for (unsigned int i = 0; i < size(); ++i) {
		char c = this->at(i);
		if (c == '\t'
			|| c == '\n'
			|| c == '\v'
			|| c == '\f'
			|| c == '\r'
			|| c == ' ') {
				++beginIndex;
		} else {
			break;
		}
	}

	// find endIndex
	for (int i = size() - 1; i >= 0; --i) {
		char c = this->at(i);
		if (c == '\t'
			|| c == '\n'
			|| c == '\v'
			|| c == '\f'
			|| c == '\r'
			|| c == ' ') {
				++endIndex;
		} else {
			break;
		}
	}

	return substr(beginIndex, size() - beginIndex - endIndex);
}

void LkString::truncate(int position)
{
	LkStringIterator first = begin() + position;
	erase(first, end());
}

LkString &LkString::sprintf(const char *cformat, ...)
{
	va_list vp;
	va_start(vp, cformat);

	char buffer[1024];
	vsprintf(buffer, cformat, vp);
	va_end(vp);
	this->append(buffer);

	return *this;
}

bool LkString::contains(const LkString &str) const
{
	return find(str) != npos;
}

bool LkString::contains(const string &str) const
{
	return find(str) != npos;
}

bool LkString::contains(const char *str) const
{
	return find(str) != npos;
}

bool LkString::startWith(const LkString &str) const
{
	return find_first_of(str) == 0;
}

bool LkString::startWith(const string &str) const
{
	return find_first_of(str) == 0;
}

bool LkString::startWith(const char *str) const
{
	return find_first_of(str) == 0;
}

bool LkString::endWith(const LkString &str) const
{
	return find_last_of(str) == (size() - str.size());
}

bool LkString::endWith(const string &str) const
{
	return find_last_of(str) == (size() - str.size());
}

bool LkString::endWith(const char *str) const
{
	return find_last_of(str) == (size() - strlen(str));
}

LkString &LkString::replace(const LkString &before, const LkString &after, bool replaceAll)
{
	size_t  pos = npos;
	while ((pos = find(before.c_str())) != npos) {
		string::replace(pos, before.size(), after);

		if (!replaceAll) {
			break;
		}
	}

	return *this;
}


LkStringList LkString::split(const LkString &sep)
{
	LkString temp(*this);
	LkStringList ret;
	if (sep.isEmpty()) {
		return ret;
	}

	while (temp.contains(sep)) {
		size_type index = temp.find(sep);

		LkString ss = temp.substr(0, index);
		if (!ss.isEmpty()) {
			ret << ss;
		}
		temp = temp.substr(index + sep.size(), temp.size() - 1);
	}
	if (!temp.isEmpty()) {
		ret << temp;
	}

	return ret;
}

LkString &LkString::prepend(const LkString &str)
{
	LkString temp = *this;
	*this = str + temp;
	return *this;
}

LkString &LkString::prepend(const char *str, int size)
{
	LkString temp(str, size);
	return prepend(temp);
}

LkString & LkString::operator <<(mint32 value)
{
	append(number(value));
	return *this;
}

LkString & LkString::operator <<(muint64 value)
{
	append(number(value));
	return *this;
}

LkString & LkString::operator <<(const LkString &str)
{
	append(str);
	return *this;
}

LkString LkString::number(mint32 n, int /*base*/)
{
	// TODO process base
	char buffer[32] = {0};
	::sprintf(buffer, "%d", n);

	return buffer;
}

LkString LkString::number(muint64 n, int /*base*/)
{
	// TODO process base
	char buffer[64] = {0};
	::sprintf(buffer, "%lld", n);

	return buffer;
}

LkString LkString::number(size_t n, int /*base*/)
{
	// TODO process base
	char buffer[32] = {0};
	::sprintf(buffer, "%d", n);

	return buffer;
}
