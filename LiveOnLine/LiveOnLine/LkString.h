
#ifndef _LK_STRING_H_
#define _LK_STRING_H_

#include <string>
#include "Lkglobal.h"

using namespace std;

typedef string::iterator LkStringIterator;
class LkStringList;


class LkString : public string
{
public:
    LkString();
    LkString(const char *str);
    LkString(const char *str, int n);
    LkString(const string &str);
    //LkString(const string &str, size_t pos, size_t len = npos);
    LkString(size_t n, char c);

    virtual ~LkString();

    string toStdString();

    void chop(int n);
    LkString trimmed() const;
    void truncate(int position);

    /**
    * @brief C-Style sprintf
    * @see int vsprintf(char *str, const char *format, va_list ap)
    */
    LkString &sprintf(const char *cformat, ...);

    bool contains(const LkString &str) const;
    bool contains(const string &str) const;
    bool contains(const char *str) const;
    bool contains(const char *str, size_t len) const;

    bool startWith(const LkString &str) const;
    bool startWith(const string &str) const;
    bool startWith(const char *str) const;

    bool endWith(const LkString &str) const;
    bool endWith(const string &str) const;
    bool endWith(const char *str) const;

    /**
    * @brief replace string
    * @retval *this
    * @snippet
    * LkString a("///////a/bc////cc");
    * a.replace("//", "/");  // now a = "/a/bc/c"
    * a.replace("//", "/", false);  // a = "//////a/bc////cc"
    */
    LkString &replace(const LkString &before, const LkString &after, bool replaceAll = true);

    int toInt(bool *ok = 0, int base = 10);
    short toShort(bool *ok = 0, int base = 10);
    LkString toHex();
    muint64 toInt64(bool *ok = 0, int base = 10);

    inline bool isEmpty() const { return empty(); }

    LkStringList split(const LkString &sep);

    /**
     *  prepend \a str
     *  @snippet
     *  LkString pd("before");
     *  pd.prepend("123");      // pd : "123before"
     */
    LkString &prepend(const LkString &str);
    LkString &prepend(const char *str, int size);

    LkString & operator <<(mint32 value);
    LkString & operator <<(muint64 value);
    LkString & operator <<(const LkString &str);

public:
    static LkString number(mint32 n, int base = 10);
    static LkString number(muint64 n, int base = 10);
    static LkString number(size_t n, int base = 10);
};

#endif // LkString
