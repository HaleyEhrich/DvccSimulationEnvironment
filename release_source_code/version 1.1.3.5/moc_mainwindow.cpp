/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../simulation/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[86];
    char stringdata0[947];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 21), // "on_FMnewWin_triggered"
QT_MOC_LITERAL(33, 0), // ""
QT_MOC_LITERAL(34, 23), // "on_FMopenFile_triggered"
QT_MOC_LITERAL(58, 23), // "on_FMsaveFile_triggered"
QT_MOC_LITERAL(82, 21), // "on_FMeditor_triggered"
QT_MOC_LITERAL(104, 18), // "on_PMRAM_triggered"
QT_MOC_LITERAL(123, 18), // "on_PMROM_triggered"
QT_MOC_LITERAL(142, 29), // "on_OMdefaultWinSize_triggered"
QT_MOC_LITERAL(172, 21), // "on_ALUAcess_triggered"
QT_MOC_LITERAL(194, 21), // "on_RAMAcess_triggered"
QT_MOC_LITERAL(216, 22), // "on_a299Acess_triggered"
QT_MOC_LITERAL(239, 26), // "on_registerAcess_triggered"
QT_MOC_LITERAL(266, 30), // "on_microControlAcess_triggered"
QT_MOC_LITERAL(297, 19), // "on_AMInfo_triggered"
QT_MOC_LITERAL(317, 27), // "on_AMinstructions_triggered"
QT_MOC_LITERAL(345, 24), // "on_runInMicroCmd_clicked"
QT_MOC_LITERAL(370, 18), // "on_autoRun_clicked"
QT_MOC_LITERAL(389, 19), // "on_runInCmd_clicked"
QT_MOC_LITERAL(409, 18), // "on_T4pulse_clicked"
QT_MOC_LITERAL(428, 14), // "on_SWA_clicked"
QT_MOC_LITERAL(443, 14), // "on_SWC_clicked"
QT_MOC_LITERAL(458, 19), // "on_swi_LDAR_clicked"
QT_MOC_LITERAL(478, 20), // "on_swi_LDDR1_clicked"
QT_MOC_LITERAL(499, 19), // "on_swi_299B_clicked"
QT_MOC_LITERAL(519, 20), // "on_swi_LDDR2_clicked"
QT_MOC_LITERAL(540, 19), // "on_swi_LDAD_clicked"
QT_MOC_LITERAL(560, 19), // "on_swi_LDPC_clicked"
QT_MOC_LITERAL(580, 18), // "on_swi_PCB_clicked"
QT_MOC_LITERAL(599, 19), // "on_swi_ALUB_clicked"
QT_MOC_LITERAL(619, 18), // "on_swi_SWB_clicked"
QT_MOC_LITERAL(638, 17), // "on_swi_WE_clicked"
QT_MOC_LITERAL(656, 17), // "on_swi_AR_clicked"
QT_MOC_LITERAL(674, 17), // "on_swi_CE_clicked"
QT_MOC_LITERAL(692, 27), // "on_swiInput_editingFinished"
QT_MOC_LITERAL(720, 17), // "on_AR_BUT_clicked"
QT_MOC_LITERAL(738, 36), // "on_startMircoADInput_editingF..."
QT_MOC_LITERAL(775, 32), // "on_functionInput_editingFinished"
QT_MOC_LITERAL(808, 34), // "on_startMircoADInput_inputRej..."
QT_MOC_LITERAL(843, 25), // "on_swiInput_inputRejected"
QT_MOC_LITERAL(869, 30), // "on_functionInput_inputRejected"
QT_MOC_LITERAL(900, 21), // "on_FMSaveAs_triggered"
QT_MOC_LITERAL(922, 24) // "on_FMpasteFile_triggered"

    },
    "MainWindow\0on_FMnewWin_triggered\0\0"
    "on_FMopenFile_triggered\0on_FMsaveFile_triggered\0"
    "on_FMeditor_triggered\0on_PMRAM_triggered\0"
    "on_PMROM_triggered\0on_OMdefaultWinSize_triggered\0"
    "on_ALUAcess_triggered\0on_RAMAcess_triggered\0"
    "on_a299Acess_triggered\0"
    "on_registerAcess_triggered\0"
    "on_microControlAcess_triggered\0"
    "on_AMInfo_triggered\0on_AMinstructions_triggered\0"
    "on_runInMicroCmd_clicked\0on_autoRun_clicked\0"
    "on_runInCmd_clicked\0on_T4pulse_clicked\0"
    "on_SWA_clicked\0on_SWC_clicked\0"
    "on_swi_LDAR_clicked\0on_swi_LDDR1_clicked\0"
    "on_swi_299B_clicked\0on_swi_LDDR2_clicked\0"
    "on_swi_LDAD_clicked\0on_swi_LDPC_clicked\0"
    "on_swi_PCB_clicked\0on_swi_ALUB_clicked\0"
    "on_swi_SWB_clicked\0on_swi_WE_clicked\0"
    "on_swi_AR_clicked\0on_swi_CE_clicked\0"
    "on_swiInput_editingFinished\0"
    "on_AR_BUT_clicked\0"
    "on_startMircoADInput_editingFinished\0"
    "on_functionInput_editingFinished\0"
    "on_startMircoADInput_inputRejected\0"
    "on_swiInput_inputRejected\0"
    "on_functionInput_inputRejected\0"
    "on_FMSaveAs_triggered\0on_FMpasteFile_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      41,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  260,    2, 0x08,    0 /* Private */,
       3,    0,  261,    2, 0x08,    1 /* Private */,
       4,    0,  262,    2, 0x08,    2 /* Private */,
       5,    0,  263,    2, 0x08,    3 /* Private */,
       6,    0,  264,    2, 0x08,    4 /* Private */,
       7,    0,  265,    2, 0x08,    5 /* Private */,
       8,    0,  266,    2, 0x08,    6 /* Private */,
       9,    0,  267,    2, 0x08,    7 /* Private */,
      10,    0,  268,    2, 0x08,    8 /* Private */,
      11,    0,  269,    2, 0x08,    9 /* Private */,
      12,    0,  270,    2, 0x08,   10 /* Private */,
      13,    0,  271,    2, 0x08,   11 /* Private */,
      14,    0,  272,    2, 0x08,   12 /* Private */,
      15,    0,  273,    2, 0x08,   13 /* Private */,
      16,    0,  274,    2, 0x08,   14 /* Private */,
      17,    0,  275,    2, 0x08,   15 /* Private */,
      18,    0,  276,    2, 0x08,   16 /* Private */,
      19,    0,  277,    2, 0x08,   17 /* Private */,
      20,    0,  278,    2, 0x08,   18 /* Private */,
      21,    0,  279,    2, 0x08,   19 /* Private */,
      22,    0,  280,    2, 0x08,   20 /* Private */,
      23,    0,  281,    2, 0x08,   21 /* Private */,
      24,    0,  282,    2, 0x08,   22 /* Private */,
      25,    0,  283,    2, 0x08,   23 /* Private */,
      26,    0,  284,    2, 0x08,   24 /* Private */,
      27,    0,  285,    2, 0x08,   25 /* Private */,
      28,    0,  286,    2, 0x08,   26 /* Private */,
      29,    0,  287,    2, 0x08,   27 /* Private */,
      30,    0,  288,    2, 0x08,   28 /* Private */,
      31,    0,  289,    2, 0x08,   29 /* Private */,
      32,    0,  290,    2, 0x08,   30 /* Private */,
      33,    0,  291,    2, 0x08,   31 /* Private */,
      34,    0,  292,    2, 0x08,   32 /* Private */,
      35,    0,  293,    2, 0x08,   33 /* Private */,
      36,    0,  294,    2, 0x08,   34 /* Private */,
      37,    0,  295,    2, 0x08,   35 /* Private */,
      38,    0,  296,    2, 0x08,   36 /* Private */,
      39,    0,  297,    2, 0x08,   37 /* Private */,
      40,    0,  298,    2, 0x08,   38 /* Private */,
      41,    0,  299,    2, 0x08,   39 /* Private */,
      42,    0,  300,    2, 0x08,   40 /* Private */,

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

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_FMnewWin_triggered(); break;
        case 1: _t->on_FMopenFile_triggered(); break;
        case 2: _t->on_FMsaveFile_triggered(); break;
        case 3: _t->on_FMeditor_triggered(); break;
        case 4: _t->on_PMRAM_triggered(); break;
        case 5: _t->on_PMROM_triggered(); break;
        case 6: _t->on_OMdefaultWinSize_triggered(); break;
        case 7: _t->on_ALUAcess_triggered(); break;
        case 8: _t->on_RAMAcess_triggered(); break;
        case 9: _t->on_a299Acess_triggered(); break;
        case 10: _t->on_registerAcess_triggered(); break;
        case 11: _t->on_microControlAcess_triggered(); break;
        case 12: _t->on_AMInfo_triggered(); break;
        case 13: _t->on_AMinstructions_triggered(); break;
        case 14: _t->on_runInMicroCmd_clicked(); break;
        case 15: _t->on_autoRun_clicked(); break;
        case 16: _t->on_runInCmd_clicked(); break;
        case 17: _t->on_T4pulse_clicked(); break;
        case 18: _t->on_SWA_clicked(); break;
        case 19: _t->on_SWC_clicked(); break;
        case 20: _t->on_swi_LDAR_clicked(); break;
        case 21: _t->on_swi_LDDR1_clicked(); break;
        case 22: _t->on_swi_299B_clicked(); break;
        case 23: _t->on_swi_LDDR2_clicked(); break;
        case 24: _t->on_swi_LDAD_clicked(); break;
        case 25: _t->on_swi_LDPC_clicked(); break;
        case 26: _t->on_swi_PCB_clicked(); break;
        case 27: _t->on_swi_ALUB_clicked(); break;
        case 28: _t->on_swi_SWB_clicked(); break;
        case 29: _t->on_swi_WE_clicked(); break;
        case 30: _t->on_swi_AR_clicked(); break;
        case 31: _t->on_swi_CE_clicked(); break;
        case 32: _t->on_swiInput_editingFinished(); break;
        case 33: _t->on_AR_BUT_clicked(); break;
        case 34: _t->on_startMircoADInput_editingFinished(); break;
        case 35: _t->on_functionInput_editingFinished(); break;
        case 36: _t->on_startMircoADInput_inputRejected(); break;
        case 37: _t->on_swiInput_inputRejected(); break;
        case 38: _t->on_functionInput_inputRejected(); break;
        case 39: _t->on_FMSaveAs_triggered(); break;
        case 40: _t->on_FMpasteFile_triggered(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t

, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 41)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 41;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 41)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 41;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
