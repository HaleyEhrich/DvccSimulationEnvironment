#include "microconqgitem.h"

QRectF MicroConQGItem::boundingRect() const
{
    return QRectF(this->mapFromScene(187*this->data->zoomXPer,24*this->data->zoomYPer),
                  QSizeF(180*this->data->zoomXPer,100*this->data->zoomYPer));
}

void MicroConQGItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->data->load_con==false){
        return;
    }
    //数据准备
    double zoomX=this->data->zoomXPer;
    double zoomY=this->data->zoomYPer;

    //
    this->setPos(187*zoomX,24*zoomY);

    //Body draw
    QRectF microConBody;
    microConBody.setTopLeft(this->mapFromScene(187*zoomX,24*zoomY));
    microConBody.setWidth(180*zoomX);
    microConBody.setHeight(100*zoomY);
    painter->setPen(microConBodyPen);
    painter->setBrush(microConBodyBrush);
    painter->drawRect(microConBody);

    QRectF romBody;
    romBody.setTopLeft(this->mapFromScene(202*zoomX,34*zoomY));
    romBody.setWidth(60*zoomX);
    romBody.setHeight(80*zoomY);
    painter->setPen(romBodyPen);
    painter->setBrush(romBodyBrush);
    painter->drawRoundedRect(romBody,5,5);

    //Cir
    QRectF romCir;
    romCir.setTopLeft(this->mapFromScene(247*zoomX,39*zoomY));
    romCir.setWidth(10*zoomX);
    romCir.setHeight(10*zoomX);
    painter->setPen(romCirPen);
    painter->setBrush(romCirBrush);
    painter->drawEllipse(romCir);

    QRectF conBody;
    conBody.setTopLeft(this->mapFromScene(292*zoomX,34*zoomY));
    conBody.setWidth(60*zoomX);
    conBody.setHeight(80*zoomY);
    painter->setPen(conBodyPen);
    painter->setBrush(conBodyBrush);
    painter->drawRect(conBody);

    painter->setPen(lightTextPen);

    //Name draw
    QPointF romNameText;
    romNameText=this->mapFromScene(212*zoomX,80*zoomY);
    painter->setFont(smallNameTextFont);
    painter->drawText(romNameText,"ROM");
}

MicroConQGItem::MicroConQGItem(systemDataSet *dataSet, QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    this->setZValue(0);
    this->data=dataSet;
}
