/*********************************
 * 需要使用的函数集
 * 包含进制转换等
 * 各部件内部实现函数
 *********************************/
#include "functionSet.h"

using namespace std;

//2进制转10进制
int dataBTransD(int op1, int op2, int op3, int op4, int op5, int op6) {
    return (((((((op1) * 2 + op2) * 2 + op3) * 2) + op4) * 2) + op5) * 2 + op6;
}

//16进制转10进制
int dataHTransD(char op_1, char op_2) {
    int res;
    if (op_1 >= 'A' && op_1 <= 'F') {
        res = (int)(10 + op_1 - 'A') * 16;
    }else {
        res = (int)(op_1 - '0') * 16;
    }

    if (op_2 >= 'A' && op_2 <= 'F') {
        res += (int)(10 + op_2 - 'A');
    }else {
        res += (int)(op_2 - '0');
    }
    return res;
}

//16进制装转2进制
bool dataHTransB(char op,string& dataO) {
    int data = dataHTransD('0',op);
    //8 4 2 1
    dataO[0] = data / 8;
    dataO[1] = data % 8 / 4;
    dataO[2] = data % 8 % 4/2;
    dataO[3] = data % 8 % 4 % 2;
    return true;
}

//10进制转16进制
bool dataDTransH(int dataI,string& dataO) {
    dataO="00";
    if (dataI < 0) {
        dataI += 256;
    }
    if (dataI > 255)return false;
    if ((dataI / 16) > 9) {
        dataO[0] = dataI / 16 - 10 + 'A';
    }
    else {
        dataO[0] = dataI / 16 + '0';
    }
    if ((dataI % 16) > 9) {
        dataO[1] = dataI % 16 -10+ 'A';
    }
    else {
        dataO[1] = dataI % 16 + '0';
    }
    return true;
}

//-------------------部件299-------------------------------------------------------------
// 移位寄存器，选中信号、微指令s1、s0、m
bool _299(_data *data) {

    std::string& busData=data->busData;
    bool statu_299b=data->Acess_299 && data->statu_299b;
    bool& cy=data->signal_cy;
    char s1=data->rom[data->mroAddress][22];
    char s0=data->rom[data->mroAddress][21];
    char m=data->rom[data->mroAddress][20];
    int& _299=data->_299;

    if (s1 == 1 && s0 == 1 ) {
        _299 = dataHTransD(busData[0], busData[1]);
    }
    else if(s1 == 0 && s0 == 0 && m == 0){
        if (statu_299b == false)return false;
        dataDTransH(_299, busData);
    }
    else if (s1 == 1 && s0 == 0 && m == 1) {//带进位循环右移1位
        _299 = rorc(_299,cy);

    }
    else if (s1 == 1 && s0 == 0 && m == 0) {//循环右移1位
        _299 = ror(_299);
    }
    else if (s1 == 0 && s0 == 1 && m == 0) {//循环左移
        _299 = rol(_299);
    }
    else if (s1 == 0 && s0 == 1 && m == 1) {//循环带进位左移
        _299 = rolc(_299,cy);
    }
    return true;
}

/*循环左移*/
int rol(int val)
{
    int res = (val * 2) % 256 + val / 128;
    return res;
}

/*循环右移*/
int ror(int val)
{
    int res = val / 2 + 128 * (val % 2);
    return res;
}

/*循环带进位左移*/
int rolc(int val,int cy)
{
    int res;
    if (cy == true) {
        res = val % 128;
        res *= 2;
        res += 1;
    }
    else {
        res = val % 128;
        res *= 2;
    }
    cy = val / 128;
    return res;
}

/*循环带进位右移*/
int rorc(int val,int cy)
{
    int res;

    if (cy == true) {
        res = val / 2 + 128;
    }
    else {
        res = val / 2;
    }
    cy = val % 2;
    return res;
}

//-------------------部件ALU-------------------------------------------------------------
//ALU主控，是否输出(B字段产生)，s3~s0,m,cn,ar(C字段产生，是否影响CY&&ZI)
bool ALU(_data* data) {
    bool statu_alub=data->statu_alub&&data->Acess_ALU;
    if(statu_alub==false) return true;

    std::string& busData=data->busData;
    bool& cy=data->signal_cy;
    bool& zi=data->signal_zi;
    bool& ar=data->signal_ar;
    char s3=data->rom[data->mroAddress][24];
    char s2=data->rom[data->mroAddress][23];
    char s1=data->rom[data->mroAddress][22];
    char s0=data->rom[data->mroAddress][21];
    char m=data->rom[data->mroAddress][20];
    char cn=data->rom[data->mroAddress][19];
    int& dr1=data->dr1;
    int& dr2=data->dr2;

    //QMessageBox::information(nullptr,"","Dr1+Dr2  "+QString::number(data->mroAddress));

    int res=1;
    if (ar) {
        cy = false;
        zi = false;
    }

    if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 0 && m == 0 && cn == 1) {//dr1
        res = dr1;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 0 && m == 0 && cn == 0) {//dr1+1
        res = dr1 + 1;
        if (ar && res>255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 0 && m == 1) {//逻辑  ~dr1
        res = 256 - dr1;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 1 && m == 0 && cn == 1) {// dr1|dr2
        res = dr1 | dr2;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 1 && m == 0 && cn == 0) {// dr1|dr2+1
        res = dr1 | dr2 + 1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 1 && m == 1) {//逻辑 ~(dr1|dr2)
        res = dr1 | dr2;
        res = 256-res;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 0 && m == 0 && cn == 1) {//A|(~B)
        res = dr1 | (256-dr2);
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 0 && m == 0 && cn == 0) {//A||(~B)+1
        res = (dr1 | (256 - dr2)) + 1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 0 && m == 1) {//逻辑 ~(A|B)
        res = 256 - (dr1 | dr2);
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 1 && m == 0 && cn == 1) {//-1
        res = 255;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 1 && m == 0 && cn == 0) {//0
        res = 0;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 1 && m == 1) {//逻辑0
        res = 0;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 0 && m == 0 && cn == 1) {//A+(A&~b)
        res = dr1 + (dr1 & (256 - dr2));
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 0 && m == 0 && cn == 0) {//A+(A&~b)+1
        res = dr1 + (dr1 & (256 - dr2))+1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 0 && m == 1) {//逻辑~(a&b)
        res = 256 - (dr1 & dr2);
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 1 && m == 0 && cn == 1) {//(A|B)+(A&~B)
        res = (dr1 | dr2) + (dr1 & (256 - dr2));
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 1 && m == 0 && cn == 0) {//(A|B)+(A&~B)+1
        res = (dr1 | dr2) + (dr1 & (256 - dr2)) + 1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 1 && m == 1) {//逻辑~dr2
        res = 256 - dr2;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 0 && m == 0 && cn == 1) {//a-b-1
        res = dr1 - dr2 + 255 + 255;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 0 && m == 0 && cn == 0) {//a-b
        res = dr1 - dr2+256;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 0 && m == 1) {//逻辑(a^b)
        res = dr1 ^ dr2;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 1 && m == 0 && cn == 1) {//(A&~B)-1
        res = dr1 & (256 - dr2) + 255;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 1 && m == 0 && cn == 0) {//A&~B
        res = dr1 & (256 - dr2);
        if (ar) {
            cy = true;
        }
        dataDTransH(res, busData);
    }
    else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 1 && m == 1) {//逻辑A&~B
        res = dr1 & (256 - dr2);
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 0 && m == 0 && cn == 1) {//A+A&B
        res = dr1 + (dr1 & dr2);
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 0 && m == 0 && cn == 0) {//A+A&B+1
        res = dr1 + (dr1 & dr2) + 1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 0 && m == 1) {//逻辑~A | B   here
        res = 256 - (dr1 & dr2);
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 1 && m == 0 && cn == 1) {//A+B
        res = dr1 + dr2;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 1 && m == 0 && cn == 0) {//A+B+1
        res = dr1 + dr2 + 1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 1 && m == 1) {//逻辑~(A^B)
        res = 256 - (dr1 ^ dr2);
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 0 && m == 0 && cn == 1) {//(A|~B)+A&B
        res = (dr1 | (256 - dr2)) + (dr1 & dr2);
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 0 && m == 0 && cn == 0) {//(A|~B)+A&B+1
        res = (dr1 | (256 - dr2)) + dr1 & dr2 + 1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 0 && m == 1) {//逻辑B
        res = dr2;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 1 && m == 0 && cn == 1) {//A&B-1
        res = dr1 & dr2 + 255;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 1 && m == 0 && cn == 0) {//A&B
        res = dr1 & dr2;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 1 && m == 1) {//逻辑A&B
        res = dr1 & dr2;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 0 && m == 0 && cn == 1) {//A+A
        res = dr1 + dr1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 0 && m == 0 && cn == 0) {//A+A+1
        res = dr1 + dr1+1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 0 && m == 1) {//逻辑1
        res = 1;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 1 && m == 0 && cn == 1) {//(A|B)+A
        res = (dr1 | dr2) + dr1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 1 && m == 0 && cn == 0) {//(A|B)+A+1
        res = (dr1 | dr2) + dr1 + 1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 1 && m == 1) {//逻辑A|~B
        res = dr1 | (256 - dr2);
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 0 && m == 0 && cn == 1) {//(A|~B)+A
        res = (dr1 | (256 - dr2)) + dr1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 0 && m == 0 && cn == 0) {//(A|~B)+A+1
        res = (dr1 | (256 - dr2)) + dr1 + 1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 0 && m == 1) {//逻辑A|B
        res = dr1 | dr2;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 1 && m == 0 && cn == 1) {//A-1
        res = dr1 + 255;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 1 && m == 0 && cn == 0) {//A
        res = dr1;
        dataDTransH(res, busData);
    }
    else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 1 && m == 1) {//逻辑A
        res = dr1;
        dataDTransH(res, busData);
    }
    //
    if (ar) {
        if (res == 0) {
            zi = true;
        }
        else {
            zi = false;
        }
    }
    return true;
}
bool DR1(_data* data){
    if(data->statu_lddr1){
        data->dr1=dataHTransD(data->busData[0],data->busData[1]);
    }
    return true;
}
bool DR2(_data* data){
    if(data->statu_lddr2){
        data->dr2=dataHTransD(data->busData[0],data->busData[1]);
    }
    return true;
}

//-------------------部件RAM-------------------------------------------------------------
bool RAM(_data* data) {
    std::string& busData=data->busData;
    bool& ce=data->signal_ce;
    bool& we=data->signal_we;
    int& ar=data->ar;

    if (ce == false) {//未选中
        return false;
    }
    if (we == READ) {
        if (ar > 256) {
            return false;
        }
        busData[0] = data->ram[ar][0];
        busData[1] = data->ram[ar][1];
        //QMessageBox::information(nullptr,"","Ram输出  "+QString::number(data->ar)+data->ram[ar][0]+data->ram[ar][1]);
        return true;
    }
    else {//写入
        if (ar > 256) {
            return false;
        }
        data->ram[ar][0] = busData[0];
        data->ram[ar][1] = busData[1];
        return true;
    }
    return true;
}

//-------------------部件SW(IN)------------------------------------------------------------
bool SW(_data* data){
    if(data->statu_swb) return dataDTransH(data->swiInputData,data->busData);
    return false;
}

//-------------------部件OUT-------------------------------------------------------------

bool LED(_data* data) {
    if (data->signal_we == READ) {//未输出
        return false;
    }
    if (data->statu_ldled == false){
        return false;
    }
    return true;
}

//-------------------部件PC-------------------------------------------------------------
bool PC(_data* data){

    if (data->statu_ldpc == false)return false;
    std::string& busData=data->busData;
    if(data->statu_ldad){
        //PC作为输入，选中信号
        data->pc=dataHTransD(busData[0],busData[1]);
        return true;
    }else if(data->statu_pcb){


        dataDTransH(data->pc, busData);
        data->pc++;
        return true;
    }
    return true;
}

//-------------------部件IR-------------------------------------------------------------
bool IR(_data* data){
    if(data->statu_ldir){
        data->ir=dataHTransD(data->busData[0],data->busData[1]);
    }else if(data->statu_irb){
        dataDTransH(data->ir,data->busData);
    }
    return true;
}

//-------------------部件IR-------------------------------------------------------------
bool AR(_data* data){
    if(data->statu_ldar){
        //QMessageBox::information(nullptr,"","AR  "+QString::fromStdString(data->busData));
        data->ar=dataHTransD(data->busData[0],data->busData[1]);
    }
    return true;
}


//-------------------部件Register-------------------------------------------------------------
//RI作为输出，选中信号、B字段选中类型
bool RIOut(_data* data) {
    if (data->statu_r0b) {//0000---R0
        dataDTransH(data->r0, data->busData);
    }
    else if (data->statu_r1b) {//0100---R1
        dataDTransH(data->r1, data->busData);
    }
    else if (data->statu_r2b) {//1000---R2
        dataDTransH(data->r2, data->busData);
    }
    else {//1100---ERROR
        return false;
    }
    return true;
}

//RI作为输入，选中信号（选中类型在A字段以确定）
bool RIIn(_data* data) {
    if (data->statu_ldr0) {//0000---R0
        data->r0=dataHTransD(data->busData[0],data->busData[1]);
    }
    else if (data->statu_ldr1) {//0100---R1
        data->r1=dataHTransD(data->busData[0],data->busData[1]);
    }
    else if (data->statu_ldr2) {//1000---R2
        data->r2=dataHTransD(data->busData[0],data->busData[1]);
    }
    else {//1100---ERROR
        return false;
    }
    return true;
}

//-------------------转移方式-------------------------------------------------------------
//P(1)转移，返回下一微地址
int P1(_data* data) {
    data->mroAddress -= data->mroAddress % 16;
    data->mroAddress=data->ir / 16 + data->mroAddress;
    return data->ir / 16 + data->mroAddress;
}

//P(2)转移，i3、i2的值,返回下一微地址
int P2(_data* data) {
    data->mroAddress -= data->mroAddress % 4;
    data->mroAddress=(data->ir % 16) / 4 + data->mroAddress;
    return (data->ir % 16) / 4 + data->mroAddress;
}

//P(3)转移，在zi&&cy均为false时返回false
bool P3(_data* data) {
    if (data->signal_cy == false && data->signal_zi == false) {
        return false;
    }
    if ((data->mroAddress % 32) / 16 == 0) {
        data->mroAddress += 16;
    }
    return true;
}

//P(4)，SWC，SWA转移返回下一微地址
int P4(_data* data) {
    data->mroAddress -= data->mroAddress % 4;
    data->mroAddress+=data->mroAddress + data->signal_swc * 2 + data->signal_swa;
    return data->mroAddress + data->signal_swc * 2 + data->signal_swa;
}
