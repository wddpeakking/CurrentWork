#ifndef _LK_SOURCEABS_H_
#define _LK_SOURCEABS_H_

#include <QString>
#include <QRect>

#define LkImage_Format_Invalid         -1
#define LkImage_Format_RGB24           0x01
#define LkImage_Format_BGR24           0x02
#define LkImage_Format_RGB32           0x03
#define LkImage_Format_YUV420          0x04

struct LkImage
{
	qint64 pts;
	int width;
	int height;

	int format;

	int dataSize;
	char *data;
	int *ref;

	LkImage();
	~LkImage();

	LkImage & operator=(LkImage & other);
	LkImage(const LkImage & other);

	LkImage clone();

	int addRef();
	int deRef();

	void destory();    

private:
	void init();
};

class LkSourceAbstract;
struct SourcePair {
	LkSourceAbstract *source;
	QRect rect;

	bool operator ==(const SourcePair & other) {
		return source == other.source;
	}
};

class LkSourceAbstract
{
public:
	LkSourceAbstract();
	virtual ~LkSourceAbstract();

	virtual LkImage getImage();
	virtual void stopCapture();
	virtual void setCaptureInterval(int interval);
};

#endif // LkSourceAbstract_HPP
