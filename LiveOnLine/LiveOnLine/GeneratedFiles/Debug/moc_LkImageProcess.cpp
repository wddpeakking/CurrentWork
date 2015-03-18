/****************************************************************************
** Meta object code from reading C++ file 'LkImageProcess.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LkImageProcess.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LkImageProcess.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LkImageProcessWidget_t {
    QByteArrayData data[10];
    char stringdata[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LkImageProcessWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LkImageProcessWidget_t qt_meta_stringdata_LkImageProcessWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "LkImageProcessWidget"
QT_MOC_LITERAL(1, 21, 15), // "onIncBtnClicked"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 15), // "onDecBtnClicked"
QT_MOC_LITERAL(4, 54, 14), // "onUpBtnClicked"
QT_MOC_LITERAL(5, 69, 16), // "onDownBtnClicked"
QT_MOC_LITERAL(6, 86, 16), // "onLeftBtnClicked"
QT_MOC_LITERAL(7, 103, 17), // "onRightBtnClicked"
QT_MOC_LITERAL(8, 121, 16), // "onRefreshTimeout"
QT_MOC_LITERAL(9, 138, 16) // "onSettingChanged"

    },
    "LkImageProcessWidget\0onIncBtnClicked\0"
    "\0onDecBtnClicked\0onUpBtnClicked\0"
    "onDownBtnClicked\0onLeftBtnClicked\0"
    "onRightBtnClicked\0onRefreshTimeout\0"
    "onSettingChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LkImageProcessWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LkImageProcessWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LkImageProcessWidget *_t = static_cast<LkImageProcessWidget *>(_o);
        switch (_id) {
        case 0: _t->onIncBtnClicked(); break;
        case 1: _t->onDecBtnClicked(); break;
        case 2: _t->onUpBtnClicked(); break;
        case 3: _t->onDownBtnClicked(); break;
        case 4: _t->onLeftBtnClicked(); break;
        case 5: _t->onRightBtnClicked(); break;
        case 6: _t->onRefreshTimeout(); break;
        case 7: _t->onSettingChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject LkImageProcessWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LkImageProcessWidget.data,
      qt_meta_data_LkImageProcessWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LkImageProcessWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LkImageProcessWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LkImageProcessWidget.stringdata))
        return static_cast<void*>(const_cast< LkImageProcessWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int LkImageProcessWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
