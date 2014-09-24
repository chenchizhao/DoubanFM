/****************************************************************************
** Meta object code from reading C++ file 'doubanfm.h'
**
** Created: Wed Sep 24 20:06:39 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "doubanfm.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'doubanfm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DoubanFM[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x08,
      34,    9,    9,    9, 0x08,
      56,    9,    9,    9, 0x08,
      76,    9,    9,    9, 0x08,
     111,    9,    9,    9, 0x08,
     145,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DoubanFM[] = {
    "DoubanFM\0\0favoriteButtonClicked()\0"
    "forgetButtonClicked()\0nextButtonClicked()\0"
    "onReceivedChannels(QNetworkReply*)\0"
    "onReceivedNewList(QNetworkReply*)\0"
    "enqueueNextSource()\0"
};

const QMetaObject DoubanFM::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DoubanFM,
      qt_meta_data_DoubanFM, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DoubanFM::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DoubanFM::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DoubanFM::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DoubanFM))
        return static_cast<void*>(const_cast< DoubanFM*>(this));
    return QDialog::qt_metacast(_clname);
}

int DoubanFM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: favoriteButtonClicked(); break;
        case 1: forgetButtonClicked(); break;
        case 2: nextButtonClicked(); break;
        case 3: onReceivedChannels((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: onReceivedNewList((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 5: enqueueNextSource(); break;
        default: ;
        }
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
