#include "logpannel.h"
#include "ui_logpannel.h"

LogPannel::LogPannel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogPannel)
{
    ui->setupUi(this);
}

LogPannel::~LogPannel()
{
    delete ui;
}

void LogPannel::addLog(const QString &log)
{
    this->logLine.push_back(log);
    this->freshLog();
}

void LogPannel::saveLog()
{
    this->on_save_btn_clicked();
}


void LogPannel::freshLog()
{
    this->on_fresh_log_clicked();
}

void LogPannel::on_save_btn_clicked()
{
    QString filePath=QFileDialog::getExistingDirectory(this,
                                                       tr("选择保存位置"),
                                                       QDir::currentPath());
    if(!filePath.isEmpty()){
        filePath+="/log_save_file_"+QDateTime::currentDateTime().toString("yy-MM-dd_hh-mm-ss")+".txt";
        QFile saveAsFile(filePath);
retrySaveLog:
        saveAsFile.open(QIODevice::ReadWrite | QIODevice::Text);
        if(saveAsFile.isOpen()==false){
            switch (QMessageBox::critical(this,tr("错误"),tr("日志存保存失败!"),QMessageBox::Retry,QMessageBox::Cancel)){
            case QMessageBox::Retry:{
                goto retrySaveLog;
                break;
            }
            case QMessageBox::Cancel:{
                return;
                break;
            }
            }
        }else{
            QTextStream outStream(&saveAsFile);
            for(auto& line:this->logLine){
                outStream<<line<<"\n";
            }

        }
    }
}

void LogPannel::on_clear_btn_clicked()
{
    this->logLine.clear();
    this->ui->log_editer->setText("");
}


void LogPannel::on_fresh_log_clicked()
{
    QString log;
    for(auto& line:this->logLine){
        log+=line+"\n";
    }
    this->ui->log_editer->setText(log);
}

