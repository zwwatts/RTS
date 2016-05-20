/****************************************************************************
** Meta object code from reading C++ file 'videowindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../serverui/videowindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videowindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_VideoWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      20,   12,   12,   12, 0x08,
      28,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_VideoWindow[] = {
    "VideoWindow\0\0open()\0print()\0fitToWindow()\0"
};

void VideoWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        VideoWindow *_t = static_cast<VideoWindow *>(_o);
        switch (_id) {
        case 0: _t->open(); break;
        case 1: _t->print(); break;
        case 2: _t->fitToWindow(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData VideoWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject VideoWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VideoWindow,
      qt_meta_data_VideoWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &VideoWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *VideoWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *VideoWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VideoWindow))
        return static_cast<void*>(const_cast< VideoWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int VideoWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
