#pragma once

#ifndef _LK_UTIL_H_
#define _LK_UTIL_H_

#include <assert.h>
#include <QMutexLocker>

#include "LkLog.h"

#define LkFree(ptr) \
	do { if (ptr) { delete ptr; ptr = NULL;} } while (0)

#define LkFreeArray(ptr) \
	do { if (ptr) { delete [] ptr; ptr = NULL;} } while (0)

#define LkAutoLocker(mutex) QMutexLocker locker(&mutex)

#define LkAssert(x) do { assert(x); } while (0)

// from srs
template<class T>
class LkAutoFree
{
private:
	T **ptr;
	bool is_array;
public:
	LkAutoFree(T **_ptr, bool _is_array) {
		ptr = _ptr;
		is_array = _is_array;
	}

	virtual ~LkAutoFree() {
		if (ptr == NULL || *ptr == NULL) {
			return;
		}

		if (is_array) {
			delete[] *ptr;
		} else {
			delete *ptr;
		}

		*ptr = NULL;
	}
};

#define LkAutoFree(className, instance) \
	LkAutoFree<className> LkAutoFree##instance(&instance, false)

#define LkAutoFreeArray(className, instance) \
	LkAutoFreeArray<className> LkAutoFree##instance(&instance, true)

#define SAFE_STOP_THREAD(thread) \
	do { \
	if (thread && thread->isRunning()) { thread->stop(); thread->wait(); } \
	} while (0)

#define START_THREAD(thread) \
	do { \
	if (!thread->isRunning()) { thread->start(); } \
	} while (0)

#endif // BLEUTIL_H
