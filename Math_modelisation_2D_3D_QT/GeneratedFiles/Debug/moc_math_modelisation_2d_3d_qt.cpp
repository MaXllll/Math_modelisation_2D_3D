/****************************************************************************
** Meta object code from reading C++ file 'math_modelisation_2d_3d_qt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../math_modelisation_2d_3d_qt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'math_modelisation_2d_3d_qt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Math_modelisation_2D_3D_QT_t {
    QByteArrayData data[11];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Math_modelisation_2D_3D_QT_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Math_modelisation_2D_3D_QT_t qt_meta_stringdata_Math_modelisation_2D_3D_QT = {
    {
QT_MOC_LITERAL(0, 0, 26), // "Math_modelisation_2D_3D_QT"
QT_MOC_LITERAL(1, 27, 10), // "newBSpline"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 5), // "clear"
QT_MOC_LITERAL(4, 45, 15), // "createPointMode"
QT_MOC_LITERAL(5, 61, 13), // "movePointMode"
QT_MOC_LITERAL(6, 75, 15), // "repeatPointMode"
QT_MOC_LITERAL(7, 91, 11), // "BSplineMode"
QT_MOC_LITERAL(8, 103, 13), // "ExtrusionMode"
QT_MOC_LITERAL(9, 117, 12), // "BSurfaceMode"
QT_MOC_LITERAL(10, 130, 13) // "WireFrameMode"

    },
    "Math_modelisation_2D_3D_QT\0newBSpline\0"
    "\0clear\0createPointMode\0movePointMode\0"
    "repeatPointMode\0BSplineMode\0ExtrusionMode\0"
    "BSurfaceMode\0WireFrameMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Math_modelisation_2D_3D_QT[] = {

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
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
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

void Math_modelisation_2D_3D_QT::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Math_modelisation_2D_3D_QT *_t = static_cast<Math_modelisation_2D_3D_QT *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->newBSpline(); break;
        case 1: _t->clear(); break;
        case 2: _t->createPointMode(); break;
        case 3: _t->movePointMode(); break;
        case 4: _t->repeatPointMode(); break;
        case 5: _t->BSplineMode(); break;
        case 6: _t->ExtrusionMode(); break;
        case 7: _t->BSurfaceMode(); break;
        case 8: _t->WireFrameMode(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Math_modelisation_2D_3D_QT::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Math_modelisation_2D_3D_QT.data,
      qt_meta_data_Math_modelisation_2D_3D_QT,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Math_modelisation_2D_3D_QT::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Math_modelisation_2D_3D_QT::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Math_modelisation_2D_3D_QT.stringdata0))
        return static_cast<void*>(const_cast< Math_modelisation_2D_3D_QT*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Math_modelisation_2D_3D_QT::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
