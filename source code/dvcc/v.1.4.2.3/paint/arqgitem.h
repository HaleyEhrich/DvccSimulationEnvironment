#ifndef ARQGITEM_H
#define ARQGITEM_H

#include <QBrush>
#include <QFont>
#include <QGraphicsItem>
#include "qgraphicsitem.h"
#include <QObject>
#include <QPainter>
#include <QPen>
#include <QRectF>

#include "systemdataset.h"


//#define arBodyPen QPen(QColor(103, 158, 210),2)
//#define arBodyBrush QBrush(QColor(103, 158, 210))
//#define lightTextPen QPen(QColor(255,255,255),2)
//#define smallNameTextFont QFont("HarmonyOS Sans SC",12,7)
//#define smallDataTextFont QFont("HarmonyOS Sans SC",20,7)
//#define darkSignalsPen QPen(QColor(0,0,0),2)
//#define darkSignalsPenAct QPen(QColor(255, 117, 0),2)
//#define darkSmallSignalsFont QFont("HarmonyOS Sans SC",13,7)
//#define linePen QPen(QColor(0,0,0),6)
//#define linePenAct QPen(QColor(255, 70, 31),6)

class ARQGItem : public QGraphicsItem
{
private:
    QRectF* bodyRect=nullptr;

    QGraphicsRectItem* body=nullptr;

    QGraphicsDropShadowEffect* bodyShadowEff=nullptr;

    QGraphicsSimpleTextItem* dataText=nullptr;

    QGraphicsSimpleTextItem* nameText=nullptr;

    QGraphicsSimpleTextItem* signalsInText=nullptr;

//    QGraphicsSimpleTextItem* signalsOutText=nullptr;

    QGraphicsPathItem* toBusLine=nullptr;

    QGraphicsPathItem* fromBusLine=nullptr;

    systemDataSet* data=nullptr;

protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=nullptr) Q_DECL_OVERRIDE;

public:

    ARQGItem(systemDataSet* dataSet,QGraphicsItem *parent = 0);
};

#endif // ARQGITEM_H
