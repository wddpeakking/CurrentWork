#ifndef _LK_STREAM_H_
#define _LK_STREAM_H_

#include "LkString.h"
class LkStream :public LkString
{
public:
	LkStream(void);
	~LkStream(void);
	void write1Bytes(uchar value);
	void write2Bytes(mint16 value);
	void write3Bytes(int value);
	void write4Bytes(int value);
	void write8Bytes(mint64 value);
	void write8Bytes(double value);
	void writeString(const LkString &value);
	void writeString(const char *data, int size);

	int read1Bytes(mint8 &var);
	int read2Bytes(mint16 &var);
	int read3Bytes(mint32 &var);
	int read4Bytes(mint32 &var);
	int read8Bytes(double &var);

	int readString(mint16 len, LkString &var);

	int left();
	int skip(int len);
	void reset();
	bool end();
	int pos();
	void print(int len);

private:
	mint32 m_pos;
};
#endif
