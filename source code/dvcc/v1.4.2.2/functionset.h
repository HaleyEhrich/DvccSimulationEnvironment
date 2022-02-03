#ifndef FUNCTIONSET_H
#define FUNCTIONSET_H

#include <QApplication>
#include <QMessageBox>
#include <QString>

#include "systemdataset.h"

class functionSet
{
public:
    functionSet();
};

///
/// \brief hexcToDec 传入一个Hexc，返回一个int值(Deci)
/// \param hexcLetter Hexc字符('0'-'9' 'a'-'f' 'A'-'F')
/// \return deci 0x00-oxff
///
int hexcToDec(QChar& hexcLetter);

///
/// \brief binaToDec 传入6个Bina，返回一个int值(Deci)
/// \param op1 bianary 1 ('0'-'1') Hightest Bit
/// \param op2 bianary 2 ('0'-'1')
/// \param op3 bianary 3 ('0'-'1')
/// \param op4 bianary 4 ('0'-'1')
/// \param op5 bianary 5 ('0'-'1')
/// \param op6 bianary 6 ('0'-'1')Lowerest Bit
/// \return deci 0x00-0x4f
///
int binaToDec(int op1, int op2, int op3, int op4, int op5, int op6);

void signalsPreProcess(systemDataSet* data);

//-------------------部件299-------------------------------------------------------------
bool _299(systemDataSet* data);
int rol(int val);
int ror(int val);
int rolc(int val,bool& cy);
int rorc(int val,bool& cy);

//-------------------部件ALU-------------------------------------------------------------
bool ALU(systemDataSet*data);
bool DR1(systemDataSet* data);
bool DR2(systemDataSet* data);

//-------------------部件RAM-------------------------------------------------------------
bool RAM(systemDataSet* data);

//-------------------部件SW-------------------------------------------------------------
bool SW(systemDataSet* data);

//-------------------部件PC-------------------------------------------------------------
bool PC(systemDataSet* data);

//-------------------部件OUT-------------------------------------------------------------
bool LED(systemDataSet* data);

//-------------------部件IR-------------------------------------------------------------
bool IR(systemDataSet* data);

//-------------------部件AR-------------------------------------------------------------
bool AR(systemDataSet* data);

//-------------------部件Register-------------------------------------------------------------
//RI作为输出，选中信号、B字段选中类型
bool RIOut(systemDataSet* data);

//RI作为输入，选中信号（选中类型在A字段以确定）
bool RIIn(systemDataSet* data);

//-------------------转移方式-------------------------------------------------------------
int Oreder(systemDataSet* data);

//P(1)转移，返回下一微地址
int P1(systemDataSet* data);

//P(2)转移，i3、i2的值,返回下一微地址
int P2(systemDataSet* data);

//P(3)转移，在zi&&cy均为false时返回false
int P3(systemDataSet* data);

//P(4)，SWC，SWA转移返回下一微地址
int P4(systemDataSet* data);


#endif // FUNCTIONSET_H
