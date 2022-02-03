#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <fstream>
#include <QFile>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QInputDialog>
#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <QValidator>
#include <QWindow>
#include <QDesktopServices>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QLabel>
#include <QButtonGroup>
#include <QWidget>
#include <QPen>
#include <QBrush>
#include <QTimer>
#include "dataSet.h"
#include "ramcheck.h"
#include "romcheck.h"



//--------------目前执行的微指令的宏---------
#define _s3 this->data->rom[this->data->mroAddress][24]
#define _s2 this->data->rom[this->data->mroAddress][23]
#define _s1 this->data->rom[this->data->mroAddress][22]
#define _s0 this->data->rom[this->data->mroAddress][21]
#define _m this->data->rom[this->data->mroAddress][20]
#define _cn this->data->rom[this->data->mroAddress][19]
#define _we this->data->rom[this->data->mroAddress][18]
#define _B1 this->data->rom[this->data->mroAddress][17]
#define _B0 this->data->rom[this->data->mroAddress][16]
#define _a3 this->data->rom[this->data->mroAddress][15]
#define _a2 this->data->rom[this->data->mroAddress][14]
#define _a1 this->data->rom[this->data->mroAddress][13]
#define _b3 this->data->rom[this->data->mroAddress][12]
#define _b2 this->data->rom[this->data->mroAddress][11]
#define _b1 this->data->rom[this->data->mroAddress][10]
#define _c3 this->data->rom[this->data->mroAddress][9]
#define _c2 this->data->rom[this->data->mroAddress][8]
#define _c1 this->data->rom[this->data->mroAddress][7]
#define _u6 this->data->rom[this->data->mroAddress][6]
#define _u5 this->data->rom[this->data->mroAddress][5]
#define _u4 this->data->rom[this->data->mroAddress][4]
#define _u3 this->data->rom[this->data->mroAddress][3]
#define _u2 this->data->rom[this->data->mroAddress][2]
#define _u1 this->data->rom[this->data->mroAddress][1]



//颜色定义
#define dataColor 255, 255, 255
#define desWordColor 0, 0, 0

//主要画笔

#define bodyBrush QBrush(QColor(103, 158, 210))
#define bodyPen QPen(QColor(92, 146, 145),0)            //部件主体

#define busPen QPen(QColor(0,0,0),4)
#define chooseBusPen QPen(QColor(255, 86, 0),5)        //数据传输线

#define signalPen QPen(Qt::black, 1)
#define chooseSignalPen QPen(QColor(255, 194, 0),3)     //信号线，信号描述文字

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //statubar显示用数据
    QLabel* statusBarLable;
    //仿真环境数据
    QFile *proFile;
    class _data *data;
    class RAMCheck *ramPannel;
    class ROMCheck *romPannel;

    //绘制各部件函数
    void paintBusLine(bool choose,QPainter *paint);
    void paint299(QPainter *paint);
    void paintAlu(QPainter *paint);
    void paintDr1(QPainter *paint);
    void paintDr2(QPainter *paint);
    void paintPc(QPainter *paint);
    void paintAr(QPainter *paint);
    void paintRam(QPainter *paint);
    void paintR0(QPainter *paint);
    void paintR1(QPainter *paint);
    void paintR2(QPainter *paint);
    void paintIr(QPainter *paint);
    void paintMroCon(QPainter *paint);
    void paintInput(QPainter *paint);
    void paintOutput(QPainter *paint);
    void paintSignal(QPainter *paint);
    //
    void signalPro(_data*);
    bool isFileLoad();


protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

private slots:

    void on_FMnewWin_triggered();

    void on_FMopenFile_triggered();

    void on_FMsaveFile_triggered();

    void on_FMeditor_triggered();

    void on_PMRAM_triggered();

    void on_PMROM_triggered();

//    void on_PMswitch_triggered();

    void on_OMdefaultWinSize_triggered();

    void on_ALUAcess_triggered();

    void on_RAMAcess_triggered();

    void on_a299Acess_triggered();

    void on_registerAcess_triggered();

    void on_microControlAcess_triggered();

    void on_AMInfo_triggered();

    void on_AMinstructions_triggered();

    void on_runInMicroCmd_clicked();

    void on_autoRun_clicked();

    void on_runInCmd_clicked();

    void on_T4pulse_clicked();

    void on_SWA_clicked();

    void on_SWC_clicked();

    void on_swi_LDAR_clicked();

    void on_swi_LDDR1_clicked();

    void on_swi_299B_clicked();

    void on_swi_LDDR2_clicked();

    void on_swi_LDAD_clicked();

    void on_swi_LDPC_clicked();

    void on_swi_PCB_clicked();

    void on_swi_ALUB_clicked();

    void on_swi_SWB_clicked();

    void on_swi_WE_clicked();

    void on_swi_AR_clicked();

    void on_swi_CE_clicked();

    void on_swiInput_editingFinished();

    void on_AR_BUT_clicked();

    void on_startMircoADInput_editingFinished();

    void on_functionInput_editingFinished();

    void on_startMircoADInput_inputRejected();

    void on_swiInput_inputRejected();

    void on_functionInput_inputRejected();

    void on_FMSaveAs_triggered();

    void on_FMpasteFile_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
