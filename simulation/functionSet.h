#ifndef FUNCTIONSET_H
#define FUNCTIONSET_H

#include<string>
#include "dataSet.h"

//2进制转16进制
int dataBTransD(int op1, int op2, int op3, int op4, int op5, int op6);

//16进制转10进制
int dataHTransD(char op_1, char op_2);

//16进制装转2进制
bool dataHTransB(char op,std::string& dataO);

//10进制转16进制
bool dataDTransH(int dataI,std::string& dataO);

//-------------------部件299-------------------------------------------------------------
bool _299(_data* data);
int rol(int val);
int ror(int val);
int rolc(int val,int cy);
int rorc(int val,int cy);

//-------------------部件ALU-------------------------------------------------------------
bool ALU(_data *data);
bool DR1(_data* data);
bool DR2(_data* data);

//-------------------部件RAM-------------------------------------------------------------
bool RAM(_data* data);

//-------------------部件SW-------------------------------------------------------------
bool SW(_data* data);

//-------------------部件PC-------------------------------------------------------------
bool PC(_data* data);

//-------------------部件OUT-------------------------------------------------------------
bool LED(_data* data);

//-------------------部件IR-------------------------------------------------------------
bool IR(_data* data);

//-------------------部件AR-------------------------------------------------------------
bool AR(_data* data);

//-------------------部件Register-------------------------------------------------------------
//RI作为输出，选中信号、B字段选中类型
bool RIOut(_data* data);

//RI作为输入，选中信号（选中类型在A字段以确定）
bool RIIn(_data* data);

//-------------------转移方式-------------------------------------------------------------
//P(1)转移，返回下一微地址
int P1(_data* data);

//P(2)转移，i3、i2的值,返回下一微地址
int P2(_data* data);

//P(3)转移，在zi&&cy均为false时返回false
bool P3(_data* data);

//P(4)，SWC，SWA转移返回下一微地址
int P4(_data* data);

#endif // FUNCTIONSET_H
