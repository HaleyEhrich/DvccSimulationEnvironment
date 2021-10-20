#include "dataSet.h"


_data::_data(){
    this->Acess_299=true;
    this->Acess_ALU=true;
    this->Acess_Mro=true;
    this->Acess_RAM=true;
    this->Acess_res=true;
    //------------状态数据------------
    statu_ldar=false;            //(In)AR地址寄存器选中
    statu_lddr1=false;
    statu_lddr2=false;           //(In)dr1/2接入总线
    statu_ldad=false;            //(In)PC接入总线
    statu_ldled=false;           //(In)led接入总线
    statu_alub=false;            //(Out)alu上总线，注仅在alu上总线时才会进行运算
    statu_299b=false;            //(Out)299上总线
    statu_swb=false;             //(Out)开关上总线
    statu_pcb=false;             //(Out)PC上总线
    statu_ldpc=false;            //(Signal)选中pc计数寄存器，在有输出情况下pc+1
    statu_ld299=false;
    statu_ldr0=false;
    statu_ldr1=false;
    statu_ldr2=false;
    statu_r0b=false;
    statu_r1b=false;
    statu_r2b=false;
    statu_ldir=false;
    statu_irb=false;

    //-------------信号数据------------
    signal_we=false;              //(Signal)读写信号
    signal_ar=false;              //(Signal)带进位运算
    signal_ce=false;              //(Signal)Ram片选信号
    signal_swc=true;
    signal_swa=true;              //(Signal)swc，swa开关
    signal_cy=false;
    signal_zi=false;

    //-----主要数据部件------------
    busData="00";       //总线数据
    ar=0;               //地址寄存器
    dr1=0;
    dr2=0;              //alu隐含寄存器
    r0=0;
    r1=0;
    r2=0;               //寄存器组
    pc=0;                //PC计数器
    ir=0;               //指令寄存器
    _299=0;             //299移位寄存器内存
    mroAddress=0;       //微地址寄存器，也即微指令的地址寄存器
    startMroAd=2;       //微地址每条指令取值令的第一条微地址
    swiInputData=0;     //数据开关数据
    functionInput=0;    //功能开关数据
    //rom初始化为0
    for(int i=0;i<100;++i){
        for(int j=0;j<=25;++j)
            rom[i][j]=0;
    }
    //ram初始化
    for(int i=0;i<256;i++){
        for(int j=0;j<2;j++){
            ram[i][j]='0';
        }
    }

    //--------------临时----------
    tempString="00";

    //--------------绘图使用--------------
    this->zoomPerX=1.0;
    this->zoomPerY=1.0;
}

bool _data::reSet(){
    this->Acess_299=true;
    this->Acess_ALU=true;
    this->Acess_Mro=true;
    this->Acess_RAM=true;
    this->Acess_res=true;
    //------------状态数据------------
    statu_ldar=false;            //(In)AR地址寄存器选中
    statu_lddr1=false;
    statu_lddr2=false;           //(In)dr1/2接入总线
    statu_ldad=false;            //(In)PC接入总线
    statu_ldled=false;           //(In)led接入总线
    statu_alub=false;            //(Out)alu上总线，注仅在alu上总线时才会进行运算
    statu_299b=false;            //(Out)299上总线
    statu_swb=false;             //(Out)开关上总线
    statu_pcb=false;             //(Out)PC上总线
    statu_ldpc=false;            //(Signal)选中pc计数寄存器，在有输出情况下pc+1
    statu_ld299=false;
    statu_ldr0=false;
    statu_ldr1=false;
    statu_ldr2=false;
    statu_r0b=false;
    statu_r1b=false;
    statu_r2b=false;
    statu_ldir=false;
    statu_irb=false;

    //-------------信号数据------------
    signal_we=false;              //(Signal)读写信号
    signal_ar=false;              //(Signal)带进位运算
    signal_ce=false;              //(Signal)Ram片选信号
    signal_swc=true;
    signal_swa=true;              //(Signal)swc，swa开关
    signal_cy=false;
    signal_zi=false;

    //-----主要数据部件------------
    busData="00";       //总线数据
    ar=0;               //地址寄存器
    dr1=0;
    dr2=0;              //alu隐含寄存器
    r0=0;
    r1=0;
    r2=0;               //寄存器组
    pc=0;                //PC计数器
    ir=0;               //指令寄存器
    _299=0;             //299移位寄存器内存
    mroAddress=0;       //微地址寄存器，也即微指令的地址寄存器
    startMroAd=2;       //微地址每条指令取值令的第一条微地址
    swiInputData=0;     //数据开关数据
    functionInput=0;    //功能开关数据
    //rom初始化为0
    for(int i=0;i<100;++i){
        for(int j=0;j<=25;++j)
            rom[i][j]=0;
    }
    //ram初始化
    for(int i=0;i<256;i++){
        for(int j=0;j<2;j++){
            ram[i][j]='0';
        }
    }

    //--------------临时----------
    tempString="00";

    return true;
}

//自动运行信号恢复
bool _data::reSetSig(){
    //------------状态数据------------
    statu_ldar=false;            //(In)AR地址寄存器选中
    statu_lddr1=false;
    statu_lddr2=false;           //(In)dr1/2接入总线
    statu_ldad=false;            //(In)PC接入总线
    statu_ldled=false;           //(In)led接入总线
    statu_alub=false;            //(Out)alu上总线，注仅在alu上总线时才会进行运算
    statu_299b=false;            //(Out)299上总线
    statu_swb=false;             //(Out)开关上总线
    statu_pcb=false;             //(Out)PC上总线
    statu_ldpc=false;            //(Signal)选中pc计数寄存器，在有输出情况下pc+1
    statu_ld299=false;
    statu_ldr0=false;
    statu_ldr1=false;
    statu_ldr2=false;
    statu_r0b=false;
    statu_r1b=false;
    statu_r2b=false;
    statu_ldir=false;
    statu_irb=false;

    //-------------信号数据------------
    signal_we=false;              //(Signal)读写信号
    signal_ar=false;              //(Signal)带进位运算
    signal_ce=false;              //(Signal)Ram片选信号
    return true;
}

_data::~_data(){

}
