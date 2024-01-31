/****************************************************************************
** Meta object code from reading C++ file 'play.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Chess/play.h"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'play.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSplayENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSplayENDCLASS = QtMocHelpers::stringData(
    "play",
    "on_btnRefresh_clicked",
    "",
    "on_btnBack_clicked",
    "on_btnInvite_clicked",
    "on_btnMM_clicked",
    "on_btnNo_clicked",
    "on_btnYes_clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSplayENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[5];
    char stringdata1[22];
    char stringdata2[1];
    char stringdata3[19];
    char stringdata4[21];
    char stringdata5[17];
    char stringdata6[17];
    char stringdata7[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSplayENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSplayENDCLASS_t qt_meta_stringdata_CLASSplayENDCLASS = {
    {
        QT_MOC_LITERAL(0, 4),  // "play"
        QT_MOC_LITERAL(5, 21),  // "on_btnRefresh_clicked"
        QT_MOC_LITERAL(27, 0),  // ""
        QT_MOC_LITERAL(28, 18),  // "on_btnBack_clicked"
        QT_MOC_LITERAL(47, 20),  // "on_btnInvite_clicked"
        QT_MOC_LITERAL(68, 16),  // "on_btnMM_clicked"
        QT_MOC_LITERAL(85, 16),  // "on_btnNo_clicked"
        QT_MOC_LITERAL(102, 17)   // "on_btnYes_clicked"
    },
    "play",
    "on_btnRefresh_clicked",
    "",
    "on_btnBack_clicked",
    "on_btnInvite_clicked",
    "on_btnMM_clicked",
    "on_btnNo_clicked",
    "on_btnYes_clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSplayENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x08,    1 /* Private */,
       3,    0,   51,    2, 0x08,    2 /* Private */,
       4,    0,   52,    2, 0x08,    3 /* Private */,
       5,    0,   53,    2, 0x08,    4 /* Private */,
       6,    0,   54,    2, 0x08,    5 /* Private */,
       7,    0,   55,    2, 0x08,    6 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject play::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSplayENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSplayENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSplayENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<play, std::true_type>,
        // method 'on_btnRefresh_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnBack_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnInvite_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnMM_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnNo_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnYes_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void play::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<play *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_btnRefresh_clicked(); break;
        case 1: _t->on_btnBack_clicked(); break;
        case 2: _t->on_btnInvite_clicked(); break;
        case 3: _t->on_btnMM_clicked(); break;
        case 4: _t->on_btnNo_clicked(); break;
        case 5: _t->on_btnYes_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *play::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *play::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSplayENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int play::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
