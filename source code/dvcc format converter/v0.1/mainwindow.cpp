#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString *MainWindow::convToStd(QString softMCLines)
{
    QString* res=new QString();
    QStringList microCodeList=softMCLines.split("\n");
    for(auto& line:microCodeList){
        if(ramLineNewPattern.match(line).hasMatch()){//Ram
            (*res)+="$P"+line.mid(4)+"\n";
        }else if(romLineNewPattern.match(line).hasMatch()){//rom
            (*res)+="$M"+line.mid(4)+"\n";
        }else{
            (*res)+=line+'\n';
        }
    }
    return res;
}

QString *MainWindow::convToSoft(QString stdMCLines)
{
    QString* res=new QString();
    QStringList microCodeList=stdMCLines.split("\n");
    for(auto& line:microCodeList){
        if(ramLineOldPattern.match(line).hasMatch()){//Ram
            (*res)+="$P00"+line.mid(2)+'\n';
        }else if(romLineOldPattern.match(line).hasMatch()){//rom
            (*res)+="$M00"+line.mid(2)+'\n';
        }else{
            (*res)+=line+'\n';
        }
    }
    return res;
}

///Formate to stander code type
void MainWindow::on_conv_to_std_clicked()
{
    this->ui->std_mc->setText(*convToStd(this->ui->soft_mc->toPlainText()));
}

///Formate to soft code type
void MainWindow::on_conv_to_soft_clicked()
{
    this->ui->soft_mc->setText(*convToSoft(this->ui->std_mc->toPlainText()));
}


