#include "LkStream.h"

#define E_SUCCESS           0
#define E_SPACE_NOT_ENOUGH  -2
#define E_STREAM_SKIP_ERROR -3

LkStream::LkStream()
	: m_pos(0)
{
}
LkStream::~LkStream()
{
}


void LkStream::write1Bytes(uchar value)
{
	append(1, (char)value);
}

void LkStream::write2Bytes(mint16 value)
{
	char *p = (char*)&value;
	append(1, p[1]);
	append(1, p[0]);
}

void LkStream::write3Bytes(int value)
{
	char *p = (char*)&value;
	append(1, p[2]);
	append(1, p[1]);
	append(1, p[0]);
}

void LkStream::write4Bytes(int value)
{
	char *p = (char*)&value;
	append(1, p[3]);
	append(1, p[2]);
	append(1, p[1]);
	append(1, p[0]);
}

void LkStream::write8Bytes(mint64 value)
{
	char *p = (char*)&value;
	append(1, p[7]);
	append(1, p[6]);
	append(1, p[5]);
	append(1, p[4]);
	append(1, p[3]);
	append(1, p[2]);
	append(1, p[1]);
	append(1, p[0]);
}

void LkStream::write8Bytes(double value)
{
	char *p = (char*)&value;
	append(1, p[7]);
	append(1, p[6]);
	append(1, p[5]);
	append(1, p[4]);
	append(1, p[3]);
	append(1, p[2]);
	append(1, p[1]);
	append(1, p[0]);
}

void LkStream::writeString(const LkString &value)
{
	append(value);
}

void LkStream::writeString(const char *data, int size)
{
	append(data, size);
}

int LkStream::read1Bytes(mint8 &var)
{
	int ret = E_SUCCESS;
	if (left() < (int)sizeof(var)) {
		return E_SPACE_NOT_ENOUGH;
	}

	char *p = (char*)&var;
	p[0] = at(m_pos++);

	return ret;
}

int LkStream::read2Bytes(mint16 &var)
{
	int ret = E_SUCCESS;
	if (left() < 2) {
		return E_SPACE_NOT_ENOUGH;
	}

	char *p = (char*)&var;
	p[1] = at(m_pos++);
	p[0] = at(m_pos++);

	return ret;
}

int LkStream::read3Bytes(mint32 &var)
{
	int ret = E_SUCCESS;
	if (left() < 3) {
		return E_SPACE_NOT_ENOUGH;
	}

	char *p = (char*)&var;
	p[3] = 0;
	p[2] = at(m_pos++);
	p[1] = at(m_pos++);
	p[0] = at(m_pos++);

	return ret;
}

int LkStream::read4Bytes(mint32 &var)
{
	int ret = E_SUCCESS;
	if (left() < 4) {
		return E_SPACE_NOT_ENOUGH;
	}

	char *p = (char*)&var;
	p[3] = at(m_pos++);
	p[2] = at(m_pos++);
	p[1] = at(m_pos++);
	p[0] = at(m_pos++);

	return ret;
}

int LkStream::read8Bytes(double &var)
{
	int ret = E_SUCCESS;
	if (left() < (int)sizeof(var)) {
		return E_SPACE_NOT_ENOUGH;
	}

	char *p = (char*)&var;
	p[7] = at(m_pos++);
	p[6] = at(m_pos++);
	p[5] = at(m_pos++);
	p[4] = at(m_pos++);
	p[3] = at(m_pos++);
	p[2] = at(m_pos++);
	p[1] = at(m_pos++);
	p[0] = at(m_pos++);

	return ret;
}

int LkStream::readString(mint16 len, LkString &var)
{
	int ret = E_SUCCESS;
	if (left() < (int)len) {
		return E_SPACE_NOT_ENOUGH;
	}

	var = substr(m_pos, len);
	m_pos += len;

	return ret;
}

int LkStream::left()
{
	return size() - m_pos;
}

int LkStream::skip(int len)
{
	int temp = m_pos;
	temp += len;
	if (temp >= (int)size() || temp < 0) {
		return E_STREAM_SKIP_ERROR;
	}
	m_pos = temp;

	return E_SUCCESS;
}

void LkStream::reset()
{
	m_pos = 0;
}

bool LkStream::end()
{
	return m_pos == (int)size();
}

int LkStream::pos()
{
	return m_pos;
}

void LkStream::print(int len)
{
	unsigned char *d = (unsigned char*)data() + m_pos;
	for (int i = 0; i < len; ++i) {
		printf("%02x  ", d[i]);
	}
	printf("\n");
	fflush(stdout);
}
