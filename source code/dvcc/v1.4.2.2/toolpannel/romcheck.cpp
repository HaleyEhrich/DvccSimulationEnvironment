#include "romcheck.h"
#include "ui_romcheck.h"

ROMCheck::ROMCheck(QWidget *parent,systemDataSet* data) :
    QWidget(parent),
    ui(new Ui::ROMCheck)
{
    ui->setupUi(this);

    this->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));

    //绑定主窗口数据集
    this->data=data;

    this->matchPattrn=new QRegularExpression(("[0-9A-Fa-f]{6,6}"));

    //设置行数
    this->ui->ROMTable->setRowCount(this->data->rom_row_size);

    //设置拉伸适应
    ui->ROMTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->on_freshRom_clicked();
}


ROMCheck::~ROMCheck()
{
    delete ui;
}

///数据刷新接口
bool ROMCheck::freshData(){
    this->on_freshRom_clicked();
    return true;
}

///
/// \brief ROMCheck::getMCInHex 获得微指令16进制码字符串
/// \param row
/// \param dataBack
/// \return
///
bool ROMCheck::getMCInHex(int row,QString& dataBack){
    dataBack.clear();

    if(row>this->data->rom_row_size) return false;

    dataBack.append(this->hexNumberSet[binaToDec(0,0,
                                                 this->data->data_rom[row][8],
            this->data->data_rom[row][7],this->data->data_rom[row][6],this->data->data_rom[row][5])]);
    dataBack.append(this->hexNumberSet[binaToDec(0,0,
                                                 this->data->data_rom[row][4],this->data->data_rom[row][3],this->data->data_rom[row][2],this->data->data_rom[row][1])]);
    dataBack.append(this->hexNumberSet[binaToDec(0,0,
                                                 this->data->data_rom[row][16],this->data->data_rom[row][15],this->data->data_rom[row][14],this->data->data_rom[row][13])]);
    dataBack.append(this->hexNumberSet[binaToDec(0,0,
                                                 this->data->data_rom[row][12],this->data->data_rom[row][11],this->data->data_rom[row][10],this->data->data_rom[row][9])]);
    dataBack.append(this->hexNumberSet[binaToDec(0,0,
                                                 this->data->data_rom[row][24],this->data->data_rom[row][23],this->data->data_rom[row][22],this->data->data_rom[row][21])]);
    dataBack.append(this->hexNumberSet[binaToDec(0,0,
                                                 this->data->data_rom[row][20],this->data->data_rom[row][19],
            this->data->data_rom[row][18],this->data->data_rom[row][17])]);
    return true;
}

///
/// \brief ROMCheck::getB1B0Statu 获得B1B0状态字符串
/// \param row
/// \param dataBack
/// \return
///
bool ROMCheck::getB1B0Statu(int row,QString& dataBack){
    dataBack.clear();

    if(row>this->data->rom_row_size) return false;

    if(this->data->data_rom[row][17]==0&&this->data->data_rom[row][16]==0){
        dataBack="Input";
    }else if(this->data->data_rom[row][17]==0&&this->data->data_rom[row][16]==1){
        dataBack="RAM";
    }else if(this->data->data_rom[row][17]==1&&this->data->data_rom[row][16]==0){
        dataBack="Output";
    }else if(this->data->data_rom[row][17]==1&&this->data->data_rom[row][16]==1){
        dataBack="None";
    }
    return true;
}

bool ROMCheck::getB1B0(int row, QString &dataBack)
{
    dataBack.clear();

    if(row>this->data->rom_row_size) return false;

    if(this->data->data_rom[row][mB1]){
        dataBack+='1';
    }else{
        dataBack+='0';
    }
    if(this->data->data_rom[row][mB0]){
        dataBack+='1';
    }else{
        dataBack+='0';
    }
    return true;
}

///
/// \brief ROMCheck::getAStatu A字符串
/// \param row
/// \param dataBack
/// \return
///
bool ROMCheck::getAStatu(int row,QString& dataBack){
    dataBack.clear();

    if(row>this->data->rom_row_size) return false;

    int _a3= this->data->data_rom[row][ma3];
    int _a2= this->data->data_rom[row][ma2];
    int _a1= this->data->data_rom[row][ma1];
    if (_a3 == 0 && _a2 == 0 && _a1 == 0) {//内部输入设备不选中
        dataBack="None";
    }
    else if (_a3 == 0 && _a2 == 0 && _a1 == 1) {//RiIN
        dataBack="R";
        dataBack.append((char)(this->data->data_ir%4+'0'));
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

bool ROMCheck::getA(int row, QString &dataBack)
{
    dataBack.clear();

    if(row>this->data->rom_row_size) return false;

    if(this->data->data_rom[row][ma3]){
        dataBack+='1';
    }else{
        dataBack+='0';
    }
    if(this->data->data_rom[row][ma2]){
        dataBack+='1';
    }else{
        dataBack+='0';
    }

    if(this->data->data_rom[row][ma1]){
        dataBack+='1';
    }else{
        dataBack+='0';
    }
    return true;
}

///
/// \brief ROMCheck::getBStatu B字符串
/// \param row
/// \param dataBack
/// \return
///
bool ROMCheck::getBStatu(int row,QString& dataBack){
    dataBack.clear();
    if(row>this->data->rom_row_size) return false;

    int _c3=this->data->data_rom[row][mc3];
    int _c2=this->data->data_rom[row][mc2];
    int _c1=this->data->data_rom[row][mc1];
    int _b3=this->data->data_rom[row][mb3];
    int _b2=this->data->data_rom[row][mb2];
    int _b1=this->data->data_rom[row][mb1];

    if (_b3 == 0 && _b2 == 0 && _b1 == 0) {//内部输出设备不存在
        dataBack="NONE";
    }
    else if (_b3 == 0 && _b2 == 0 && _b1 == 1) {//RS-B
        dataBack="R(S)";
        dataBack.append((char)(((this->data->data_ir) % 8)/4+'0'));
    }
    else if (_b3 == 0 && _b2 == 1 && _b1 == 0) {//RD-B
        dataBack="R";
        dataBack.append((char)((this->data->data_ir) % 4+'0'));
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

bool ROMCheck::getB(int row, QString &dataBack)
{
    dataBack.clear();

    if(row>this->data->rom_row_size) return false;

    if(this->data->data_rom[row][mb3]){
        dataBack+='1';
    }else{
        dataBack+='0';
    }
    if(this->data->data_rom[row][mb2]){
        dataBack+='1';
    }else{
        dataBack+='0';
    }
    if(this->data->data_rom[row][mb1]){
        dataBack+='1';
    }else{
        dataBack+='0';
    }

    return true;
}

///
/// \brief ROMCheck::getCStatu C字符串
/// \param row
/// \param dataBack
/// \return
///
bool ROMCheck::getCStatu(int row,QString& dataBack){
    dataBack.clear();
    if(row>this->data->rom_row_size) return false;

    int _c3=this->data->data_rom[row][9];
    int _c2=this->data->data_rom[row][8];
    int _c1=this->data->data_rom[row][7];

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
        dataBack="AR选中\n顺序执行";
    }
    else if (_c3 == 1 && _c2 == 1 && _c1 == 0) {//LDPC
        dataBack="Pc+1\n顺序执行";
    }
    else if (_c3 == 1 && _c2 == 1 && _c1 == 1) {//NONE
        dataBack="NONE";
    }
    return true;
}

bool ROMCheck::getC(int row, QString &dataBack)
{
    dataBack.clear();

    if(row>this->data->rom_row_size) return false;

    if(this->data->data_rom[row][mc3]){
        dataBack+='1';
    }else{
        dataBack+='0';
    }
    if(this->data->data_rom[row][mc2]){
        dataBack+='1';
    }else{
        dataBack+='0';
    }
    if(this->data->data_rom[row][mc1]){
        dataBack+='1';
    }else{
        dataBack+='0';
    }
    return true;
}

///
/// \brief ROMCheck::getNextMroAD 获取下一微地址字符串，未经P跳转处理
/// \param row
/// \param dataBack
/// \return
///
bool ROMCheck::getNextMroAD(int row,QString &dataBack){
    dataBack.clear();

    if(row>this->data->rom_row_size) return false;

    int _u6=this->data->data_rom[row][6];
    int _u5=this->data->data_rom[row][5];
    int _u4=this->data->data_rom[row][4];
    int _u3=this->data->data_rom[row][3];
    int _u2=this->data->data_rom[row][2];
    int _u1=this->data->data_rom[row][1];
    dataBack=QString("%1").arg(binaToDec(_u6,_u5,_u4, _u3, _u2,_u1),
                               6,//Width
                               2,//Hexc
                               QLatin1Char('0')//Fill letter
                               );
    return true;
}

bool ROMCheck::getS3S0(int row, QString &dataBack)
{
    if(row>this->data->rom_row_size) return false;
    dataBack.clear();

    if(this->data->data_rom[row][ms3]){
        dataBack+='1';
    }else{
        dataBack+='0';
    }
    if(this->data->data_rom[row][ms2]){
        dataBack+='1';
    }else{
        dataBack+='0';
    }
    if(this->data->data_rom[row][ms1]){
        dataBack+='1';
    }else{
        dataBack+='0';
    }
    if(this->data->data_rom[row][ms0]){
        dataBack+='1';
    }else{
        dataBack+='0';
    }
    return true;
}

bool ROMCheck::getM(int row, QString &dataBack)
{
    if(row>this->data->rom_row_size) return false;
    dataBack.clear();

    if(this->data->data_rom[row][mm]){
        dataBack='1';
    }else{
        dataBack='0';
    }
    return true;
}

bool ROMCheck::getCn(int row, QString &dataBack)
{
    if(row>this->data->rom_row_size) return false;
    dataBack.clear();

    if(this->data->data_rom[row][mcn]){
        dataBack='1';
    }else{
        dataBack='0';
    }
    return true;
}

bool ROMCheck::getWe(int row, QString &dataBack)
{
    if(row>this->data->rom_row_size) return false;
    dataBack.clear();

    if(this->data->data_rom[row][mwe]){
        dataBack='1';
    }else{
        dataBack='0';
    }
    return true;
}

//数据刷新
void ROMCheck::on_freshRom_clicked()
{
    this->ui->ROMTable->blockSignals(true);
    //初始化数据
    QString hexcOutStirng="000";
    for(int rowIndex=0;rowIndex<this->data->rom_row_size;rowIndex++){
        //输出rom内容
        this->getMCInHex(rowIndex,hexcOutStirng);
        this->ui->ROMTable->setItem(rowIndex,1,new QTableWidgetItem(hexcOutStirng));

        this->getB1B0Statu(rowIndex,hexcOutStirng);
        this->ui->ROMTable->setItem(rowIndex,2,new QTableWidgetItem(hexcOutStirng));

        this->getAStatu(rowIndex,hexcOutStirng);
        this->ui->ROMTable->setItem(rowIndex,3,new QTableWidgetItem(hexcOutStirng));

        this->getBStatu(rowIndex,hexcOutStirng);
        this->ui->ROMTable->setItem(rowIndex,4,new QTableWidgetItem(hexcOutStirng));

        this->getCStatu(rowIndex,hexcOutStirng);
        this->ui->ROMTable->setItem(rowIndex,5,new QTableWidgetItem(hexcOutStirng));

        this->getNextMroAD(rowIndex,hexcOutStirng);
        this->ui->ROMTable->setItem(rowIndex,6,new QTableWidgetItem(hexcOutStirng));

        //输出地址序号
        hexcOutStirng=QString("%1").arg(rowIndex,4,16,QLatin1Char('0'));
        this->ui->ROMTable->setItem(rowIndex,0,new QTableWidgetItem(hexcOutStirng));
    }

    this->ui->ROMTable->blockSignals(false);
}

//数据更改
void ROMCheck::on_ROMTable_itemChanged(QTableWidgetItem *item)
{
    int row=item->row();
    int column=item->column();
    if(column==1){
        if(this->matchPattrn->match(item->text()).hasMatch()){
            //数据保存
            this->updateRomRowData(row,item->text());

        }else{
            item->setText(this->oldText);

        }
    }
}

//保存原始数据
void ROMCheck::on_ROMTable_cellDoubleClicked(int row, int column)
{
    this->oldText=this->ui->ROMTable->item(row,column)->text();
}


//更新表格内容到rom
bool ROMCheck::updateRomRowData(int &row, QString mcString)
{
    if(row>this->data->rom_row_size){
        return false;
    }
    //8 9 10 11
    int trans=hexcToDec(mcString[4]);
    this->data->data_rom[row][ms3] = trans /8;
    this->data->data_rom[row][ms2] = trans % 8 / 4;
    this->data->data_rom[row][ms1] = trans % 8 % 4/2;
    this->data->data_rom[row][ms0] = trans % 8 % 4 % 2;
    trans=hexcToDec(mcString[5]);
    this->data->data_rom[row][mm] = trans /8;
    this->data->data_rom[row][mcn] = trans % 8 / 4;
    this->data->data_rom[row][mwe] = trans % 8 % 4/2;
    this->data->data_rom[row][mB1] = trans % 8 % 4 % 2;
    trans=hexcToDec(mcString[2]);
    this->data->data_rom[row][mB0] = trans /8;
    this->data->data_rom[row][ma3] = trans % 8 / 4;
    this->data->data_rom[row][ma2] = trans % 8 % 4/2;
    this->data->data_rom[row][ma1] = trans % 8 % 4 % 2;
    trans=hexcToDec(mcString[3]);
    this->data->data_rom[row][mb3] = trans /8;
    this->data->data_rom[row][mb2] = trans % 8 / 4;
    this->data->data_rom[row][mb1] = trans % 8 % 4/2;
    this->data->data_rom[row][mc3] = trans % 8 % 4 % 2;
    trans=hexcToDec(mcString[0]);
    this->data->data_rom[row][mc2] = trans /8;
    this->data->data_rom[row][mc1] = trans % 8 / 4;
    this->data->data_rom[row][mu6] = trans % 8 % 4/2;
    this->data->data_rom[row][mu5] = trans % 8 % 4 % 2;
    trans=hexcToDec(mcString[1]);
    this->data->data_rom[row][mu4] = trans /8;
    this->data->data_rom[row][mu3] = trans % 8 / 4;
    this->data->data_rom[row][mu2] = trans % 8 % 4/2;
    this->data->data_rom[row][mu1] = trans % 8 % 4 % 2;
    return true;
}

bool ROMCheck::setEditModel(bool edit){
    this->on_freshRom_clicked();
    this->ui->edit_btn->setChecked(edit);
    this->on_edit_btn_clicked(true);
    if(this->isHidden()==true){
        this->show();
    }
    return true;
}

void ROMCheck::on_edit_btn_clicked(bool checked)
{
    if(checked){
        this->ui->ROMTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        this->ui->edit_btn->setText(tr("编辑"));
        this->ui->ROMCheckTitle->setText(tr("RAM内存"));
    }else{
        this->ui->ROMTable->setEditTriggers(QAbstractItemView::DoubleClicked);
        this->ui->edit_btn->setText(tr("停止编辑"));
        this->ui->ROMCheckTitle->setText(tr("RAM内存(编辑模式)"));
    }
}

