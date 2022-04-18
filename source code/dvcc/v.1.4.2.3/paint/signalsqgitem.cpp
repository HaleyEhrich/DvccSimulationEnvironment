#include "signalsqgitem.h"

QRectF SignalsQGItem::boundingRect() const
{
    return QRectF(this->mapFromScene(-480*this->data->zoomXPer,170*this->data->zoomYPer),
                  QSizeF(180*this->data->zoomXPer,50*this->data->zoomYPer));
}

void SignalsQGItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    //数据准备
    double zoomX=this->data->zoomXPer;
    double zoomY=this->data->zoomYPer;

    //
    this->setPos(-480*zoomX,170*zoomY);

    //Body draw
    this->cyBodyRect->setTopLeft(QPointF(0,0));
    this->cyBodyRect->setHeight(50*zoomX);
    this->cyBodyRect->setWidth(50*zoomX);
    this->cyBody->setRect(*this->cyBodyRect);
    if(this->data->signal_cy){
        this->cyBody->setPen(signalsLedBodyPenAct);
        this->cyBody->setBrush(signalsLedBodyBrushAct);
        cyBodyShadowEff->setColor(Qt::red);
    }else{
        this->cyBody->setPen(signalsLedBodyPen);
        this->cyBody->setBrush(signalsLedBodyBrush);
        cyBodyShadowEff->setColor(Qt::gray);
    }

    //Cyname
    this->cyNameText->setPos(25*zoomX-this->cyNameText->boundingRect().width()/2,55*zoomY);


    //cy sig
    if(this->data->signal_cy){
        this->cySignalsText->setPen(darkSignalsPenAct);
        this->cySignalsText->setBrush(darkSignalsBrushAct);
        this->cySignalsText->setText("CY: 1");
    }else{
        this->cySignalsText->setPen(darkSignalsPen);
        this->cySignalsText->setBrush(darkSignalsBrush);
        this->cySignalsText->setText("CY: 0");
    }
    this->cySignalsText->setPos(25*zoomX-this->cySignalsText->boundingRect().width()/2,85*zoomY);

//---------------zi

    //Body draw
    this->ziBodyRect->setTopLeft(QPointF(100*zoomX,0));
    this->ziBodyRect->setHeight(50*zoomX);
    this->ziBodyRect->setWidth(50*zoomX);
    this->ziBody->setRect(*this->ziBodyRect);
    if(this->data->signal_zi){
        this->ziBody->setPen(signalsLedBodyPenAct);
        this->ziBody->setBrush(signalsLedBodyBrushAct);
        ziBodyShadowEff->setColor(Qt::red);
    }else{
        this->ziBody->setPen(signalsLedBodyPen);
        this->ziBody->setBrush(signalsLedBodyBrush);
        ziBodyShadowEff->setColor(Qt::gray);
    }

    //ziname
    this->ziNameText->setPos(125*zoomX-this->ziNameText->boundingRect().width()/2,55*zoomY);

    //zi sig
    if(this->data->signal_zi){
        this->ziSignalsText->setPen(darkSignalsPenAct);
        this->ziSignalsText->setBrush(darkSignalsBrushAct);
        this->ziSignalsText->setText("ZI: 1");
    }else{
        this->ziSignalsText->setPen(darkSignalsPen);
        this->ziSignalsText->setBrush(darkSignalsBrush);
        this->ziSignalsText->setText("ZI: 0");
    }
    this->ziSignalsText->setPos(125*zoomX-this->ziSignalsText->boundingRect().width()/2,85*zoomY);

}

SignalsQGItem::SignalsQGItem(systemDataSet *dataSet, QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    this->setZValue(0);
    this->data=dataSet;


    cyBodyRect=new QRectF();

    cyBodyShadowEff=new QGraphicsDropShadowEffect();
    cyBodyShadowEff->setOffset(0,0);
    cyBodyShadowEff->setColor(Qt::gray);
    cyBodyShadowEff->setBlurRadius(15);

    cyBody=new QGraphicsEllipseItem(this);

    cyBody->setGraphicsEffect(cyBodyShadowEff);

    cyNameText=new QGraphicsSimpleTextItem(this);
    this->cyNameText->setText("CY");
    this->cyNameText->setPen(darkTextPen);
    this->cyNameText->setBrush(darkTextBrush);
    this->cyNameText->setFont(bigNameTextFont);

    cySignalsText=new QGraphicsSimpleTextItem(this);
    this->cySignalsText->setFont(smallSignalsFont);

//---------ZI

    ziBodyRect=new QRectF();

    ziBodyShadowEff=new QGraphicsDropShadowEffect();
    ziBodyShadowEff->setOffset(0,0);
    ziBodyShadowEff->setColor(Qt::gray);
    ziBodyShadowEff->setBlurRadius(15);

    ziBody=new QGraphicsEllipseItem(this);
    ziBody->setPen(shifterBodyPen);
    ziBody->setBrush(shifterBodyBrush);

    ziBody->setGraphicsEffect(ziBodyShadowEff);

    ziNameText=new QGraphicsSimpleTextItem(this);
    this->ziNameText->setText("ZI");
    this->ziNameText->setPen(darkTextPen);
    this->ziNameText->setBrush(darkTextBrush);
    this->ziNameText->setFont(bigNameTextFont);

    ziSignalsText=new QGraphicsSimpleTextItem(this);
    this->ziSignalsText->setFont(smallSignalsFont);
}

