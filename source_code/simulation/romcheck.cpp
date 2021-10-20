#include "romcheck.h"
#include "ui_romcheck.h"

ROMCheck::ROMCheck(QWidget *parent,_data* data) :
    QWidget(parent),
    ui(new Ui::ROMCheck)
{
    ui->setupUi(this);
    this->data=data;
    this->isFreshData=false;
    this->editAble=false;
    this->matchPattrn=new QRegularExpression(("[0-9ABCDEF]{6,6}"));

    this->on_freshRom_clicked();

}

ROMCheck::~ROMCheck()
{
    delete ui;
}

//数据编辑接口
bool ROMCheck::editModel(){
    this->on_freshRom_clicked();
    this->on_editRom_clicked();
    if(this->isHidden()==true){
        this->show();
    }
    return true;
}

//数据刷新接口
bool ROMCheck::freshData(){
    this->on_freshRom_clicked();
    return true;
}

//获得指令的2进制码
bool ROMCheck::getBin(int& row){
    std::string temp;
    int sequce[]={4,5,2,3,0,1};
    int k=0;
    for(int i=24;i>0;){
        dataHTransB(this->data->tempString[sequce[k++]],temp);
        for(int j=0;j<=3;++j,--i){
            this->data->rom[row][i]=temp[j];
        }
    }


    return true;
}

//获得微指令16进制码
bool ROMCheck::getHex(int row,QString& dataBack){
    dataBack.clear();
    dataBack.append(this->hexNumberSet[dataBTransD(0,0,this->data->rom[row][8],this->data->rom[row][7],this->data->rom[row][6],this->data->rom[row][5])]);
    dataBack.append(this->hexNumberSet[dataBTransD(0,0,this->data->rom[row][4],this->data->rom[row][3],this->data->rom[row][2],this->data->rom[row][1])]);

    dataBack.append(this->hexNumberSet[dataBTransD(0,0,this->data->rom[row][16],this->data->rom[row][15],this->data->rom[row][14],this->data->rom[row][13])]);
    dataBack.append(this->hexNumberSet[dataBTransD(0,0,this->data->rom[row][12],this->data->rom[row][11],this->data->rom[row][10],this->data->rom[row][9])]);

    dataBack.append(this->hexNumberSet[dataBTransD(0,0,this->data->rom[row][24],this->data->rom[row][23],this->data->rom[row][22],this->data->rom[row][21])]);
    dataBack.append(this->hexNumberSet[dataBTransD(0,0,this->data->rom[row][20],this->data->rom[row][19],this->data->rom[row][18],this->data->rom[row][17])]);

    return true;
}

//获得B1B0状态
bool ROMCheck::getB1B0Statu(int row,QString& dataBack){
    dataBack.clear();
    if(this->data->rom[row][17]==0&&this->data->rom[row][16]==0){
        dataBack="Input";
    }else if(this->data->rom[row][17]==0&&this->data->rom[row][16]==1){
        dataBack="RAM";
    }else if(this->data->rom[row][17]==1&&this->data->rom[row][16]==0){
        dataBack="Output";
    }else if(this->data->rom[row][17]==1&&this->data->rom[row][16]==1){
        dataBack="None";
    }
    return true;
}

//A
bool ROMCheck::getAStatu(int row,QString& dataBack){
    dataBack.clear();
    int _a3= this->data->rom[row][15];
    int _a2= this->data->rom[row][14];
    int _a1= this->data->rom[row][13];
    if (_a3 == 0 && _a2 == 0 && _a1 == 0) {//内部输入设备不选中
        dataBack="None";
    }
    else if (_a3 == 0 && _a2 == 0 && _a1 == 1) {//RiIN
        dataBack="R";
        dataBack.append((char)(this->data->ir%4+'0'));
    }
    else if (_a3 == 0 && _a2 == 1 && _a1 == 0) {//DR1
        dataBack="DR1";
    }
    else if (_a3 == 0 && _a2 == 1 && _a1 == 1) {//DR2
        dataBack="DR2";
    }
    else if (_a3 == 1 && _a2 == 0 && _a1 == 0) {//LDIR
        dataBack="IR";
    }
    else if (_a3 == 1 && _a2 == 0 && _a1 == 1) {//LDAD(PC)
        dataBack ="PC";
    }
    else if (_a3 == 1 && _a2 == 1 && _a1 == 0) {//LDAR
        dataBack="AR";
    }
    else if (_a3 == 1 && _a2 == 1 && _a1 == 1) {//NONE
        dataBack="NONE";
    }
    return true;
}

//B
bool ROMCheck::getBStatu(int row,QString& dataBack){
    dataBack.clear();
    int _c3=this->data->rom[row][9];
    int _c2=this->data->rom[row][8];
    int _c1=this->data->rom[row][7];
    int _b3=this->data->rom[row][12];
    int _b2=this->data->rom[row][11];
    int _b1=this->data->rom[row][10];

    if (_b3 == 0 && _b2 == 0 && _b1 == 0) {//内部输出设备不存在
           dataBack="NONE";
    }
    else if (_b3 == 0 && _b2 == 0 && _b1 == 1) {//RS-B
        dataBack="R(S)";
        dataBack.append((char)(((this->data->ir) % 8)/4+'0'));
    }
    else if (_b3 == 0 && _b2 == 1 && _b1 == 0) {//RD-B
        dataBack="R";
        dataBack.append((char)((this->data->ir) % 4+'0'));
    }
    else if (_b3 == 0 && _b2 == 1 && _b1 == 1) {//RI-B(选R2）
        dataBack="R2";
    }
    else if (_b3 == 1 && _b2 == 0 && _b1 == 0) {//299-B
        dataBack="299";
    }
    else if (_b3 == 1 && _b2 == 0 && _b1 == 1) {//ALU-B
        if (_c3 == 1 && _c2 == 0 && _c1 == 1) {//AR是否有效
           dataBack="ALU(AR)";
        }
        else {
            dataBack="ALU";
        }
    }
    else if (_b3 == 1 && _b2 == 1 && _b1 == 0) {//PC-B
            dataBack="PC";
    }
    else if (_b3 == 1 && _b2 == 1 && _b1 == 1) {//NOne
        dataBack="NONE";
    }
    return true;
}

//C
bool ROMCheck::getCStatu(int row,QString& dataBack){
    dataBack.clear();
    int _c3=this->data->rom[row][9];
    int _c2=this->data->rom[row][8];
    int _c1=this->data->rom[row][7];

    if (_c3 == 0 && _c2 == 0 && _c1 == 0) {//顺序执行
        dataBack="顺序执行";
    }
    else if (_c3 == 0 && _c2 == 0 && _c1 == 1) {//P(1)
        dataBack="P(1)";
    }
    else if (_c3 == 0 && _c2 == 1 && _c1 == 0) {//P(2)
        dataBack="p(2)";
    }
    else if (_c3 == 0 && _c2 == 1 && _c1 == 1) {//P(3)
        dataBack="p(3)";
    }
    else if (_c3 == 1 && _c2 == 0 && _c1 == 0) {//P(4)
      dataBack="p(4)";
    }
    else if (_c3 == 1 && _c2 == 0 && _c1 == 1) {//AR
        dataBack="AR选中+顺序执行";
    }
    else if (_c3 == 1 && _c2 == 1 && _c1 == 0) {//LDPC
        dataBack="Pc+1+顺序执行";
    }
    else if (_c3 == 1 && _c2 == 1 && _c1 == 1) {//NONE
        dataBack="NONE";
    }
    return true;
}

//获取下一微地址
bool ROMCheck::getNextMroAD(int row,QString &dataBack){
    dataBack.clear();
    int _u6=this->data->rom[row][6];
    int _u5=this->data->rom[row][5];
    int _u4=this->data->rom[row][4];
    int _u3=this->data->rom[row][3];
    int _u2=this->data->rom[row][2];
    int _u1=this->data->rom[row][1];

    dataDTransH(dataBTransD(_u6,_u5,_u4, _u3, _u2,_u1),this->data->tempString);
    dataBack=QString::fromStdString(this->data->tempString);

    return true;
}

//编辑数据
void ROMCheck::on_editRom_clicked()
{
    if(this->editAble){
        this->ui->ROMTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        this->ui->editRom->setText("编辑");
        this->editAble=false;
        this->ui->ROMCheckTitle->setText("RAM内存");
    }else{
        this->ui->ROMTable->setEditTriggers(QAbstractItemView::DoubleClicked);
        this->ui->editRom->setText("停止编辑");
        this->editAble=true;
        this->ui->ROMCheckTitle->setText("RAM内存(可编辑)");
    }
}

//数据刷新
void ROMCheck::on_freshRom_clicked()
{
    this->isFreshData=true;
    int a1=0;
    int a2=0;
    //初始化数据
    QString dataOut="000";
    for(int i=0;i<100;i++){
        //输出rom内容
        this->getHex(i,dataOut);
        this->ui->ROMTable->setItem(i,1,new QTableWidgetItem(dataOut));

        this->getB1B0Statu(i,dataOut);
        this->ui->ROMTable->setItem(i,2,new QTableWidgetItem(dataOut));

        this->getAStatu(i,dataOut);
        this->ui->ROMTable->setItem(i,3,new QTableWidgetItem(dataOut));

        this->getBStatu(i,dataOut);
        this->ui->ROMTable->setItem(i,4,new QTableWidgetItem(dataOut));

        this->getCStatu(i,dataOut);
        this->ui->ROMTable->setItem(i,5,new QTableWidgetItem(dataOut));

        this->getNextMroAD(i,dataOut);
        this->ui->ROMTable->setItem(i,6,new QTableWidgetItem(dataOut));

        //输出地址序号
        dataOut.clear();
        dataOut.append(this->hexNumberSet[a1]);
        dataOut.append(this->hexNumberSet[a2]);
        if(a2==15){
            a2=0;
            a1++;
        }else{
            a2++;
        }
        this->ui->ROMTable->setItem(i,0,new QTableWidgetItem(dataOut));
    }
    this->isFreshData=false;
}

//数据更改
void ROMCheck::on_ROMTable_itemChanged(QTableWidgetItem *item)
{
    if(this->isFreshData==false){
        int row=item->row();
        int column=item->column();
        if(column==1){
            if(this->matchPattrn->match(item->text()).hasMatch()){
                //数据保存地点
                this->data->tempString=item->text().toStdString();
                this->getBin(row);
                this->ui->ROMCheckTitle->setText("ROM内存(编辑已保存)");
            }else{
                item->setText(this->oldText);
            }
        }
    }
}

//保存原始数据
void ROMCheck::on_ROMTable_cellDoubleClicked(int row, int column)
{
    this->oldText=this->ui->ROMTable->item(row,column)->text();
}
