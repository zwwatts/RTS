/****************************************************************************
** Meta object code from reading C++ file 'videoupdater.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../serverui/videoupdater.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videoupdater.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VideoUpdater[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   14,   13,   13, 0x05,
      39,   13,   13,   13, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_VideoUpdater[] = {
    "VideoUpdater\0\0img\0sendNewFrame(QImage)\0"
    "vidUp()\0"
};

void VideoUpdater::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VideoUpdater *_t = static_cast<VideoUpdater *>(_o);
        switch (_id) {
        case 0: _t->sendNewFrame((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->vidUp(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData VideoUpdater::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VideoUpdater::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VideoUpdater,
      qt_meta_data_VideoUpdater, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VideoUpdater::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VideoUpdater::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VideoUpdater::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VideoUpdater))
        return static_cast<void*>(const_cast< VideoUpdater*>(this));
    return QObject::qt_metacast(_clname);
}

int VideoUpdater::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void VideoUpdater::sendNewFrame(QImage _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VideoUpdater::vidUp()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
