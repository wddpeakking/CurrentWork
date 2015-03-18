#include "LkSourceAbstract.h"
#include "LkUtil.h"

LkImage::LkImage()
{
	init();
}

LkImage::~LkImage()
{
	if (deRef() <= 0) {
		LkFreeArray(data);
		LkFree(ref);
	}
}

LkImage &LkImage::operator=(LkImage &other)
{
	// if has data alloc and no ref, first free it.
	if (deRef() <= 0) {
		LkFreeArray(data);
		LkFree(ref);
	}

	this->pts = other.pts;
	this->width = other.width;
	this->height = other.height;
	this->format = other.format;
	this->dataSize = other.dataSize;
	this->data = other.data;
	this->ref = other.ref;

	other.addRef();

	return *this;
}

LkImage::LkImage(const LkImage &other)
{
	this->pts = other.pts;
	this->width = other.width;
	this->height = other.height;
	this->format = other.format;
	this->dataSize = other.dataSize;
	this->data = other.data;
	this->ref = other.ref;

	this->addRef();
}

LkImage LkImage::clone()
{
	LkImage image;
	image.width = width;
	image.height = height;
	image.pts = pts;
	image.format = format;

	image.data = new char[dataSize];
	memcpy(image.data, data, dataSize);

	image.dataSize = dataSize;

	return image;
}

int LkImage::addRef()
{
	*ref += 1;

	return *ref;
}

int LkImage::deRef()
{
	*ref -= 1;

	return *ref;
}

void LkImage::init()
{
	width = 0;
	height = 0;
	format = LkImage_Format_Invalid;
	dataSize = 0;
	data = NULL;
	pts = 0;

	ref = new int(0);

	addRef();
}

LkSourceAbstract::LkSourceAbstract()
{
}

LkSourceAbstract::~LkSourceAbstract()
{

}

LkImage LkSourceAbstract::getImage()
{
	return LkImage();
}

void LkSourceAbstract::stopCapture()
{

}

void LkSourceAbstract::setCaptureInterval(int interval)
{
	Q_UNUSED(interval);
}


