#include "configset.h"

ConfigSet::ConfigSet()
{

}

bool ConfigSet::loadConfig(QString confFilePath)
{
    QFileInfo fio(confFilePath);
    QSettings* coonfig=new QSettings(confFilePath,QSettings::IniFormat);//Open setting ini file

    if(fio.isFile() && coonfig!=nullptr){
        //gen set
        //lan
        if(coonfig->value("general/language").isValid()){
            this->language=coonfig->value("general/language").value<lanType>();
        }
        //theme
        if(coonfig->value("general/theme").isValid()){
            this->themeName=coonfig->value("general/theme").toString();
        }
        //font family
        if(coonfig->value("general/fontFamily").isValid()){
            this->font.setFamily(coonfig->value("general/fontFamily").toString());
            if(this->installFont(font.family())){
                if(this->installFont(font.family())){
                    font.setFamily("HarmonyOS Sans SC");
                }
            }
        }

        //run set

        //起始地址
        if(coonfig->value("run/startMCAdd").isValid()){
            startMCAddress=coonfig->value("run/startMCAdd").toInt();
        }

        //间隔时间
        if(coonfig->value("run/intervalTime").isValid()){
            defaultIntervalTime=coonfig->value("run/intervalTime").toInt();
        }

        //实时刷新
        if(coonfig->value("run/freshInRealTime").isValid()){
            freshInRealTime=coonfig->value("run/freshInRealTime").toBool();
        }

        //advanced
        if(coonfig->value("advanced/ramRow").isValid()){
            ramRow=coonfig->value("advanced/ramRow").toInt();
        }
        if(coonfig->value("advanced/romRow").isValid()){
            romRow=coonfig->value("advanced/romRow").toInt();
        }
        if(coonfig->value("advanced/ramCol").isValid()){
            ramCol=coonfig->value("advanced/ramCol").toInt();
        }
        if(coonfig->value("advanced/romCol").isValid()){
            romCol=coonfig->value("advanced/romCol").toInt();
        }
        if(coonfig->value("advanced/clearDataWhenChangeStatu").isValid()){
            clearDataWhenChangeStatu=coonfig->value("advanced/clearDataWhenChangeStatu").toBool();
        }
        if(coonfig->value("advanced/openDesigner").isValid()){
            openDesigner=coonfig->value("advanced/openDesigner").toBool();
        }

        //other set
        if(coonfig->value("other/autoCheckUpdate").isValid()){
            autoCheckUpdate=coonfig->value("other/autoCheckUpdate").toBool();
        }

        delete coonfig;
        coonfig=nullptr;

        return true;
    }else{
        this->newConfig(confFilePath);
    }

    if(coonfig!=nullptr){
        delete coonfig;
        coonfig=nullptr;
    }

    return false;


}

bool ConfigSet::saveConfig(QString confFilePath)
{
    QFileInfo fio(confFilePath);
    QSettings* coonfig=new QSettings(confFilePath,QSettings::IniFormat);//Open setting ini file

    if(fio.isFile() && coonfig!=nullptr){
        coonfig->remove("/general");
        //gen set
        //lan
        coonfig->setValue("general/language",this->language);

        //theme
        coonfig->setValue("general/theme",this->themeName);

        //font family
        coonfig->setValue("general/fontFamily",this->font.family());

        //font size
        coonfig->setValue("general/fontSie",this->font.pointSize());

        //window size
        coonfig->setValue("general/winSize",this->defaultWinSize);

        //run set
        coonfig->remove("/run");
        //起始地址
        coonfig->setValue("run/startMCAdd",this->startMCAddress);

        //间隔时间
        coonfig->setValue("run/intervalTime",this->defaultIntervalTime);

        //实时刷新
        coonfig->setValue("run/freshInRealTime",this->freshInRealTime);

        //advanced
        coonfig->remove("/advanced");
        coonfig->setValue("advanced/ramRow",this->ramRow);

        coonfig->setValue("advanced/romRow",this->romRow);

        coonfig->setValue("advanced/ramCol",this->ramCol);

        coonfig->setValue("advanced/romCol",this->romCol);

        coonfig->setValue("advanced/clearDataWhenChangeStatu",this->clearDataWhenChangeStatu);

        coonfig->setValue("advanced/openDesigner",this->openDesigner);

        //other set
        coonfig->remove("/other");
        coonfig->setValue("other/autoCheckUpdate",this->autoCheckUpdate);

        delete coonfig;
        coonfig=nullptr;

        return true;
    }

    if(coonfig!=nullptr){
        delete coonfig;
        coonfig=nullptr;
    }

    return false;
}

bool ConfigSet::newConfig(QString confFilePath)
{
   if(this->setDefaultConfig()){
       QFileInfo fio(confFilePath);
       QSettings* coonfig=new QSettings(confFilePath,QSettings::IniFormat);//Open setting ini file
       //gen set
       //lan
       coonfig->setValue("general/language",this->language);

       //theme
       coonfig->setValue("general/theme",this->themeName);

       //font family
       coonfig->setValue("general/fontFamily",this->font.family());

       //font size
       coonfig->setValue("general/fontSie",this->font.pointSize());

       //window size
       coonfig->setValue("general/winSize",this->defaultWinSize);

       //run set

       //起始地址
       coonfig->setValue("run/startMCAdd",this->startMCAddress);

       //间隔时间
       coonfig->setValue("run/intervalTime",this->defaultIntervalTime);

       //实时刷新
       coonfig->setValue("run/freshInRealTime",this->freshInRealTime);

       //advanced
       coonfig->setValue("advanced/ramRow",this->ramRow);

       coonfig->setValue("advanced/romRow",this->romRow);

       coonfig->setValue("advanced/ramCol",this->ramCol);

       coonfig->setValue("advanced/romCol",this->romCol);

       coonfig->setValue("advanced/clearDataWhenChangeStatu",this->clearDataWhenChangeStatu);

       coonfig->setValue("advanced/openDesigner",this->openDesigner);

       //other set
       coonfig->setValue("other/autoCheckUpdate",this->autoCheckUpdate);

       delete coonfig;
       coonfig=nullptr;

       return true;
   }
   return false;
}

bool ConfigSet::setDefaultConfig()
{
    language=lanType::zh;
    themeName="macQss";
    font.setFamily("HarmonyOS Sans SC");
    font.setPointSize(12);
    font.setWeight(QFont::Normal);

    defaultWinSize.setWidth(1400);
    defaultWinSize.setHeight(800);

    startMCAddress=2;
    defaultIntervalTime=1000;
    freshInRealTime=false;

    ramRow=128;
    romRow=64;
    ramCol=8;
    romCol=25;
    clearDataWhenChangeStatu=true;
    openDesigner=false;

    autoCheckUpdate=false;
    return true;
}

bool ConfigSet::installFont(const QString fontFamName)
{
    //安装字体
    QFile file(QDir::currentPath()+"/resource/file_resource/font/"+fontFamName+".ttf");
    if(file.exists()){
        if(QFile::exists("C:/Windows/Fonts/"+fontFamName+".ttf")){
            return true;
        }
        file.copy(QString("C:/Windows/Fonts/%1.ttf").arg(fontFamName));
        QStringList sl  = QFontDatabase::families();
        if(sl.contains(fontFamName))
        {
            return true;
        }
    }
    return false;
}
