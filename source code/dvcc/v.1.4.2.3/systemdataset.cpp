#include "systemdataset.h"
QPen aluBodyPen=QPen(QColor(103, 158, 210),2);
QBrush aluBodyBrush=QBrush(QColor(103, 158, 210));
//
QPen arBodyPen =QPen(QColor(103, 158, 210),2);
QBrush arBodyBrush =QBrush(QColor(103, 158, 210));
//
QPen drBodyPen =QPen(QColor(103, 158, 210),2);
QBrush drBodyBrush =QBrush(QColor(103, 158, 210));
//
QPen inputBodyPen =QPen(QColor(103, 158, 210),2);
QBrush inputBodyBrush =QBrush(QColor(103, 158, 210));
//
QPen irBodyPen =QPen(QColor(103, 158, 210),2);
QBrush irBodyBrush =QBrush(QColor(103, 158, 210));
//
QPen microConBodyPen =QPen(QColor(38, 87, 39),2);
QBrush microConBodyBrush =QBrush(QColor(38, 87, 39));

QPen romBodyPen =QPen(QColor(48, 48, 47),2);
QBrush romBodyBrush=QBrush(QColor(48, 48, 47));

QPen romCirPen =QPen(QColor(48, 48, 47),2);
QBrush romCirBrush =QBrush(QColor(77, 77, 77));

QPen conBodyPen =QPen(QColor(240, 252, 255),2);
QBrush conBodyBrush =QBrush(QColor(240, 252, 255));
//
QPen outputBodyPen =QPen(QColor(103, 158, 210),2);
QBrush outputBodyBrush =QBrush(QColor(103, 158, 210));
//
QPen pcBodyPen =QPen(QColor(103, 158, 210),2);
QBrush pcBodyBrush =QBrush(QColor(103, 158, 210));
//
QPen registerBodyPen =QPen(QColor(103, 158, 210),2);
QBrush registerBodyBrush =QBrush(QColor(103, 158, 210));
//
QPen ramBodyPen =QPen{QColor{48, 48, 47},2};
QBrush ramBodyBrush =QBrush(QColor(48,48,47));
//
QPen ramCirPen =QPen(QColor(48, 48, 47),2);
QBrush ramCirBrush =QBrush(QColor(77, 77, 77));
//
QPen shifterBodyPen =QPen(QColor(103, 158, 210),2);
QBrush shifterBodyBrush =QBrush(QColor(103, 158, 210));
//
QPen signalsLedBodyPen =QPen(QColor(16, 147, 45),2);
QBrush signalsLedBodyBrush =QBrush(QColor(22, 201, 61));
QPen signalsLedBodyPenAct =QPen(QColor(147, 6, 6),2);
QBrush signalsLedBodyBrushAct =QBrush(QColor(204, 11, 11));


//text pen brush
QPen lightTextPen{QColor(255,255,255),0};
QBrush ligthTextBrush{QColor(255,255,255)};
QPen darkTextPen{QColor(0,0,0),0};
QBrush darkTextBrush{QColor(0,0,0)};

//Siganls pen brush
QPen lightSignalsPen =QPen(QColor(255,255,255),0);
QBrush lightSignalsBrush{QColor(255,255,255)};
QPen lightSignalsPenAct =QPen(QColor(255, 117, 0),0);
QBrush lightSignalsBrushAct{QColor(255, 117, 0)};

QPen darkSignalsPen =QPen(QColor(0,0,0),0);
QBrush darkSignalsBrush{QColor(0,0,0)};
QPen darkSignalsPenAct =QPen(QColor(255, 117, 0),0);
QBrush darkSignalsBrushAct{QColor(255, 117, 0)};

//Font
QFont bigNameTextFont =QFont("HarmonyOS Sans SC",20,QFont::Medium);
QFont bigDataTextFont =QFont("HarmonyOS Sans SC",20,QFont::Medium);

QFont smallNameTextFont =QFont("HarmonyOS Sans SC",12,QFont::Medium);
QFont smallDataTextFont =QFont("HarmonyOS Sans SC",16,QFont::Medium);


QFont bigSignalsFont =QFont("HarmonyOS Sans SC",14,QFont::Normal);
QFont smallSignalsFont =QFont("HarmonyOS Sans SC",12,QFont::Normal);

//Line pen brush
QPen linePen{QColor(0,0,0),6};
QBrush lineBrush{QColor(0,0,0)};
QPen linePenAct{QColor(255, 70, 31),6};
QBrush lineBrushAct{QColor(255, 70, 31)};

QPen sigLinePen{QColor(0,0,0),2};
QPen sigLinePenAct{QColor(255, 70, 31),2};


systemDataSet::systemDataSet()
{

}

/// \brief 重置数据集，将所有内容置为false\0; Reset the dataset, set everything to false\0
bool systemDataSet::reSetDataSet(){

    //------------部件加载---------------
    this->load_rom=true;
    this->load_ram=true;
    this->load_ar=true;
    this->load_alu=true;
    this->load_dr1=true;
    this->load_dr2=true;
    this->load_r0=true;
    this->load_r1=true;
    this->load_r2=true;
    this->load_pc=true;
    this->load_ir=true;
    this->load_shifter_299b=true;
    this->load_con=true;

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
    signal_cy=false;
    signal_zi=false;

    //-----主要数据部件------------
    data_bus="00";       //总线数据
    data_ar=0;               //地址寄存器
    data_dr1=0;
    data_dr2=0;              //alu隐含寄存器
    data_r0=0;
    data_r1=0;
    data_r2=0;               //寄存器组
    data_pc=0;                //PC计数器
    data_ir=0;               //指令寄存器
    data_shifter_299b=0;             //299移位寄存器内存
//    data_mroAddress=0;       //微地址寄存器，也即微指令的地址寄存器
//    data_nextMroAddress=0;
    data_startMroAd=2;       //微地址每条指令取值令的第一条微地址
    data_swi_input=0;     //数据开关数据
    data_function_swi=0;    //功能开关数据

    if(this->data_rom!=nullptr){
        for(int row=0;row<this->rom_col_size;++row){
            for(int col=0;col<=25;++col)
                data_rom[row][col]=0;
        }
    }else{
        //rom初始化为0
        this->data_rom=new int*[this->rom_col_size];
        for(int row=0;row<this->rom_col_size;++row){
            this->data_rom[row]=new int[this->rom_col_size];
            for(int col=0;col<=25;++col)
                data_rom[row][col]=0;
        }
    }

    if(this->data_ram!=nullptr){
        //ram初始化
        for(int row=0;row<this->ram_row_size;row++){
            for(int col=0;col<this->ram_col_size;col++)
                data_ram[row][col]='0';
        }
    }else{
        //ram初始化
        this->data_ram=new QChar*[this->ram_row_size];
        for(int row=0;row<this->ram_row_size;row++){
            this->data_ram[row]=new QChar[this->ram_col_size];
            for(int col=0;col<this->ram_col_size;col++)
                data_ram[row][col]='0';
        }
    }


    //--------------临时----------
//    tempString="00";
    return true;
}

/// \brief 重置信号，不包含ZI/CY; Reset signal, not including ZI/CY
bool systemDataSet::reSetSig(){
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

/// \brief 重置ram\rom，将所有内容置为0; Reset ram\rom, set everything to 0
void systemDataSet::resetRaomData()
{
    if(this->data_ram==nullptr || this->data_rom==nullptr){
        //rom初始化为0
        this->data_rom=new int*[this->rom_row_size];
        for(int row=0;row<this->rom_row_size;row++){
            this->data_rom[row]=new int[this->rom_col_size];
            for(int col=0;col<rom_col_size;col++){
                this->data_rom[row][col]=0;
            }
        }

        //ram初始化
        this->data_ram=new QChar*[this->ram_row_size];
        for(int row=0;row<this->ram_row_size;row++){
            this->data_ram[row]=new QChar[this->ram_col_size];
            for(int col=0;col<this->ram_col_size;col++)
                data_ram[row][col]='0';
        }
    }else{
        for(int row=0;row<this->rom_row_size;row++){
            for(int col=0;col<rom_col_size;col++){
                this->data_rom[row][col]=0;
            }
        }

        for(int row=0;row<this->ram_row_size;row++){
            for(int col=0;col<this->ram_col_size;col++)
                data_ram[row][col]='0';
        }
    }

}

QString &systemDataSet::getLogString()
{
    QString* res=new QString("\n");

    *res+="**************************************************\n"
          "数据输出:\n\t";
    if(this->statu_299b){
        *res+="299输出\t";
    }

    if(this->statu_alub){
        *res+="ALU输出\t";
    }

    if(this->statu_pcb && this->statu_ldpc){
        *res+="PC输出\t";
    }

    if(this->signal_ce && this->signal_we==READ){
        *res+="RAM输出\t";
    }

    if(this->statu_r0b){
        *res+="R0输出\t";
    }

    if(this->statu_r1b){
        *res+="R1输出\t";
    }

    if(this->statu_r0b){
        *res+="R2输出\t";
    }

    if(this->statu_swb){
        *res+="SW开关输出\t";
    }

    *res+="\n数据输入:\n\t";
    if(this->statu_ld299){
        *res+="299输入\t";
    }

    if(this->statu_lddr1){
        *res+="DR1输入\t";
    }

    if(this->statu_lddr2){
        *res+="DR2输入\t";
    }

    if(this->statu_ldar){
        *res+="AR输入\t";
    }

    if(this->statu_ldpc && this->statu_ldad){
        *res+="PC输入\t";
    }

    if(this->signal_ce && this->signal_we==WRITE){
        *res+="RAM输入\t";
    }

    if(this->statu_ldr0){
        *res+="R0输入\t";
    }

    if(this->statu_ldr1){
        *res+="R1输入\t";
    }
    if(this->statu_ldr2){
        *res+="R2输入\t";
    }
    if(this->statu_ldir){
        *res+="ir输入\t";
    }
    if(this->statu_ldled && this->signal_we==WRITE){
        *res+="开关输入\t";
    }

    *res+="\n数据:\n\t";
    *res+="BUS "+data_bus+"\n\t";
    *res+="AR "+QString::number(data_ar)+"\n\t";
    *res+="DR1 "+QString::number(data_dr1)+"\n\t";
    *res+="DR2 "+QString::number(data_dr2)+"\n\t";
    *res+="R0 "+QString::number(data_r0)+"\n\t";
    *res+="R1 "+QString::number(data_r1)+"\n\t";
    *res+="R2 "+QString::number(data_r2)+"\n\t";
    *res+="PC "+QString::number(data_pc)+"\n\t";
    *res+="IR "+QString::number(data_ir)+"\n\t";
    *res+="299B "+QString::number(data_shifter_299b)+"\n\t";
    *res+="开关数据 "+QString::number(data_swi_input)+"\n\t";
    *res+="功能开关数据 "+QString::number(data_function_swi)+"\n\t";
    *res+="微指令地址 "+QString::number(data_mroAddress)+"\n\t";
    *res+="下一微指令地址 "+QString::number(data_nextMroAddress)+"\n"
                                                          "**************************************************\n";
    return *res;
}

///
systemDataSet::~systemDataSet(){

}

/// \brief 设置数据集参数，重新生成数据集，可更改ram\rom大小; Set dataset parameters, regenerate dataset, can change ram\rom size
bool systemDataSet::setPara(int ram_row_size, int ram_col_size, int rom_row_size, int rom_col_size)
{
    //-----------
    this->ram_col_size=ram_col_size;
    this->ram_row_size=ram_row_size;
    this->rom_col_size=rom_col_size;
    this->rom_row_size=rom_row_size;
    this->bus_size=ram_row_size;

    //------------部件加载---------------
    this->load_rom=true;
    this->load_ram=true;
    this->load_ar=true;
    this->load_alu=true;
    this->load_dr1=true;
    this->load_dr2=true;
    this->load_r0=true;
    this->load_r1=true;
    this->load_r2=true;
    this->load_pc=true;
    this->load_ir=true;
    this->load_shifter_299b=true;
    this->load_con=true;

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
    data_bus="00";       //总线数据
    data_ar=0;               //地址寄存器
    data_dr1=0;
    data_dr2=0;              //alu隐含寄存器
    data_r0=0;
    data_r1=0;
    data_r2=0;               //寄存器组
    data_pc=0;                //PC计数器
    data_ir=0;               //指令寄存器
    data_shifter_299b=0;             //299移位寄存器内存
    data_mroAddress=0;       //微地址寄存器，也即微指令的地址寄存器
    data_nextMroAddress=0;
    stopMroAddress=2;
    data_startMroAd=2;       //微地址每条指令取值令的第一条微地址
    data_swi_input=0;     //数据开关数据
    data_function_swi=0;    //功能开关数据

    //rom初始化为0
    this->data_rom=new int*[this->rom_row_size];
    for(int row=0;row<this->rom_row_size;row++){
        this->data_rom[row]=new int[this->rom_col_size];
        for(int col=0;col<rom_col_size;col++){
            this->data_rom[row][col]=0;
        }
    }

    //ram初始化
    this->data_ram=new QChar*[this->ram_row_size];
    for(int row=0;row<this->ram_row_size;row++){
        this->data_ram[row]=new QChar[this->ram_col_size];
        for(int col=0;col<this->ram_col_size;col++)
            data_ram[row][col]='0';
    }

    //--------------临时----------
    tempString="00";

    //--------------绘图使用--------------
    this->zoomXPer=1.0;
    this->zoomYPer=1.0;

    return true;
}
