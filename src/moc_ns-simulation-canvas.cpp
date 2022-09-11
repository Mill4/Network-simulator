/****************************************************************************
** Meta object code from reading C++ file 'ns-simulation-canvas.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "frontend/components/ns-simulation-canvas.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ns-simulation-canvas.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NsSimulationCanvas_t {
    const uint offsetsAndSize[28];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_NsSimulationCanvas_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_NsSimulationCanvas_t qt_meta_stringdata_NsSimulationCanvas = {
    {
QT_MOC_LITERAL(0, 18), // "NsSimulationCanvas"
QT_MOC_LITERAL(19, 7), // "setMode"
QT_MOC_LITERAL(27, 0), // ""
QT_MOC_LITERAL(28, 6), // "NsMode"
QT_MOC_LITERAL(35, 6), // "nsMode"
QT_MOC_LITERAL(42, 16), // "insertedItemType"
QT_MOC_LITERAL(59, 15), // "NetworkItemType"
QT_MOC_LITERAL(75, 4), // "type"
QT_MOC_LITERAL(80, 13), // "runSimulation"
QT_MOC_LITERAL(94, 10), // "deleteItem"
QT_MOC_LITERAL(105, 3), // "Run"
QT_MOC_LITERAL(109, 10), // "Simulator*"
QT_MOC_LITERAL(120, 1), // "s"
QT_MOC_LITERAL(122, 11) // "clearCanvas"

    },
    "NsSimulationCanvas\0setMode\0\0NsMode\0"
    "nsMode\0insertedItemType\0NetworkItemType\0"
    "type\0runSimulation\0deleteItem\0Run\0"
    "Simulator*\0s\0clearCanvas"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NsSimulationCanvas[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x0a,    1 /* Public */,
       5,    1,   53,    2, 0x0a,    3 /* Public */,
       8,    0,   56,    2, 0x0a,    5 /* Public */,
       9,    0,   57,    2, 0x0a,    6 /* Public */,
      10,    1,   58,    2, 0x0a,    7 /* Public */,
      13,    0,   61,    2, 0x0a,    9 /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,

       0        // eod
};

void NsSimulationCanvas::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NsSimulationCanvas *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setMode((*reinterpret_cast< NsMode(*)>(_a[1]))); break;
        case 1: _t->insertedItemType((*reinterpret_cast< NetworkItemType(*)>(_a[1]))); break;
        case 2: _t->runSimulation(); break;
        case 3: _t->deleteItem(); break;
        case 4: _t->Run((*reinterpret_cast< Simulator*(*)>(_a[1]))); break;
        case 5: _t->clearCanvas(); break;
        default: ;
        }
    }
}

const QMetaObject NsSimulationCanvas::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsScene::staticMetaObject>(),
    qt_meta_stringdata_NsSimulationCanvas.offsetsAndSize,
    qt_meta_data_NsSimulationCanvas,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_NsSimulationCanvas_t
, QtPrivate::TypeAndForceComplete<NsSimulationCanvas, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<NsMode, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<NetworkItemType, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Simulator *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *NsSimulationCanvas::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NsSimulationCanvas::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NsSimulationCanvas.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int NsSimulationCanvas::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
