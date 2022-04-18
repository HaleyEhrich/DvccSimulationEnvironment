#ifndef SIGNALSQGITEM_H
#define SIGNALSQGITEM_H

#include <QBrush>
#include <QFont>
#include <QGraphicsItem>
#include <QObject>
#include <QPainter>
#include <QPen>
#include <QRectF>

#include "systemdataset.h"


class SignalsQGItem : public QGraphicsItem
{
private:
    QRectF* cyBodyRect=nullptr;

    QGraphicsEllipseItem* cyBody=nullptr;

    QGraphicsDropShadowEffect* cyBodyShadowEff=nullptr;

    QGraphicsSimpleTextItem* cyNameText=nullptr;

    QGraphicsSimpleTextItem* cySignalsText=nullptr;

    QRectF* ziBodyRect=nullptr;

    QGraphicsEllipseItem* ziBody=nullptr;

    QGraphicsDropShadowEffect* ziBodyShadowEff=nullptr;

    QGraphicsSimpleTextItem* ziNameText=nullptr;

    QGraphicsSimpleTextItem* ziSignalsText=nullptr;

    systemDataSet* data=nullptr;

protected:
    QRectF boundingRect() const Q_DECL_OVERRIDE;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget=nullptr) Q_DECL_OVERRIDE;

public:
    SignalsQGItem(systemDataSet*,QGraphicsItem *parent = nullptr);
};

#endif // SIGNALSQGITEM_H
