/****************************************************************************
** Meta object code from reading C++ file 'KakaInterface.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/kaka_interface_pkg/src/KakaInterface.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'KakaInterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_kaka_interface_pkg__KakaInterface[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      35,   34,   34,   34, 0x0a,
      60,   34,   34,   34, 0x0a,
      84,   34,   34,   34, 0x0a,
     110,   34,   34,   34, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_kaka_interface_pkg__KakaInterface[] = {
    "kaka_interface_pkg::KakaInterface\0\0"
    "on_StartButton_clicked()\0"
    "on_StopButton_clicked()\0"
    "on_SampleButton_clicked()\0"
    "on_CalculateButton_clicked()\0"
};

void kaka_interface_pkg::KakaInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        KakaInterface *_t = static_cast<KakaInterface *>(_o);
        switch (_id) {
        case 0: _t->on_StartButton_clicked(); break;
        case 1: _t->on_StopButton_clicked(); break;
        case 2: _t->on_SampleButton_clicked(); break;
        case 3: _t->on_CalculateButton_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData kaka_interface_pkg::KakaInterface::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject kaka_interface_pkg::KakaInterface::staticMetaObject = {
    { &rviz::Panel::staticMetaObject, qt_meta_stringdata_kaka_interface_pkg__KakaInterface,
      qt_meta_data_kaka_interface_pkg__KakaInterface, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &kaka_interface_pkg::KakaInterface::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *kaka_interface_pkg::KakaInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *kaka_interface_pkg::KakaInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_kaka_interface_pkg__KakaInterface))
        return static_cast<void*>(const_cast< KakaInterface*>(this));
    typedef rviz::Panel QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int kaka_interface_pkg::KakaInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef rviz::Panel QMocSuperClass;
    _id = QMocSuperClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
