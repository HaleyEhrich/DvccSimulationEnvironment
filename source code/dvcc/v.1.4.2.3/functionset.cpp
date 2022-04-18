#include "functionset.h"

functionSet::functionSet()
{

}

int hexcToDec(QChar& hexcLetter){

    if(hexcLetter<='9'&&hexcLetter>='0'){
        return hexcLetter.toLatin1()-'0';
    }else{

        if(hexcLetter>='a'&&hexcLetter<='f'){
            return hexcLetter.toLatin1()-'a'+10;
        }

        if(hexcLetter>='A'&&hexcLetter<='F'){
            return hexcLetter.toLatin1()-'A'+10;
        }
    }
    return 15;
}

int binaToDec(int op1, int op2, int op3, int op4, int op5, int op6)
{
    return (((((((op1) * 2 + op2) * 2 + op3) * 2) + op4) * 2) + op5) * 2 + op6;
}

/// \brief 对rom目前指向的微指令进行处理，设置对应部件的输入、输出控制变量
/// \author HE
void signalsPreProcess(systemDataSet *data)
{
    data->reSetSig();

//    qDebug()<<data->data_mroAddress<<data->data_nextMroAddress;

    if (data->data_rom[data->data_mroAddress][mb3] == 0
            && data->data_rom[data->data_mroAddress][mb2] == 0
            && data->data_rom[data->data_mroAddress][mb1] == 0) {//内部输出设备不存在
        if (data->data_rom[data->data_mroAddress][mB1] == 0
                && data->data_rom[data->data_mroAddress][mB0] == 0) {//SW
            data->statu_swb=true;
        }else if(data->data_rom[data->data_mroAddress][mB1]==0 && data->data_rom[data->data_mroAddress][mB0]==1){//RAM
            data->signal_ce=true;
        }
    }
    else if (data->data_rom[data->data_mroAddress][mb3] == 0
             && data->data_rom[data->data_mroAddress][mb2] == 0
             && data->data_rom[data->data_mroAddress][mb1] == 1) {//RS-B
        switch ((data->data_ir%8)/4){
        case 0:{
            data->statu_r0b=true;
            break;
        }
        case 1:{
            data->statu_r1b=true;
            break;
        }
        case 2:{
            data->statu_r2b=true;
            break;
        }
        }
    }
    else if (data->data_rom[data->data_mroAddress][mb3] == 0
             && data->data_rom[data->data_mroAddress][mb2] == 1
             && data->data_rom[data->data_mroAddress][mb1] == 0) {//RD-B
        switch ((data->data_ir % 4)){
        case 0:{
            data->statu_r0b=true;
            break;
        }
        case 1:{
            data->statu_r1b=true;
            break;
        }
        case 2:{
            data->statu_r2b=true;
            break;
        }
        }
    }
    else if (data->data_rom[data->data_mroAddress][mb3] == 0
             && data->data_rom[data->data_mroAddress][mb2] == 1
             && data->data_rom[data->data_mroAddress][mb1] == 1) {//RI-B(选R2）
        data->statu_r2b=true;
    }
    else if (data->data_rom[data->data_mroAddress][mb3] == 1
             && data->data_rom[data->data_mroAddress][mb2] == 0
             && data->data_rom[data->data_mroAddress][mb1] == 0) {//299-B
        data->statu_299b=true;
    }
    else if (data->data_rom[data->data_mroAddress][mb3] == 1
             && data->data_rom[data->data_mroAddress][mb2] == 0
             && data->data_rom[data->data_mroAddress][mb1] == 1) {//ALU-B
        data->statu_alub=true;
    }
    else if (data->data_rom[data->data_mroAddress][mb3] == 1
             && data->data_rom[data->data_mroAddress][mb2] == 1
             && data->data_rom[data->data_mroAddress][mb1] == 0) {//PC-B
        data->statu_pcb=true;
    }

    //输入部件运行
    if (data->data_rom[data->data_mroAddress][ma3] == 0
            && data->data_rom[data->data_mroAddress][ma2] == 0
            && data->data_rom[data->data_mroAddress][ma1] == 0) {//内部输入设备不选中
        if (data->data_rom[data->data_mroAddress][mB1] == 1
                && data->data_rom[data->data_mroAddress][mB0] == 0) {//LED
            data->statu_ldled=true;
        }else if(data->data_rom[data->data_mroAddress][mB1] ==0
                 && data->data_rom[data->data_mroAddress][mB0] ==1){//RAM
            data->signal_ce=true;
        }else {
            if (data->data_rom[data->data_mroAddress][ms1] == 1
                    && data->data_rom[data->data_mroAddress][ms0] == 1) {//299装数
                data->statu_ld299=true;
            }
        }
    }
    else if (data->data_rom[data->data_mroAddress][ma3] == 0
             && data->data_rom[data->data_mroAddress][ma2] == 0
             && data->data_rom[data->data_mroAddress][ma1] == 1) {//RiIN
        switch ((data->data_ir % 4)){
        case 0:{
            data->statu_ldr0=true;
            break;
        }
        case 1:{
            data->statu_ldr1=true;
            break;
        }
        case 2:{
            data->statu_ldr2=true;
            break;
        }
        }
    }
    else if (data->data_rom[data->data_mroAddress][ma3] == 0
             && data->data_rom[data->data_mroAddress][ma2] == 1
             && data->data_rom[data->data_mroAddress][ma1] == 0) {//DR1
        data->statu_lddr1=true;
    }
    else if (data->data_rom[data->data_mroAddress][ma3] == 0
             && data->data_rom[data->data_mroAddress][ma2] == 1
             && data->data_rom[data->data_mroAddress][ma1] == 1) {//DR2
        data->statu_lddr2=true;
    }
    else if (data->data_rom[data->data_mroAddress][ma3] == 1
             && data->data_rom[data->data_mroAddress][ma2] == 0
             && data->data_rom[data->data_mroAddress][ma1] == 0) {//LDIR
        data->statu_ldir=true;
    }
    else if (data->data_rom[data->data_mroAddress][ma3] == 1
             && data->data_rom[data->data_mroAddress][ma2] == 0
             && data->data_rom[data->data_mroAddress][ma1] == 1) {//LDAD(PC)
        data->statu_ldad=true;
    }
    else if (data->data_rom[data->data_mroAddress][ma3] == 1
             && data->data_rom[data->data_mroAddress][ma2] == 1
             && data->data_rom[data->data_mroAddress][ma1] == 0) {//LDAR
        data->statu_ldar=true;
    }
    else if (data->data_rom[data->data_mroAddress][ma3] == 1
             && data->data_rom[data->data_mroAddress][ma2] == 1
             && data->data_rom[data->data_mroAddress][ma1] == 1) {//NONE
        if (data->data_rom[data->data_mroAddress][ms1] == 1
                && data->data_rom[data->data_mroAddress][ms0] == 1) {//299装数
            data->statu_ld299=true;
        }
    }
    data->signal_we=data->data_rom[data->data_mroAddress][mwe];
    if (data->data_rom[data->data_mroAddress][mc3] == 1
            && data->data_rom[data->data_mroAddress][mc2] == 0
            && data->data_rom[data->data_mroAddress][mc1] == 1) {//AR
        data->signal_ar=true;
    }
    else if (data->data_rom[data->data_mroAddress][mc3] == 1
             && data->data_rom[data->data_mroAddress][mc2] == 1
             && data->data_rom[data->data_mroAddress][mc1] == 0) {//LDPC

        data->statu_ldpc=true;
    }
}

//-------------------部件299-------------------------------------------------------------
// 移位寄存器，选中信号、微指令s1、s0、m
bool _299(systemDataSet *data) {
    QString& busData=data->data_bus;
    bool statu_299b=data->load_shifter_299b && data->statu_299b;
    bool& cy=data->signal_cy;
    char s1=data->data_rom[data->data_mroAddress][ms1];
    char s0=data->data_rom[data->data_mroAddress][ms0];
    char m=data->data_rom[data->data_mroAddress][mm];
    int& _299=data->data_shifter_299b;

    if (s1 == 1 && s0 == 1 ) {//299装入数据
        _299 = busData.toInt(new bool(),16);
    }
    else if(s1 == 0 && s0 == 0 && m == 0){//输出数据
        if (statu_299b == false)return false;
         busData=QString("%1").arg(_299,2,16,QLatin1Char('0'));
//        busData=QString::number(_299);
    }
    else if (s1 == 1 && s0 == 0 && m == 1) {//带进位循环右移1位
        if (statu_299b == false)return false;
        _299 = rorc(_299,cy);
    }
    else if (s1 == 1 && s0 == 0 && m == 0) {//循环右移1位
        if (statu_299b == false)return false;
        _299 = ror(_299);
    }
    else if (s1 == 0 && s0 == 1 && m == 0) {//循环左移
        if (statu_299b == false)return false;
        _299 = rol(_299);
    }
    else if (s1 == 0 && s0 == 1 && m == 1) {//循环带进位左移
        if (statu_299b == false)return false;
        _299 = rolc(_299,cy);
    }
    return true;
}

/// \brief 循环左移
int rol(int val)
{
    int res = (val * 2) % 256 + val / 128;
    return res;
}

/// \brief 循环右移
int ror(int val)
{
    int res = val / 2 + 128 * (val % 2);
    return res;
}

/// \brief 循环带进位左移
int rolc(int val,bool& cy)
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

/// \brief 循环带进位右移
int rorc(int val,bool& cy)
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
/// \brief ALU主控，是否输出(B字段产生)，s3~s0,m,cn,ar(C字段产生，是否影响CY&&ZI)
bool ALU(systemDataSet* data) {
    bool statu_alub=data->statu_alub&&data->load_alu;
    if(statu_alub==false) return true;

    QString& busData=data->data_bus;
    bool& cy=data->signal_cy;
    bool& zi=data->signal_zi;
    bool& ar=data->signal_ar;
    int s3=data->data_rom[data->data_mroAddress][24];
    int s2=data->data_rom[data->data_mroAddress][23];
    int s1=data->data_rom[data->data_mroAddress][22];
    int s0=data->data_rom[data->data_mroAddress][21];
    int m=data->data_rom[data->data_mroAddress][20];
    int cn=data->data_rom[data->data_mroAddress][19];
    int& dr1=data->data_dr1;
    int& dr2=data->data_dr2;

    //QMessageBox::information(nullptr,"","Dr1+Dr2  "+QString::number(data->mroAddress));

    int res=1;
    if (ar) {
        cy = false;
        zi = false;
    }

    if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 0 && m == 0 && cn == 1) {//dr1
        res = dr1;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 0 && m == 0 && cn == 0) {//dr1+1
        res = dr1 + 1;
        if (ar && res>255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 0 && m == 1) {//逻辑  ~dr1
        res = 256 - dr1;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 1 && m == 0 && cn == 1) {// dr1|dr2
        res = dr1 | dr2;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 1 && m == 0 && cn == 0) {// dr1|dr2+1
        res = dr1 | dr2 + 1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 0 && s1 == 0 && s0 == 1 && m == 1) {//逻辑 ~(dr1|dr2)
        res = dr1 | dr2;
        res = 256-res;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 0 && m == 0 && cn == 1) {//A|(~B)
        res = dr1 | (256-dr2);
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 0 && m == 0 && cn == 0) {//A||(~B)+1
        res = (dr1 | (256 - dr2)) + 1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 0 && m == 1) {//逻辑 ~(A|B)
        res = 256 - (dr1 | dr2);
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 1 && m == 0 && cn == 1) {//-1
        res = 255;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 1 && m == 0 && cn == 0) {//0
        res = 0;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 0 && s1 == 1 && s0 == 1 && m == 1) {//逻辑0
        res = 0;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 0 && m == 0 && cn == 1) {//A+(A&~b)
        res = dr1 + (dr1 & (256 - dr2));
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 0 && m == 0 && cn == 0) {//A+(A&~b)+1
        res = dr1 + (dr1 & (256 - dr2))+1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 0 && m == 1) {//逻辑~(a&b)
        res = 256 - (dr1 & dr2);
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 1 && m == 0 && cn == 1) {//(A|B)+(A&~B)
        res = (dr1 | dr2) + (dr1 & (256 - dr2));
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 1 && m == 0 && cn == 0) {//(A|B)+(A&~B)+1
        res = (dr1 | dr2) + (dr1 & (256 - dr2)) + 1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 1 && s1 == 0 && s0 == 1 && m == 1) {//逻辑~dr2
        res = 256 - dr2;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 0 && m == 0 && cn == 1) {//a-b-1
        res = dr1 - dr2 + 255 + 255;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 0 && m == 0 && cn == 0) {//a-b
        res = dr1 - dr2+256;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 0 && m == 1) {//逻辑(a^b)
        res = dr1 ^ dr2;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 1 && m == 0 && cn == 1) {//(A&~B)-1
        res = dr1 & (256 - dr2) + 255;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 1 && m == 0 && cn == 0) {//A&~B
        res = dr1 & (256 - dr2);
        if (ar) {
            cy = true;
        }
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 0 && s2 == 1 && s1 == 1 && s0 == 1 && m == 1) {//逻辑A&~B
        res = dr1 & (256 - dr2);
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 0 && m == 0 && cn == 1) {//A+A&B
        res = dr1 + (dr1 & dr2);
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 0 && m == 0 && cn == 0) {//A+A&B+1
        res = dr1 + (dr1 & dr2) + 1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 0 && m == 1) {//逻辑~A | B   here
        res = 256 - (dr1 & dr2);
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 1 && m == 0 && cn == 1) {//A+B
        res = dr1 + dr2;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 1 && m == 0 && cn == 0) {//A+B+1
        res = dr1 + dr2 + 1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 0 && s1 == 0 && s0 == 1 && m == 1) {//逻辑~(A^B)
        res = 256 - (dr1 ^ dr2);
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 0 && m == 0 && cn == 1) {//(A|~B)+A&B
        res = (dr1 | (256 - dr2)) + (dr1 & dr2);
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 0 && m == 0 && cn == 0) {//(A|~B)+A&B+1
        res = (dr1 | (256 - dr2)) + dr1 & dr2 + 1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 0 && m == 1) {//逻辑B
        res = dr2;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 1 && m == 0 && cn == 1) {//A&B-1
        res = dr1 & dr2 + 255;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 1 && m == 0 && cn == 0) {//A&B
        res = dr1 & dr2;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 0 && s1 == 1 && s0 == 1 && m == 1) {//逻辑A&B
        res = dr1 & dr2;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 0 && m == 0 && cn == 1) {//A+A
        res = dr1 + dr1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 0 && m == 0 && cn == 0) {//A+A+1
        res = dr1 + dr1+1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 0 && m == 1) {//逻辑1
        res = 1;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 1 && m == 0 && cn == 1) {//(A|B)+A
        res = (dr1 | dr2) + dr1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));    }
    else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 1 && m == 0 && cn == 0) {//(A|B)+A+1
        res = (dr1 | dr2) + dr1 + 1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 1 && s1 == 0 && s0 == 1 && m == 1) {//逻辑A|~B
        res = dr1 | (256 - dr2);
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 0 && m == 0 && cn == 1) {//(A|~B)+A
        res = (dr1 | (256 - dr2)) + dr1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 0 && m == 0 && cn == 0) {//(A|~B)+A+1
        res = (dr1 | (256 - dr2)) + dr1 + 1;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 0 && m == 1) {//逻辑A|B
        res = dr1 | dr2;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 1 && m == 0 && cn == 1) {//A-1
        res = dr1 + 255;
        if (ar && res > 255) {
            cy = true;
        }
        res %= 256;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 1 && m == 0 && cn == 0) {//A
        res = dr1;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
    }
    else if (s3 == 1 && s2 == 1 && s1 == 1 && s0 == 1 && m == 1) {//逻辑A
        res = dr1;
        busData=QString("%1").arg(res,2,16,QLatin1Char('0'));
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

bool DR1(systemDataSet* data){
    if(data->statu_lddr1){
        data->data_dr1=data->data_bus.toInt(nullptr,16);
    }
    return true;
}
bool DR2(systemDataSet* data){
    if(data->statu_lddr2){
        data->data_dr2=data->data_bus.toInt(nullptr,16);
    }
    return true;
}

//-------------------部件RAM-------------------------------------------------------------
bool RAM(systemDataSet* data) {
    QString& busData=data->data_bus;
    bool& ce=data->signal_ce;
    bool& we=data->signal_we;
    int& ar=data->data_ar;

    if (ce == false) {//未选中
        return false;
    }

    if (ar > data->ram_row_size) {//Adress max than the ram row range
        QMessageBox::critical(nullptr,"Wrong","<h2>Ar地址数值超出ram范围/Ar address value out of ram range</h2>");
        return false;
    }

    if (we == READ) {
        busData="00";
        busData[0] = data->data_ram[ar][0];
        busData[1] = data->data_ram[ar][1];
        return true;
    }
    else {
        qDebug()<<busData;
        if(busData.length()>=2){

            data->data_ram[ar][0] = busData[0];
            data->data_ram[ar][1] = busData[1];
            return true;
        }else{
            return false;
        }
    }
    return false;
}

//-------------------部件SW(IN)------------------------------------------------------------
bool SW(systemDataSet* data){
    if(data->statu_swb){
        data->data_bus=QString("%1").arg(data->data_swi_input,2,16,QLatin1Char('0'));
        return true;
    }
    return false;
}

//-------------------部件OUT-------------------------------------------------------------
bool LED(systemDataSet* data) {
    if (data->signal_we == READ) {//未输出
        return false;
    }

    if (data->statu_ldled == false){
        return false;
    }

    //LED 直接读取的总线数据
    return true;
}

//-------------------部件PC-------------------------------------------------------------
bool PC(systemDataSet* data){
    //PC需要选中才可运行
    if (data->statu_ldpc == false)return false;

//    qDebug()<<data->statu_ldpc;

    QString& busData=data->data_bus;
    if(data->statu_ldad){
        //PC作为输入，选中信号
        data->data_pc=busData.toInt(nullptr,16);
        return true;
    }else if(data->statu_pcb){
        busData=QString("%1").arg(data->data_pc,2,16,QLatin1Char('0'));
//        QString::number(data->data_pc,16);
        data->data_pc++;//每次输出PC寄存器自增1
        return true;
    }
    return true;
}

//-------------------部件IR-------------------------------------------------------------
/// \brief IR部件
bool IR(systemDataSet* data){
    if(data->statu_ldir){//IR输入
        data->data_ir=data->data_bus.toInt(nullptr,16);
    }else if(data->statu_irb){//IR输出
        data->data_bus=QString("%1").arg(data->data_ir,2,16,QLatin1Char('0'));
//        QString::number(data->data_ir,16);
    }
    return true;
}

//-------------------部件AR-------------------------------------------------------------
/// \brief AR部件
bool AR(systemDataSet* data){
    if(data->statu_ldar){
        //QMessageBox::information(nullptr,"","AR  "+QString::fromStdString(data->busData));
        data->data_ar=data->data_bus.toInt(nullptr,16);
    }
    return true;
}

//-------------------部件Register-------------------------------------------------------------
/// \brief RI作为输出，选中信号、B字段选中类型
bool RIOut(systemDataSet* data) {
    if (data->statu_r0b) {//0000---R0
        data->data_bus=QString("%1").arg(data->data_r0,2,16,QLatin1Char('0'));
//        data->data_bus=QString::number(data->data_r0,16);
    }
    else if (data->statu_r1b) {//0100---R1
                data->data_bus=QString("%1").arg(data->data_r1,2,16,QLatin1Char('0'));
//        data->data_bus=QString::number(data->data_r1,16);
    }
    else if (data->statu_r2b) {//1000---R2
        data->data_bus=QString("%1").arg(data->data_r2,2,16,QLatin1Char('0'));
//        data->data_bus=QString::number(data->data_r2,16);
    }
    else {//1100---ERROR
        return false;
    }
    return true;
}

/// \brief RI作为输入，选中信号（选中类型在A字段以确定）
bool RIIn(systemDataSet* data) {
    if (data->statu_ldr0) {//0000---R0
        data->data_r0=data->data_bus.toInt(nullptr,16);
    }
    else if (data->statu_ldr1) {//0100---R1
        data->data_r1=data->data_bus.toInt(nullptr,16);
    }
    else if (data->statu_ldr2) {//1000---R2
        data->data_r2=data->data_bus.toInt(nullptr,16);
    }
    else {//1100---ERROR
        return false;
    }
    return true;
}

//-------------------转移方式-------------------------------------------------------------

int Oreder(systemDataSet *data)
{
    int mroAddress=data->data_mroAddress;
    int _u6=data->data_rom[mroAddress][6];
    int _u5=data->data_rom[mroAddress][5];
    int _u4=data->data_rom[mroAddress][4];
    int _u3=data->data_rom[mroAddress][3];
    int _u2=data->data_rom[mroAddress][2];
    int _u1=data->data_rom[mroAddress][1];
    return binaToDec(_u6,_u5,_u4, _u3, _u2,_u1);
}

/// \brief P(1)转移，返回下一微地址,不对目前地址变量产生影响
int P1(systemDataSet* data) {
    int mroAddress=data->data_mroAddress;
    int _u6=data->data_rom[mroAddress][6];
    int _u5=data->data_rom[mroAddress][5];
    int _u4=data->data_rom[mroAddress][4];
    int _u3=data->data_rom[mroAddress][3];
    int _u2=data->data_rom[mroAddress][2];
    int _u1=data->data_rom[mroAddress][1];
    mroAddress=binaToDec(_u6,_u5,_u4, _u3, _u2,_u1);
    //第4位为1，仅更新后三位
    if(mroAddress%16/8){
        mroAddress -= mroAddress % 8;
        mroAddress=data->data_ir / 16 + mroAddress;
        return mroAddress;
    }else{
        mroAddress -= mroAddress % 16;
        mroAddress=data->data_ir / 16 + mroAddress;
        return mroAddress;
    }
}

/// \brief P(2)转移，i3、i2的值,返回下一微地址,不对目前地址变量产生影响
int P2(systemDataSet* data) {
    int mroAddress=data->data_mroAddress;
    int _u6=data->data_rom[mroAddress][6];
    int _u5=data->data_rom[mroAddress][5];
    int _u4=data->data_rom[mroAddress][4];
    int _u3=data->data_rom[mroAddress][3];
    int _u2=data->data_rom[mroAddress][2];
    int _u1=data->data_rom[mroAddress][1];
    mroAddress=binaToDec(_u6,_u5,_u4, _u3, _u2,_u1);
    mroAddress -= mroAddress % 4;
    mroAddress=(data->data_ir % 16) / 4 + mroAddress;
    return mroAddress;
}

/// \brief P(3)转移，在zi&&cy均为false时返回false,不对目前地址变量产生影响
int P3(systemDataSet* data) {
    int mroAddress=data->data_mroAddress;
    int _u6=data->data_rom[mroAddress][6];
    int _u5=data->data_rom[mroAddress][5];
    int _u4=data->data_rom[mroAddress][4];
    int _u3=data->data_rom[mroAddress][3];
    int _u2=data->data_rom[mroAddress][2];
    int _u1=data->data_rom[mroAddress][1];
    mroAddress=binaToDec(_u6,_u5,_u4, _u3, _u2,_u1);

    if (data->signal_cy == false && data->signal_zi == false) {
        return mroAddress;
    }
    if ((mroAddress % 32) / 16 == 0) {
        mroAddress += 16;
    }
    return mroAddress;
}

/// \brief P(4)，SWC，SWA转移返回下一微地址,不对目前地址变量产生影响
int P4(systemDataSet* data) {
    int mroAddress=data->data_mroAddress;
    int _u6=data->data_rom[mroAddress][6];
    int _u5=data->data_rom[mroAddress][5];
    int _u4=data->data_rom[mroAddress][4];
    int _u3=data->data_rom[mroAddress][3];
    int _u2=data->data_rom[mroAddress][2];
    int _u1=data->data_rom[mroAddress][1];
    mroAddress=binaToDec(_u6,_u5,_u4, _u3, _u2,_u1);
    mroAddress -= mroAddress % 4;
    mroAddress = mroAddress + data->signal_swc * 2 + data->signal_swa;
    return mroAddress;
    //0+2+1
}



