#ifndef CONFIGSET_H
#define CONFIGSET_H

#include <QBrush>
#include <QDialog>
#include <QDir>
#include <QFile>
#include <QFont>
#include <QFontDatabase>
#include <QPen>
#include <QSettings>
#include <QSize>
#include <QString>
#include <QVariant>

class ConfigSet
{

public:
    enum lanType{zh=0,en=1};

    lanType language=lanType::zh;
    QString themeName{"macQss"};
    QFont font{"HarmonyOS Sans SC",12,QFont::Normal};
    QSize defaultWinSize{1400,800};
    int startMCAddress{2};
    int defaultIntervalTime{1000};
    bool freshInRealTime{false};
    int ramRow=128;
    int romRow=64;
    int ramCol=8;
    int romCol=25;
    bool clearDataWhenChangeStatu{true};
    bool openDesigner{false};
    bool autoCheckUpdate{false};

public:

    ConfigSet();

    bool loadConfig(QString confFilePath=QDir::currentPath()+"/resource/file_resource/configuration.ini");
    bool saveConfig(QString confFilePath=QDir::currentPath()+"/resource/file_resource/configuration.ini");
    bool newConfig(QString confFilePath=QDir::currentPath()+"/resource/file_resource/configuration.ini");

    bool setDefaultConfig();

private:


    bool installFont(const QString fontFamName);

};

//    QPen aluBodyPen=QPen(QColor(103, 158, 210),2);
//    QBrush aluBodyBrush=QBrush(QColor(103, 158, 210));
//    //
//    QPen arBodyPen =QPen(QColor(103, 158, 210),2);
//    QBrush arBodyBrush =QBrush(QColor(103, 158, 210));
//    //
//    QPen drBodyPen =QPen(QColor(103, 158, 210),2);
//    QBrush drBodyBrush =QBrush(QColor(103, 158, 210));
//    //
//    QPen inputBodyPen =QPen(QColor(103, 158, 210),2);
//    QBrush inputBodyBrush =QBrush(QColor(103, 158, 210));
//    //
//    QPen irBodyPen =QPen(QColor(103, 158, 210),2);
//    QBrush irBodyBrush =QBrush(QColor(103, 158, 210));
//    //
//    QPen microConBodyPen =QPen(QColor(38, 87, 39),2);
//    QBrush microConBodyBrush =QBrush(QColor(38, 87, 39));
//    QPen romBodyPen =QPen(QColor(48, 48, 47),2);
//    QBrush romBodyBrush=QBrush(QColor(48, 48, 47));
//    QPen romCirPen =QPen(QColor(48, 48, 47),2);
//    QBrush romCirBrush =QBrush(QColor(77, 77, 77));
//    QPen conBodyPen =QPen(QColor(240, 252, 255),2);
//    QBrush conBodyBrush =QBrush(QColor(240, 252, 255));
//    //
//    QPen outputBodyPen =QPen(QColor(103, 158, 210),2);
//    QBrush outputBodyBrush =QBrush(QColor(103, 158, 210));
//    //
//    QPen pcBodyPen =QPen(QColor(103, 158, 210),2);
//    QBrush pcBodyBrush =QBrush(QColor(103, 158, 210));
//    //
//    QPen registerBodyPen =QPen(QColor(103, 158, 210),2);
//    QBrush registerBodyBrush =QBrush(QColor(103, 158, 210));
//    //
//    QPen ramBodyPen =QPen{QColor{48, 48, 47},2};
//    QBrush ramBodyBrush =QBrush(QColor(48,48,47));
//    //
//    QPen ramCirPen =QPen(QColor(48, 48, 47),2);
//    QBrush ramCirBrush =QBrush(QColor(77, 77, 77));
//    //
//    QPen shifterBodyPen =QPen(QColor(103, 158, 210),2);
//    QBrush shifterBodyBrush =QBrush(QColor(103, 158, 210));
//    //
//    QPen signalsLedBodyPen =QPen(QColor(16, 147, 45),2);
//    QBrush signalsLedBodyBrush =QBrush(QColor(22, 201, 61));
//    QPen signalsLedBodyPenAct =QPen(QColor(147, 6, 6),2);
//    QBrush signalsLedBodyBrushAct =QBrush(QColor(204, 11, 11));
//    //text pen brush
//    QPen lightTextPen{QColor(255,255,255),0};
//    QBrush ligthTextBrush{QColor(255,255,255)};
//    QPen darkTextPen{QColor(0,0,0),0};
//    QBrush darkTextBrush{QColor(0,0,0)};
//    //Siganls pen brush
//    QPen lightSignalsPen =QPen(QColor(255,255,255),0);
//    QBrush lightSignalsBrush{QColor(255,255,255)};
//    QPen lightSignalsPenAct =QPen(QColor(255, 117, 0),0);
//    QBrush lightSignalsBrushAct{QColor(255, 117, 0)};
//    QPen darkSignalsPen =QPen(QColor(0,0,0),0);
//    QBrush darkSignalsBrush{QColor(0,0,0)};
//    QPen darkSignalsPenAct =QPen(QColor(255, 117, 0),0);
//    QBrush darkSignalsBrushAct{QColor(255, 117, 0)};
//    //Font
//    QFont bigNameTextFont =QFont("HarmonyOS Sans SC",20,QFont::Medium);
//    QFont bigDataTextFont =QFont("HarmonyOS Sans SC",20,QFont::Medium);
//    QFont smallNameTextFont =QFont("HarmonyOS Sans SC",12,QFont::Medium);
//    QFont smallDataTextFont =QFont("HarmonyOS Sans SC",16,QFont::Medium);
//    QFont bigSignalsFont =QFont("HarmonyOS Sans SC",14,QFont::Normal);
//    QFont smallSignalsFont =QFont("HarmonyOS Sans SC",12,QFont::Normal);
//    //Line pen brush
//    QPen linePen{QColor(0,0,0),6};
//    QBrush lineBrush{QColor(0,0,0)};
//    QPen linePenAct{QColor(255, 70, 31),6};
//    QBrush lineBrushAct{QColor(255, 70, 31)};
//    QPen sigLinePen{QColor(0,0,0),2};
//    QPen sigLinePenAct{QColor(255, 70, 31),2};

#endif // CONFIGSET_H
