/****************************************************************************
** Meta object code from reading C++ file 'liveonline.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../liveonline.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'liveonline.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LiveOnLine_t {
    QByteArrayData data[12];
    char stringdata[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LiveOnLine_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LiveOnLine_t qt_meta_stringdata_LiveOnLine = {
    {
QT_MOC_LITERAL(0, 0, 10), // "LiveOnLine"
QT_MOC_LITERAL(1, 11, 15), // "OnActionAddText"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 16), // "OnActionAddImage"
QT_MOC_LITERAL(4, 45, 17), // "OnActionAddCamera"
QT_MOC_LITERAL(5, 63, 18), // "OnActionAddDesktop"
QT_MOC_LITERAL(6, 82, 20), // "OnActionAddVideoFile"
QT_MOC_LITERAL(7, 103, 22), // "OnActionStartorEndRtmp"
QT_MOC_LITERAL(8, 126, 15), // "OnActionSetting"
QT_MOC_LITERAL(9, 142, 17), // "OnShowCurrentTime"
QT_MOC_LITERAL(10, 160, 12), // "MouseMovePos"
QT_MOC_LITERAL(11, 173, 2) // "pt"

    },
    "LiveOnLine\0OnActionAddText\0\0"
    "OnActionAddImage\0OnActionAddCamera\0"
    "OnActionAddDesktop\0OnActionAddVideoFile\0"
    "OnActionStartorEndRtmp\0OnActionSetting\0"
    "OnShowCurrentTime\0MouseMovePos\0pt"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LiveOnLine[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    0,   64,    2, 0x0a /* Public */,
       8,    0,   65,    2, 0x0a /* Public */,
       9,    1,   66,    2, 0x0a /* Public */,
      10,    1,   69,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QPoint,   11,

       0        // eod
};

void LiveOnLine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LiveOnLine *_t = static_cast<LiveOnLine *>(_o);
        switch (_id) {
        case 0: _t->OnActionAddText(); break;
        case 1: _t->OnActionAddImage(); break;
        case 2: _t->OnActionAddCamera(); break;
        case 3: _t->OnActionAddDesktop(); break;
        case 4: _t->OnActionAddVideoFile(); break;
        case 5: _t->OnActionStartorEndRtmp(); break;
        case 6: _t->OnActionSetting(); break;
        case 7: _t->OnShowCurrentTime((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->MouseMovePos((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject LiveOnLine::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LiveOnLine.data,
      qt_meta_data_LiveOnLine,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LiveOnLine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LiveOnLine::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LiveOnLine.stringdata))
        return static_cast<void*>(const_cast< LiveOnLine*>(this));
    return QWidget::qt_metacast(_clname);
}

int LiveOnLine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
struct qt_meta_stringdata_ShowTime_t {
    QByteArrayData data[4];
    char stringdata[26];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ShowTime_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ShowTime_t qt_meta_stringdata_ShowTime = {
    {
QT_MOC_LITERAL(0, 0, 8), // "ShowTime"
QT_MOC_LITERAL(1, 9, 11), // "currentTime"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 3) // "str"

    },
    "ShowTime\0currentTime\0\0str"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShowTime[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void ShowTime::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ShowTime *_t = static_cast<ShowTime *>(_o);
        switch (_id) {
        case 0: _t->currentTime((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ShowTime::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShowTime::currentTime)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject ShowTime::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ShowTime.data,
      qt_meta_data_ShowTime,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ShowTime::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShowTime::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ShowTime.stringdata))
        return static_cast<void*>(const_cast< ShowTime*>(this));
    return QThread::qt_metacast(_clname);
}

int ShowTime::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ShowTime::currentTime(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
