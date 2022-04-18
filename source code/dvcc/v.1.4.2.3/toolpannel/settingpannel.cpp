#include "settingpannel.h"
#include "ui_settingpannel.h"

SettingPannel::SettingPannel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingPannel)
{
    ui->setupUi(this);
}

SettingPannel::~SettingPannel()
{
    delete ui;
}

void SettingPannel::callPannel()
{

    this->loadConfig();
    this->initialPannel();
    this->setUi();

    if(this->isHidden()==false){
        this->hide();
    }

    if(this->isMinimized()){
        this->showNormal();
    }else{
        this->show();
    }

    this->setWindowFlags(Qt::Window);
    this->exec();
}

bool SettingPannel::initialPannel(QString themeFilePath)
{
    //主题cb设置
    QDir dir(themeFilePath);
    if(dir.exists()){
        //查看路径中后缀为.cfg格式的文件
        QStringList filters;
        filters<<QString("*.qss");
        dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
        dir.setNameFilters(filters);  //设置文件名称过滤器，只为filters格式
        int file_count=dir.count();
        if(file_count>0){
            for(int i=0; i<file_count; i++)
            {
                this->ui->gen_theme_cb->addItem(dir[i].split(".")[0],themeFilePath+dir[i]);
            }
        }
    }

    return true;
}

void SettingPannel::on_setting_list_currentRowChanged(int currentRow)
{
    this->ui->setting_page_stack->setCurrentIndex(currentRow);

}

bool SettingPannel::setUi()
{
    //Language
    switch ((int)this->configSet.language){
    case (int)ConfigSet::lanType::zh :{
        this->ui->gen_lan_cb->setCurrentIndex((int)ConfigSet::lanType::zh);
        break;
    }
    case (int)ConfigSet::lanType::en :{
        //TODO translater
        break;
    }
    default:{
        this->ui->gen_lan_cb->setCurrentIndex((int)ConfigSet::lanType::zh);
    }
    }

    //theme
    this->ui->gen_theme_cb->blockSignals(true);
    this->ui->gen_theme_cb->setCurrentText(this->configSet.themeName);
    if(this->ui->gen_theme_cb->currentIndex()==-1){
        //TODO styleFile not exist
    }
    this->ui->gen_theme_cb->blockSignals(false);

    //font
    this->ui->gen_font_fam_cb->setCurrentText(this->configSet.font.family());
    this->ui->gen_font_size_sp->setValue(this->configSet.font.pointSize());

    //win size
    this->ui->gen_win_size_w_sp->setValue(this->configSet.defaultWinSize.width());
    this->ui->gen_win_size_h_sp->setValue(this->configSet.defaultWinSize.height());

    //start cmd add
    this->ui->run_cmd_start_sp->setValue(this->configSet.startMCAddress);

    //interval time
    this->ui->run_cmd_interval_slider->setValue(this->configSet.defaultIntervalTime);
    this->ui->run_cmd_interval_value_la->setText(QString::number(this->configSet.defaultIntervalTime));

    //in real-time fresh
    this->ui->run_real_fresh_cb->setChecked(this->configSet.freshInRealTime);

    //ram
    this->ui->adv_ram_row_sp->setValue(this->configSet.ramRow);
    this->ui->adv_rom_row_sp->setValue(this->configSet.romRow);

    this->ui->adv_bits_sp->setValue(this->configSet.ramCol);

    this->ui->adv_designer_cb->blockSignals(true);
    this->ui->adv_designer_cb->setChecked(this->configSet.openDesigner);
    this->ui->adv_designer_cb->blockSignals(false);

    return true;
}

bool SettingPannel::readUi()
{
    //Language
    switch (this->ui->gen_lan_cb->currentIndex()){
    case (int)ConfigSet::lanType::zh :{
        this->configSet.language=ConfigSet::lanType::zh;
        break;
    }
    case (int)ConfigSet::lanType::en :{
        this->configSet.language=ConfigSet::lanType::en;
        break;
    }
    default:{
        this->configSet.language=ConfigSet::lanType::zh;
    }
    }

    //theme
    this->configSet.themeName=this->ui->gen_theme_cb->currentText();

    //font
    this->configSet.font.setFamily(this->ui->gen_font_fam_cb->currentText());
    this->configSet.font.setPointSize( this->ui->gen_font_size_sp->value());

    //win size
    this->configSet.defaultWinSize.setWidth(this->ui->gen_win_size_w_sp->value());
    this->configSet.defaultWinSize.setHeight(this->ui->gen_win_size_h_sp->value());

    //start cmd add
    this->configSet.startMCAddress=this->ui->run_cmd_start_sp->value();


    //interval time
    this->configSet.defaultIntervalTime=this->ui->run_cmd_interval_slider->value();

    //in real-time fresh
    this->configSet.freshInRealTime=this->ui->run_real_fresh_cb->isChecked();

    //ram
    this->configSet.ramRow=this->ui->adv_ram_row_sp->value();
    this->configSet.romRow=this->ui->adv_rom_row_sp->value();
    this->configSet.ramCol=this->ui->adv_bits_sp->value();
    this->configSet.openDesigner=this->ui->adv_designer_cb->isChecked();

    return true;
}

bool SettingPannel::loadConfig(QString confFilePath)
{
#ifdef QT_NO_DEBUG
    this->configSet.loadConfig(confFilePath);
#else
    qDebug()<<"settingpannel line 173 debumacro set";
    this->configSet.loadConfig("D:/文档/项目文件/软件/DVCC/DVCC模拟环境/版本发布/version 1.4.2.2/resource/resource/file_resource/configuration.ini");
#endif
    return true;
}

bool SettingPannel::saveConfig(QString confFilePath)
{

    if(this->readUi()){
        this->configSet.saveConfig(confFilePath);
    }
    return true;
}

void SettingPannel::on_adv_designer_cb_stateChanged(int arg1)
{
    if(arg1){
        QString text = QInputDialog::getMultiLineText(this,tr("密钥验证"),tr("在此输入16位密钥"));
        if(!text.isEmpty()){
            if(keyPattern.match(text).hasMatch()){
                int part1=QString(text.mid(0,4)).toInt();
                int part2=QString(text.mid(4,4)).toInt();
                int part3=QString(text.mid(8,4)).toInt();
                int part4=QString(text.mid(12,4)).toInt();

                if(part1%2==0 && part2%5==0 && part3%7==0 && part4%9==0){
                    QMessageBox::information(nullptr,tr("提示"),tr("激活成功，保存设置后，下次打开即可使用设计器"));
                    return;
                }else{
                    QMessageBox::information(nullptr,tr("错误"),tr("输入的密钥不正确"));
                }
            }else{
                QMessageBox::information(nullptr,tr("错误"),tr("输入的密钥格式正确"));
            }
        }

    }
    this->ui->adv_designer_cb->blockSignals(true);
    this->ui->adv_designer_cb->setChecked(false);
    this->ui->adv_designer_cb->blockSignals(false);
    //1232-xxxx-xxxx-xxxx

}

void SettingPannel::on_set_default_set_btn_clicked()
{
    this->configSet.setDefaultConfig();
    this->setUi();
}

void SettingPannel::on_save_setting_clicked()
{
    this->readUi();
    this->configSet.saveConfig();
}

void SettingPannel::on_cancel_edit_clicked()
{
    this->close();
}

void SettingPannel::on_check_update_btn_clicked()
{
    versionInfo versionInfo;
    if(versionInfo.newVersion()){
        QMessageBox a(this);
        a.setWindowTitle(tr("发现新版本!"));
        a.setText(QString("<h2>New Version %1</h2>"
                          "<h2>Detail:</h2>"
                          "<p>%2</p>"
                          "<h2>是否下载?</h2>")
                  .arg(versionInfo.getVersionInfo())
                  .arg(versionInfo.getUpdateDetail()));
        a.setTextFormat(Qt::RichText);
        a.addButton(QMessageBox::Cancel);
        a.addButton(tr("跳转下载页面"), QMessageBox::ActionRole);
        a.exec();
        if(a.result()!=QMessageBox::Cancel){
            QDesktopServices::openUrl(QUrl(versionInfo.getDownLoadPageUrl()));
        }
    }else{
        QMessageBox a(this);
        a.setWindowTitle(tr("无更新!"));
        a.setText(QString("<h2>恭喜啦，你的版本是最新的呢 :) </h2>"));
        a.setTextFormat(Qt::RichText);
        a.addButton(QMessageBox::Ok);
        a.exec();
    }
}

