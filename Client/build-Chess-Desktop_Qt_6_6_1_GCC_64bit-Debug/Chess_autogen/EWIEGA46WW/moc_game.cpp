/****************************************************************************
** Meta object code from reading C++ file 'game.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../Chess/game.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'game.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSgameENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSgameENDCLASS = QtMocHelpers::stringData(
    "game",
    "chessSquareClicked",
    "",
    "row",
    "col",
    "on_btnDraw_clicked",
    "on_btnYes_clicked",
    "on_btnNo_clicked",
    "on_btnResign_clicked",
    "on_btnPrQueen_clicked",
    "on_btnPrKnight_clicked",
    "on_btnPrRook_clicked",
    "on_btnPrBishop_clicked",
    "on_btnBack_clicked",
    "onBtnYes2Clicked",
    "onBtnNo2Clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSgameENDCLASS_t {
    uint offsetsAndSizes[32];
    char stringdata0[5];
    char stringdata1[19];
    char stringdata2[1];
    char stringdata3[4];
    char stringdata4[4];
    char stringdata5[19];
    char stringdata6[18];
    char stringdata7[17];
    char stringdata8[21];
    char stringdata9[22];
    char stringdata10[23];
    char stringdata11[21];
    char stringdata12[23];
    char stringdata13[19];
    char stringdata14[17];
    char stringdata15[16];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSgameENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSgameENDCLASS_t qt_meta_stringdata_CLASSgameENDCLASS = {
    {
        QT_MOC_LITERAL(0, 4),  // "game"
        QT_MOC_LITERAL(5, 18),  // "chessSquareClicked"
        QT_MOC_LITERAL(24, 0),  // ""
        QT_MOC_LITERAL(25, 3),  // "row"
        QT_MOC_LITERAL(29, 3),  // "col"
        QT_MOC_LITERAL(33, 18),  // "on_btnDraw_clicked"
        QT_MOC_LITERAL(52, 17),  // "on_btnYes_clicked"
        QT_MOC_LITERAL(70, 16),  // "on_btnNo_clicked"
        QT_MOC_LITERAL(87, 20),  // "on_btnResign_clicked"
        QT_MOC_LITERAL(108, 21),  // "on_btnPrQueen_clicked"
        QT_MOC_LITERAL(130, 22),  // "on_btnPrKnight_clicked"
        QT_MOC_LITERAL(153, 20),  // "on_btnPrRook_clicked"
        QT_MOC_LITERAL(174, 22),  // "on_btnPrBishop_clicked"
        QT_MOC_LITERAL(197, 18),  // "on_btnBack_clicked"
        QT_MOC_LITERAL(216, 16),  // "onBtnYes2Clicked"
        QT_MOC_LITERAL(233, 15)   // "onBtnNo2Clicked"
    },
    "game",
    "chessSquareClicked",
    "",
    "row",
    "col",
    "on_btnDraw_clicked",
    "on_btnYes_clicked",
    "on_btnNo_clicked",
    "on_btnResign_clicked",
    "on_btnPrQueen_clicked",
    "on_btnPrKnight_clicked",
    "on_btnPrRook_clicked",
    "on_btnPrBishop_clicked",
    "on_btnBack_clicked",
    "onBtnYes2Clicked",
    "onBtnNo2Clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSgameENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    2,   86,    2, 0x0a,    1 /* Public */,
       5,    0,   91,    2, 0x08,    4 /* Private */,
       6,    0,   92,    2, 0x08,    5 /* Private */,
       7,    0,   93,    2, 0x08,    6 /* Private */,
       8,    0,   94,    2, 0x08,    7 /* Private */,
       9,    0,   95,    2, 0x08,    8 /* Private */,
      10,    0,   96,    2, 0x08,    9 /* Private */,
      11,    0,   97,    2, 0x08,   10 /* Private */,
      12,    0,   98,    2, 0x08,   11 /* Private */,
      13,    0,   99,    2, 0x08,   12 /* Private */,
      14,    0,  100,    2, 0x08,   13 /* Private */,
      15,    0,  101,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,
    QMetaType::Void,
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

Q_CONSTINIT const QMetaObject game::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSgameENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSgameENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSgameENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<game, std::true_type>,
        // method 'chessSquareClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'on_btnDraw_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnYes_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnNo_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnResign_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnPrQueen_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnPrKnight_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnPrRook_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnPrBishop_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_btnBack_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onBtnYes2Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onBtnNo2Clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void game::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<game *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->chessSquareClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 1: _t->on_btnDraw_clicked(); break;
        case 2: _t->on_btnYes_clicked(); break;
        case 3: _t->on_btnNo_clicked(); break;
        case 4: _t->on_btnResign_clicked(); break;
        case 5: _t->on_btnPrQueen_clicked(); break;
        case 6: _t->on_btnPrKnight_clicked(); break;
        case 7: _t->on_btnPrRook_clicked(); break;
        case 8: _t->on_btnPrBishop_clicked(); break;
        case 9: _t->on_btnBack_clicked(); break;
        case 10: _t->onBtnYes2Clicked(); break;
        case 11: _t->onBtnNo2Clicked(); break;
        default: ;
        }
    }
}

const QMetaObject *game::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *game::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSgameENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int game::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
