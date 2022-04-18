#include "ramcheck.h"
#include "ui_ramcheck.h"

RAMCheck::RAMCheck(QWidget *parent,systemDataSet* data) :
    QWidget(parent),
    ui(new Ui::RAMCheck)
{
    ui->setupUi(this);

    this->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));

    this->data=data;

    this->ui->RAMTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->matchPattrn=new QRegularExpression(("[0-9A-Fa-f]{2,2}"));

    //设置行数
    this->ui->RAMTable->setRowCount(this->data->ram_row_size);

    on_freshRam_clicked();
}

RAMCheck::~RAMCheck()
{
    delete ui;

}

//数据刷新接口
bool RAMCheck::freshData(){
    this->on_freshRam_clicked();
    return true;
}

//刷新数据
void RAMCheck::on_freshRam_clicked()
{
    this->ui->RAMTable->blockSignals(true);
    //初始化数据
    QString hexcOutStirng="00";
    for(int rowIndex=0;rowIndex<this->data->ram_row_size;rowIndex++){
        //输出ram内容
        hexcOutStirng.clear();
        hexcOutStirng.append(this->data->data_ram[rowIndex][0]);
        hexcOutStirng.append(this->data->data_ram[rowIndex][1]);
        this->ui->RAMTable->setItem(rowIndex,1,new QTableWidgetItem(hexcOutStirng));
        //输出地址序号
        hexcOutStirng=QString("%1").arg(rowIndex,4,16,QLatin1Char('0'));
        this->ui->RAMTable->setItem(rowIndex,0,new QTableWidgetItem(hexcOutStirng));
    }
    this->ui->RAMTable->blockSignals(false);

}

//编辑数据接口
bool RAMCheck::setEditModel(bool edit){
    this->on_freshRam_clicked();
    this->ui->edit_btn->setChecked(edit);
    this->on_edit_btn_clicked(true);
    if(this->isHidden()==true){
        this->show();
    }
    return true;
}

//数据发生变化
void RAMCheck::on_RAMTable_itemChanged(QTableWidgetItem *item)
{
    int row=item->row();
    int column=item->column();
    if(column==1){
        if(this->matchPattrn->match(item->text()).hasMatch()){
            this->data->data_ram[row][0]=this->ui->RAMTable->item(row,column)->text().toStdString()[0];
            this->data->data_ram[row][1]=this->ui->RAMTable->item(row,column)->text().toStdString()[1];
            //TODO tip user input done
        }else{
            item->setText(this->oldText);
            //TODO tip user input uncorrect
        }
    }
}

//表格双击，保存原始文件
void RAMCheck::on_RAMTable_cellDoubleClicked(int row, int column)
{
    this->oldText=this->ui->RAMTable->item(row,column)->text();
}

//选择编辑
void RAMCheck::on_edit_btn_clicked(bool checked)
{
    if(checked){
        this->ui->RAMTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        this->ui->edit_btn->setText(tr("编辑"));
        this->ui->RAMCheckTitle->setText(tr("RAM内存"));
    }else{
        this->ui->RAMTable->setEditTriggers(QAbstractItemView::DoubleClicked);
        this->ui->edit_btn->setText(tr("停止编辑"));
        this->ui->RAMCheckTitle->setText(tr("RAM内存(编辑模式)"));
    }
}

