#ifndef DATASET_H
#define DATASET_H

#include <string>

//-----------主要信号宏值定义----------------
#define WRITE 1     //write signal
#define READ 0      //read signal

//-----------------数据集--------------
class _data{
public:
    //------各部件接入选项数据------
    bool Acess_ALU;
    bool Acess_RAM;
    bool Acess_299;
    bool Acess_res;
    bool Acess_Mro;
    //-----主要数据部件------------
    std::string busData;    //总线数据
    int rom[100][25];       //rom内存
    char ram[256][2];      //ram内存
    int ar;                 //地址寄存器
    int dr1,dr2;            //alu隐含寄存器
    int r0,r1,r2;           //寄存器组
    int pc;                 //PC计数器
    int ir;                 //指令寄存器
    int _299;              //299移位寄存器内存
    int mroAddress;         //微地址寄存器，也即微指令的地址寄存器
    int startMroAd;           //微地址每条指令取值令的第一条微地址
    int swiInputData;       //开关输入数据
    int functionInput;      //功能开关输入

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
    double zoomPerX,zoomPerY;

    _data();
    ~_data();
    bool reSet();
    bool reSetSig();
};

#endif // DATASET_H
