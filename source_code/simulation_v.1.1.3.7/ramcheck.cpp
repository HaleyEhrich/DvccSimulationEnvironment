#include "ramcheck.h"
#include "ui_ramcheck.h"

RAMCheck::RAMCheck(QWidget *parent,_data* data) :
    QWidget(parent),
    ui(new Ui::RAMCheck)
{
    ui->setupUi(this);

    this->data=data;
    this->isFreshData=false;
    this->editAble=false;
    this->matchPattrn=new QRegularExpression(("[0-9ABCDEF]{2,2}"));

    on_freshRam_clicked();
}

RAMCheck::~RAMCheck()
{
    delete ui;
}

//编数据接口
bool RAMCheck::editModel(){
    this->on_freshRam_clicked();
    this->on_editRam_clicked();
    if(this->isHidden()==true){

        this->show();
    }
    return true;
}

//数据刷新接口
bool RAMCheck::freshData(){
    this->on_freshRam_clicked();
    return true;
}

//刷新数据
void RAMCheck::on_freshRam_clicked()
{
    this->isFreshData=true;
    int a1=0;
    int a2=0;
    //初始化数据
    QString dataOut="00";
    for(int i=0;i<256;i++){
        //输出ram内容
        dataOut.clear();
        dataOut.append(this->data->ram[i][0]);
        dataOut.append(this->data->ram[i][1]);
        this->ui->RAMTable->setItem(i,1,new QTableWidgetItem(dataOut));
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
        this->ui->RAMTable->setItem(i,0,new QTableWidgetItem(dataOut));
    }
    this->isFreshData=false;
}

//选着编辑
void RAMCheck::on_editRam_clicked()
{
    if(this->editAble){
        this->ui->RAMTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        this->ui->editRam->setText("编辑");
        this->editAble=false;
        this->ui->RAMCheckTitle->setText("RAM内存");
    }else{
        this->ui->RAMTable->setEditTriggers(QAbstractItemView::DoubleClicked);
        this->ui->editRam->setText("停止编辑");
        this->editAble=true;
        this->ui->RAMCheckTitle->setText("RAM内存(可编辑)");
    }
}

//数据发生变化
void RAMCheck::on_RAMTable_itemChanged(QTableWidgetItem *item)
{
    if(this->isFreshData==false){
        int row=item->row();
        int column=item->column();
        if(column==1){
            if(this->matchPattrn->match(item->text()).hasMatch()){
                this->data->ram[row][0]=this->ui->RAMTable->item(row,column)->text().toStdString()[0];
                this->data->ram[row][1]=this->ui->RAMTable->item(row,column)->text().toStdString()[1];
                this->ui->RAMCheckTitle->setText("RAM内存(编辑已保存)");
            }else{
                item->setText(this->oldText);
            }
        }
    }
}

//表格双击，保存原始文件
void RAMCheck::on_RAMTable_cellDoubleClicked(int row, int column)
{
    this->oldText=this->ui->RAMTable->item(row,column)->text();
}

