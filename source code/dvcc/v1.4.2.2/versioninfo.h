#ifndef VERSIONINFO_H
#define VERSIONINFO_H

#include <QJsonObject>
#include <QObject>
#include <QMap>
#include <QMessageBox>
#include <QString>
#include <QtNetwork>
#include <QUrl>

static QString VERSION{"v1.4.2.2"};// 当前版本
static QUrl VERSIONURL{"https://api.github.com/repos/HaleyEhrich/DvccSimulationEnvironment/releases/latest"};// 获取当前最新版本的地址

class versionInfo
{ 
public:
    versionInfo();

    bool newVersion();

    QString getVersionInfo();

    QString getDownloadUrl();

    QString getUpdateDetail();

private:

    bool getJson=false;

    bool getGitInfo();

    QJsonObject resJson;
};

#endif // VERSIONINFO_H
