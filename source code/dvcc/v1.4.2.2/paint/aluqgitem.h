#ifndef ALUQGITEM_H
#define ALUQGITEM_H

#include <QBrush>
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsDropShadowEffect>
#include <QObject>
#include <QPainter>
#include <QPen>
#include <QRectF>

#include "systemdataset.h"


//#define aluBodyPen QPen(QColor(103, 158, 210),2)
//#define aluBodyBrush QBrush(QColor(103, 158, 210))
//#define lightTextPen QPen(QColor(255,255,255),2)
//#define bigNameTextFont QFont("HarmonyOS Sans SC",20,7)
//#define bigDataTextFont QFont("HarmonyOS Sans SC",20,7)
//#define darkSignalsPen QPen(QColor(0,0,0),2)
//#define darkSignalsPenAct QPen(QColor(255, 117, 0),2)
//#define darkSmallSignalsFont QFont("HarmonyOS Sans SC",13,7)
//#define linePen QPen(QColor(0,0,0),6)
//#define linePenAct QPen(QColor(255, 70, 31),6)

class ALUQGItem : public QGraphicsItem
{

private:
    QPainterPath* bodyPath=nullptr;

    QGraphicsPathItem* body=nullptr;

    QGraphicsDropShadowEffect* bodyShadowEff=nullptr;

    QGraphicsSimpleTextItem* dataText=nullptr;

    QGraphicsSimpleTextItem* nameText=nullptr;

    QGraphicsSimpleTextItem* signalsMText=nullptr;
    QGraphicsSimpleTextItem* signalsCnText=nullptr;
    QGraphicsSimpleTextItem* signalsS0Text=nullptr;
    QGraphicsSimpleTextItem* signalsS1Text=nullptr;
    QGraphicsSimpleTextItem* signalsS2Text=nullptr;
    QGraphicsSimpleTextItem* signalsS3Text=nullptr;

    QGraphicsPathItem* toBusLine=nullptr;

//    QGraphicsPathItem* fromBusLine=nullptr;

    systemDataSet* data=nullptr;

protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=nullptr) Q_DECL_OVERRIDE;

public:
    ALUQGItem();

    ALUQGItem(systemDataSet*,QGraphicsItem *parent = 0);
};

#endif // ALUQGITEM_H
