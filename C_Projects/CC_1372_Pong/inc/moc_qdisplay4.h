/****************************************************************************
** Meta object code from reading C++ file 'qdisplay.h'
**
** Created: Sat Nov 15 09:01:19 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qdisplay.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdisplay.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QDisplay[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_QDisplay[] = {
    "QDisplay\0\0timerDone()\0"
};

const QMetaObject QDisplay::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QDisplay,
      qt_meta_data_QDisplay, 0 }
};

const QMetaObject *QDisplay::metaObject() const
{
    return &staticMetaObject;
}

void *QDisplay::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QDisplay))
	return static_cast<void*>(const_cast< QDisplay*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QDisplay::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: timerDone(); break;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
