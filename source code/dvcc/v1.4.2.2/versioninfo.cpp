#include "versioninfo.h"

versionInfo::versionInfo()
{

}

bool versionInfo::getGitInfo(){

    if(this->getJson){
        return true;
    }
    QNetworkAccessManager *m_pHttpMgr = new QNetworkAccessManager();
    QNetworkRequest requestInfo;
    requestInfo.setUrl(VERSIONURL);

    QNetworkReply *reply =  m_pHttpMgr->get(requestInfo);
    QTimer wait_timer;
    // eventloop用于阻塞等待消息，并结合timer进行超时处理
    wait_timer.start(3000);

    QEventLoop waitNetStopLoop;

    QObject::connect(reply, SIGNAL(finished()), &waitNetStopLoop, SLOT(quit()));
    QObject::connect(&wait_timer, SIGNAL(timeout()), &waitNetStopLoop, SLOT(quit()));

    waitNetStopLoop.exec();

    // 这里的eventloop只是阻塞此段，并不会阻塞其他块的代码，比如我不加定时器，让这个eventloop一直exec，还是可以出发相关的槽函数
    bool ok=false;
    if(wait_timer.isActive())
    {
        wait_timer.stop();
        if(reply->error() == QNetworkReply::NoError){
            QByteArray responseByte = reply->readAll();
            this->resJson = QJsonDocument::fromJson(responseByte).object();
            //TODO json suc judge
            ok=true;
            this->getJson=true;
        }else{
            QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
            QMessageBox::critical(nullptr,QObject::tr("网络错误"),
                                  QString("request protobufHttp found error ....code: %1 %2\n")
                                  .arg(statusCodeV.toInt())
                                  .arg((int)reply->error()));
        }
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("网络超时"),QObject::tr("超时，请检查您的网络连接"));
    }
    waitNetStopLoop.deleteLater();
    wait_timer.deleteLater();
    // 释放资源
    reply->abort();
    return ok;
}

bool versionInfo::newVersion(){
    QString resVer=this->getVersionInfo();
    if(!resVer.isEmpty() && resVer>VERSION){
        return true;
    }
    return false;
}

QString versionInfo::getVersionInfo(){
    if(this->getGitInfo()){
        return this->resJson["tag_name"].toString();
    }
    return "";
}

QString versionInfo::getDownloadUrl(){
    if(this->getGitInfo()){
        return this->resJson["zipball_url"].toString();
    }
    return "";
}

QString versionInfo::getUpdateDetail(){
    if(this->getGitInfo()){
        return this->resJson["body"].toString();
    }
    return "";
}
