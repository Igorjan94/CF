/****************************************************************************
** Meta object code from reading C++ file 'vk.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "vk.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vk.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Vk_t {
    QByteArrayData data[13];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Vk_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Vk_t qt_meta_stringdata_Vk = {
    {
QT_MOC_LITERAL(0, 0, 2), // "Vk"
QT_MOC_LITERAL(1, 3, 8), // "onReturn"
QT_MOC_LITERAL(2, 12, 0), // ""
QT_MOC_LITERAL(3, 13, 19), // "onItemDoubleClicked"
QT_MOC_LITERAL(4, 33, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(5, 50, 4), // "item"
QT_MOC_LITERAL(6, 55, 20), // "proceedUnreadDialogs"
QT_MOC_LITERAL(7, 76, 13), // "keyPressEvent"
QT_MOC_LITERAL(8, 90, 10), // "QKeyEvent*"
QT_MOC_LITERAL(9, 101, 5), // "event"
QT_MOC_LITERAL(10, 107, 11), // "changeEvent"
QT_MOC_LITERAL(11, 119, 7), // "QEvent*"
QT_MOC_LITERAL(12, 127, 1) // "e"

    },
    "Vk\0onReturn\0\0onItemDoubleClicked\0"
    "QListWidgetItem*\0item\0proceedUnreadDialogs\0"
    "keyPressEvent\0QKeyEvent*\0event\0"
    "changeEvent\0QEvent*\0e"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Vk[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    1,   40,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,
       7,    1,   44,    2, 0x0a /* Public */,
      10,    1,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void Vk::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Vk *_t = static_cast<Vk *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onReturn(); break;
        case 1: _t->onItemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->proceedUnreadDialogs(); break;
        case 3: _t->keyPressEvent((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 4: _t->changeEvent((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Vk::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Vk.data,
      qt_meta_data_Vk,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Vk::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Vk::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Vk.stringdata0))
        return static_cast<void*>(const_cast< Vk*>(this));
    return QWidget::qt_metacast(_clname);
}

int Vk::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
