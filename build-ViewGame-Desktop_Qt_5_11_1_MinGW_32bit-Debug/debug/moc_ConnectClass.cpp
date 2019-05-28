/****************************************************************************
** Meta object code from reading C++ file 'ConnectClass.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ViewGame/ConnectClass.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConnectClass.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConnectClass_t {
    QByteArrayData data[7];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConnectClass_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConnectClass_t qt_meta_stringdata_ConnectClass = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ConnectClass"
QT_MOC_LITERAL(1, 13, 23), // "slotInfoConnectToServer"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 23), // "slotReconnectedToServer"
QT_MOC_LITERAL(4, 62, 8), // "slotTest"
QT_MOC_LITERAL(5, 71, 11), // "slotMessage"
QT_MOC_LITERAL(6, 83, 7) // "Message"

    },
    "ConnectClass\0slotInfoConnectToServer\0"
    "\0slotReconnectedToServer\0slotTest\0"
    "slotMessage\0Message"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConnectClass[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x08 /* Private */,
       3,    0,   37,    2, 0x08 /* Private */,
       4,    1,   38,    2, 0x08 /* Private */,
       5,    1,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 6,    2,

       0        // eod
};

void ConnectClass::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConnectClass *_t = static_cast<ConnectClass *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotInfoConnectToServer((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->slotReconnectedToServer(); break;
        case 2: _t->slotTest((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->slotMessage((*reinterpret_cast< const Message(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ConnectClass::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ConnectClass.data,
      qt_meta_data_ConnectClass,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ConnectClass::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConnectClass::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectClass.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ConnectClass::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
