#ifndef SYSTEMDATASET_H
#define SYSTEMDATASET_H

#include <QBrush>
#include <QGraphicsDropShadowEffect>
#include <QPainter>
#include <QPen>
#include <QString>
#include <QDebug>


//
extern QPen aluBodyPen;
extern QBrush aluBodyBrush;
//
extern QPen arBodyPen;
extern QBrush arBodyBrush;
//
extern QPen drBodyPen;
extern QBrush drBodyBrush;
//
extern QPen inputBodyPen;
extern QBrush inputBodyBrush;
//
extern QPen irBodyPen;
extern QBrush irBodyBrush;
//
extern QPen microConBodyPen;
extern QBrush microConBodyBrush;

extern QPen romBodyPen;
extern QBrush romBodyBrush;

extern QPen romCirPen;
extern QBrush romCirBrush;

extern QPen conBodyPen;
extern QBrush conBodyBrush;
//
extern QPen outputBodyPen;
extern QBrush outputBodyBrush;
//
extern QPen pcBodyPen;
extern QBrush pcBodyBrush;
//
extern QPen registerBodyPen;
extern QBrush registerBodyBrush;
//
extern QPen ramBodyPen;
extern QBrush ramBodyBrush;
//
extern QPen ramCirPen;
extern QBrush ramCirBrush;
//
extern QPen shifterBodyPen;
extern QBrush shifterBodyBrush;
//
extern QPen signalsLedBodyPen;
extern QBrush signalsLedBodyBrush;
extern QPen signalsLedBodyPenAct;
extern QBrush signalsLedBodyBrushAct;

//text pen brush
extern QPen lightTextPen;
extern QBrush ligthTextBrush;
extern QPen darkTextPen;
extern QBrush darkTextBrush;

//Siganls pen brush
extern QPen lightSignalsPen;
extern QBrush lightSignalsBrush;
extern QPen lightSignalsPenAct;
extern QBrush lightSignalsBrushAct;

extern QPen darkSignalsPen;
extern QBrush darkSignalsBrush;
extern QPen darkSignalsPenAct;
extern QBrush darkSignalsBrushAct;

//Font
extern QFont bigNameTextFont;
extern QFont bigDataTextFont;

extern QFont smallNameTextFont;
extern QFont smallDataTextFont;

extern QFont bigSignalsFont;
extern QFont smallSignalsFont;

//Line pen brush
extern QPen linePen;
extern QBrush lineBrush;
extern QPen linePenAct;
extern QBrush lineBrushAct;

extern QPen sigLinePen;

extern QPen sigLinePenAct;


//orginal color 26, 118, 150

//
#define ms3 24
#define ms2 23
#define ms1 22
#define ms0 21
#define mm 20
#define mcn 19
#define mwe 18
#define mB1 17
#define mB0 16
#define ma3 15
#define ma2 14
#define ma1 13
#define mb3 12
#define mb2 11
#define mb1 10
#define mc3 9
#define mc2 8
#define mc1 7
#define mu6 6
#define mu5 5
#define mu4 4
#define mu3 3
#define mu2 2
#define mu1 1


//-----------主要信号宏值定义----------------
#define WRITE 1     //write signal
#define READ 0      //read signal

//-----------------数据集--------------
class systemDataSet{
public:
    //
    int rom_row_size=100,rom_col_size=25;
    int ram_row_size=256,ram_col_size=2;
    int bus_size=2;

    //-----部件加载---------------
    bool load_rom=true;
    bool load_ram=true;
    bool load_ar=true;
    bool load_alu=true;
    bool load_dr1=true;
    bool load_dr2=true;
    bool load_r0=true;
    bool load_r1=true;
    bool load_r2=true;
    bool load_pc=true;
    bool load_ir=true;
    bool load_shifter_299b=true;
    bool load_con=true;


    //-----主要部件数据------------
    QString data_bus;               //总线数据
    int** data_rom;                 //rom内存
    QChar** data_ram;                //ram内存
    int data_ar;                    //地址寄存器
    int data_dr1,data_dr2;          //alu隐含寄存器
    int data_r0,data_r1,data_r2;    //寄存器组
    int data_pc;                    //PC计数器
    int data_ir;                    //指令寄存器
    int data_shifter_299b;          //299移位寄存器内存
    int data_mroAddress;            //微地址寄存器，也即微指令的地址寄存器
    int data_nextMroAddress;         //下一微地址，不存在的吼，仅用于实现程序
    int data_startMroAd;            //微地址每条指令取值令的第一条微地址
    int data_swi_input;             //开关输入数据
    int data_function_swi;          //功能开关输入

    int stopMroAddress;

    int intervalTime=1000;

    //---------------部件状态-------------------
    bool statu_ldar;                //(Indata)AR地址寄存器选中
    bool statu_lddr1,statu_lddr2;   //(Indata)dr1/2接入总线
    bool statu_ldad;                //(Indata)PC接入总线
    bool statu_ldled;               //(Indata)led接入总线
    bool statu_ld299;               //(INdata)299接入总线
    bool statu_alub;                //(Out)alu上总线，注仅在alu上总线时才会进行运算
    bool statu_299b;                //(Out)299上总线
    bool statu_swb;                 //(Out)开关上总线
    bool statu_pcb;                 //(Out)PC上总线
    bool statu_ldpc;                //(Signal)选中pc计数寄存器，在有输出情况下pc+1
    bool statu_ldr0;
    bool statu_ldr1;
    bool statu_ldr2;
    bool statu_r0b;
    bool statu_r1b;
    bool statu_r2b;
    bool statu_ldir;
    bool statu_irb;

    //---------------信号状态-------------------
    bool signal_we;              //(Signal)读写信号
    bool signal_ar;              //(Signal)带进位运算
    bool signal_ce;              //(Signal)Ram片选信号
    bool signal_swc,signal_swa;  //(Signal)swc，swa开关
    bool signal_cy,signal_zi;

    //---------------临时交换用数据---------------
    std::string tempString;

    //绘图用整体放大系数
    double zoomXPer=1,zoomYPer=1;

    systemDataSet();
    ~systemDataSet();

    bool setPara(int ram_row_size=512,int ram_col_size=2,int rom_row_size=256,int rom_col_size=25);

    //TODO 实现环境保存删除

    /// \brief Laod save enviroment
    /// \param env_file_path: Enviroment file path
    /// \return True (Load env suc), False(Load env false)
    bool loadEnv(QString env_file_path);

    /// \brief Save env to file
    /// \param env_file_path:Enviroment file save path
    /// \return True/False
    bool saveEnv(QString env_file_path);

    bool reSetDataSet();

    bool reSetSig();

    void resetRaomData();

    QString& getLogString();
};

#endif // SYSTEMDATASET_H
