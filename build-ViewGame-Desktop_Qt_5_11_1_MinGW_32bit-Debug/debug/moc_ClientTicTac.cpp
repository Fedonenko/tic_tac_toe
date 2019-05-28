/****************************************************************************
** Meta object code from reading C++ file 'ClientTicTac.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ViewGame/ClientTicTac.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClientTicTac.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClientTicTac_t {
    QByteArrayData data[11];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientTicTac_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientTicTac_t qt_meta_stringdata_ClientTicTac = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ClientTicTac"
QT_MOC_LITERAL(1, 13, 19), // "infoConnectToServer"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 6), // "tested"
QT_MOC_LITERAL(4, 41, 7), // "message"
QT_MOC_LITERAL(5, 49, 7), // "Message"
QT_MOC_LITERAL(6, 57, 13), // "slotReadyRead"
QT_MOC_LITERAL(7, 71, 9), // "slotError"
QT_MOC_LITERAL(8, 81, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(9, 110, 16), // "slotSendToServer"
QT_MOC_LITERAL(10, 127, 11) // "slotConnect"

    },
    "ClientTicTac\0infoConnectToServer\0\0"
    "tested\0message\0Message\0slotReadyRead\0"
    "slotError\0QAbstractSocket::SocketError\0"
    "slotSendToServer\0slotConnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientTicTac[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       3,    1,   52,    2, 0x06 /* Public */,
       4,    1,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   58,    2, 0x08 /* Private */,
       7,    1,   59,    2, 0x08 /* Private */,
       9,    0,   62,    2, 0x08 /* Private */,
      10,    0,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ClientTicTac::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientTicTac *_t = static_cast<ClientTicTac *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->infoConnectToServer((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->tested((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->message((*reinterpret_cast< const Message(*)>(_a[1]))); break;
        case 3: _t->slotReadyRead(); break;
        case 4: _t->slotError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: _t->slotSendToServer(); break;
        case 6: _t->slotConnect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ClientTicTac::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientTicTac::infoConnectToServer)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ClientTicTac::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientTicTac::tested)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ClientTicTac::*)(const Message & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientTicTac::message)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ClientTicTac::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ClientTicTac.data,
      qt_meta_data_ClientTicTac,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ClientTicTac::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientTicTac::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClientTicTac.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ClientTicTac::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ClientTicTac::infoConnectToServer(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClientTicTac::tested(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ClientTicTac::message(const Message & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
