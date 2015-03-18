/****************************************************************************
** Meta object code from reading C++ file 'LkSettingDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../LkSettingDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LkSettingDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LkSettingDlg_t {
    QByteArrayData data[8];
    char stringdata[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LkSettingDlg_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LkSettingDlg_t qt_meta_stringdata_LkSettingDlg = {
    {
QT_MOC_LITERAL(0, 0, 12), // "LkSettingDlg"
QT_MOC_LITERAL(1, 13, 12), // "OnActionMore"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "OnActionBack"
QT_MOC_LITERAL(4, 40, 10), // "OnActionOk"
QT_MOC_LITERAL(5, 51, 24), // "OnActionMLLXSelectChange"
QT_MOC_LITERAL(6, 76, 15), // "OnCheckSaveFlie"
QT_MOC_LITERAL(7, 92, 22) // "OnActionSaveFlieSelect"

    },
    "LkSettingDlg\0OnActionMore\0\0OnActionBack\0"
    "OnActionOk\0OnActionMLLXSelectChange\0"
    "OnCheckSaveFlie\0OnActionSaveFlieSelect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LkSettingDlg[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    1,   47,    2, 0x08 /* Private */,
       6,    0,   50,    2, 0x08 /* Private */,
       7,    0,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LkSettingDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LkSettingDlg *_t = static_cast<LkSettingDlg *>(_o);
        switch (_id) {
        case 0: _t->OnActionMore(); break;
        case 1: _t->OnActionBack(); break;
        case 2: _t->OnActionOk(); break;
        case 3: _t->OnActionMLLXSelectChange((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->OnCheckSaveFlie(); break;
        case 5: _t->OnActionSaveFlieSelect(); break;
        default: ;
        }
    }
}

const QMetaObject LkSettingDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LkSettingDlg.data,
      qt_meta_data_LkSettingDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LkSettingDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LkSettingDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LkSettingDlg.stringdata))
        return static_cast<void*>(const_cast< LkSettingDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int LkSettingDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
