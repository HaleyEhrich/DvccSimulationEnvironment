#ifndef MICROCONQGITEM_H
#define MICROCONQGITEM_H

#include <QBrush>
#include <QFont>
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QPen>
#include <QRectF>

#include "systemdataset.h"


//#define microConBodyPen QPen(QColor(38, 87, 39),2)
//#define microConBodyBrush QBrush(QColor(38, 87, 39))
//#define romBodyPen QPen(QColor(48, 48, 47),2)
//#define romBodyBrush QBrush(QColor(48, 48, 47))
//#define romCirPen QPen(QColor(48, 48, 47),2)
//#define romCirBrush QBrush(QColor(77, 77, 77))
//#define conBodyPen QPen(QColor(240, 252, 255),2)
//#define conBodyBrush QBrush(QColor(240, 252, 255))
//#define lightTextPen QPen(QColor(255,255,255),2)
//#define smallNameTextFont QFont("HarmonyOS Sans SC",12,7)
//#define smallDataTextFont QFont("HarmonyOS Sans SC",20,7)
//#define darkSignalsPen QPen(QColor(0,0,0),2)
//#define darkSignalsPenAct QPen(QColor(255, 117, 0),2)
//#define darkSmallSignalsFont QFont("HarmonyOS Sans SC",13,7)
//#define linePen QPen(QColor(0,0,0),6)
//#define linePenAct QPen(QColor(255, 70, 31),6)

class MicroConQGItem : public QGraphicsItem
{
private:
    QPainterPath* bodyPath=nullptr;

    QGraphicsPathItem* body=nullptr;

    QGraphicsDropShadowEffect* bodyShadowEff=nullptr;

    QGraphicsSimpleTextItem* dataText=nullptr;

    QGraphicsSimpleTextItem* nameText=nullptr;

    QGraphicsSimpleTextItem* signalsText=nullptr;

    QGraphicsPathItem* toBusLine=nullptr;

    QGraphicsPathItem* fromBusLine=nullptr;

    systemDataSet* data=nullptr;

protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=nullptr) Q_DECL_OVERRIDE;

public:

    MicroConQGItem(systemDataSet* dataSet,QGraphicsItem *parent = 0);
};

#endif // MICROCONQGITEM_H
