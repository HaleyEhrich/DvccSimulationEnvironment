#ifndef RAMQGITEM_H
#define RAMQGITEM_H

#include <QBrush>
#include <QFont>
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QPen>
#include <QRectF>

#include "systemdataset.h"

class RamQGItem : public QGraphicsItem
{

private:
    QPainterPath* bodyPath=nullptr;

    QGraphicsPathItem* body=nullptr;

    QPainterPath* cirPath=nullptr;

    QGraphicsPathItem* cir=nullptr;

    QGraphicsDropShadowEffect* bodyShadowEff=nullptr;

    QGraphicsSimpleTextItem* dataText=nullptr;

    QGraphicsSimpleTextItem* nameText=nullptr;

    QGraphicsSimpleTextItem* signalsText=nullptr;

    QGraphicsSimpleTextItem* signalsText2=nullptr;

    QGraphicsLineItem* toBusLine=nullptr;

//    QGraphicsPathItem* fromArLine=nullptr;

    systemDataSet* data=nullptr;

protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=nullptr) Q_DECL_OVERRIDE;

public:
    RamQGItem(systemDataSet*,QGraphicsItem *parent = 0);

};

#endif // RAMQGITEM_H
