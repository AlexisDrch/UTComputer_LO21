/****************************************************************************
** Meta object code from reading C++ file 'qcomputer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../UT_Computer/qcomputer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qcomputer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QComputer_t {
    QByteArrayData data[12];
    char stringdata0[126];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QComputer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QComputer_t qt_meta_stringdata_QComputer = {
    {
QT_MOC_LITERAL(0, 0, 9), // "QComputer"
QT_MOC_LITERAL(1, 10, 15), // "setCommandeText"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "hideClavier1"
QT_MOC_LITERAL(4, 40, 11), // "setVuePrinc"
QT_MOC_LITERAL(5, 52, 9), // "setVueVar"
QT_MOC_LITERAL(6, 62, 10), // "setVueProg"
QT_MOC_LITERAL(7, 73, 10), // "setVuePara"
QT_MOC_LITERAL(8, 84, 7), // "refresh"
QT_MOC_LITERAL(9, 92, 15), // "getNextCommande"
QT_MOC_LITERAL(10, 108, 15), // "changeNbAffiche"
QT_MOC_LITERAL(11, 124, 1) // "i"

    },
    "QComputer\0setCommandeText\0\0hideClavier1\0"
    "setVuePrinc\0setVueVar\0setVueProg\0"
    "setVuePara\0refresh\0getNextCommande\0"
    "changeNbAffiche\0i"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QComputer[] = {

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
       1,    1,   59,    2, 0x0a /* Public */,
       3,    0,   62,    2, 0x0a /* Public */,
       4,    0,   63,    2, 0x0a /* Public */,
       5,    0,   64,    2, 0x0a /* Public */,
       6,    0,   65,    2, 0x0a /* Public */,
       7,    0,   66,    2, 0x0a /* Public */,
       8,    0,   67,    2, 0x0a /* Public */,
       9,    0,   68,    2, 0x0a /* Public */,
      10,    1,   69,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,

       0        // eod
};

void QComputer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QComputer *_t = static_cast<QComputer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setCommandeText((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->hideClavier1(); break;
        case 2: _t->setVuePrinc(); break;
        case 3: _t->setVueVar(); break;
        case 4: _t->setVueProg(); break;
        case 5: _t->setVuePara(); break;
        case 6: _t->refresh(); break;
        case 7: _t->getNextCommande(); break;
        case 8: _t->changeNbAffiche((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QComputer::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QComputer.data,
      qt_meta_data_QComputer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QComputer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QComputer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QComputer.stringdata0))
        return static_cast<void*>(const_cast< QComputer*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QComputer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
