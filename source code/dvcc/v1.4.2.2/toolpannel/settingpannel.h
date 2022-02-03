#ifndef SETTINGPANNEL_H
#define SETTINGPANNEL_H

#include <QByteArray>
#include <QDesktopServices>
#include <QDialog>
#include <QDir>
#include <QInputDialog>
#include <QJsonObject>
#include <QMessageBox>
#include <QtNetwork>
#include <QRegularExpression>
#include <QString>
#include <QWidget>

#include "configset.h"
#include "versioninfo.h"


namespace Ui {
class SettingPannel;
}

class SettingPannel : public QDialog
{
    Q_OBJECT

public:

    explicit SettingPannel(QWidget *parent = nullptr);
    ~SettingPannel();

    void callPannel();

    bool initialPannel(QString themeFilePath=QDir::currentPath()+"/resource/file_resource/theme/");

private slots:

    void on_setting_list_currentRowChanged(int currentRow);

    void on_adv_designer_cb_stateChanged(int arg1);

    void on_set_default_set_btn_clicked();

    void on_save_setting_clicked();

    void on_cancel_edit_clicked();

    void on_check_update_btn_clicked();

private:

    bool setUi();

    bool readUi();


    bool loadConfig(QString confFilePath=QDir::currentPath()+"/resource/file_resource/configuration.ini");
    bool saveConfig(QString confFilePath=QDir::currentPath()+"/resource/file_resource/configuration.ini");


    Ui::SettingPannel *ui;

    ConfigSet configSet;

    QRegularExpression keyPattern{"^[0-9]{16}"};
};

#endif // SETTINGPANNEL_H
