#include "arqgitem.h"

QRectF ARQGItem::boundingRect() const
{
    return QRectF(this->mapFromScene(30*this->data->zoomXPer,-220*this->data->zoomYPer),
                  QSizeF(70*this->data->zoomXPer,45*this->data->zoomYPer));
}

void ARQGItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->data->load_ar==false){
        return;
    }

    //数据准备
    double zoomX=this->data->zoomXPer;
    double zoomY=this->data->zoomYPer;

    //body draw
    this->setPos(30*zoomX,-220*zoomY);

    this->bodyRect->setTopLeft(QPointF(0,0));
    this->bodyRect->setWidth(70*zoomX);
    this->bodyRect->setHeight(45*zoomY);

    this->body->setRect(*this->bodyRect);


    //Name draw
    this->nameText->setPos(5*zoomX,0);

    //Data draw
    this->dataText->setPos(35*zoomX-this->dataText->boundingRect().width()/2,15*zoomY);
    this->dataText->setText(QString("%1").arg(this->data->data_ar,2,16,QLatin1Char('0'))+"H");

    //Sig--ldar draw
    if(this->data->statu_ldar){
        this->signalsInText->setPen(darkSignalsPenAct);
        this->signalsInText->setBrush(darkSignalsBrushAct);
        this->signalsInText->setText("|LDAR:1");
        this->signalsInText->setPos(45*zoomX,45*zoomY);
    }else{
        this->signalsInText->setPen(darkSignalsPen);
        this->signalsInText->setBrush(darkSignalsBrush);
        this->signalsInText->setText("|LDAR:0");
        this->signalsInText->setPos(45*zoomX,45*zoomY);
    }

    //line ar-->ram
    QPainterPath arToRamPath;
    arToRamPath.moveTo(32*zoomX,-3);
    arToRamPath.lineTo(32*zoomX,-60*zoomY);
    arToRamPath.lineTo(245*zoomX,-60*zoomY);
    arToRamPath.lineTo(245*zoomX,-30*zoomY-3);

    this->toBusLine->setPath(arToRamPath);
    if(this->data->signal_ce && !this->data->statu_ldar){
        this->toBusLine->setPen(linePenAct);
        this->toBusLine->setZValue(100);
        this->setZValue(100);
    }else{
        this->toBusLine->setPen(linePen);
        this->toBusLine->setZValue(0);
        this->setZValue(0);
    }


    //line bus-->dr1
    QPainterPath busToArPath;
    busToArPath.moveTo(32*zoomX,45*zoomY+3);
    busToArPath.lineTo(32*zoomX,83*zoomY);
    busToArPath.lineTo(-30*zoomX,83*zoomY);
    busToArPath.lineTo(-30*zoomX,220*zoomY);

    this->fromBusLine->setPath(busToArPath);
    if(this->data->statu_ldar){
        this->fromBusLine->setPen(linePenAct);
        this->fromBusLine->setZValue(100);
        this->setZValue(100);
    }else{
        this->fromBusLine->setPen(linePen);
        this->fromBusLine->setZValue(0);
        this->setZValue(0);
    }
}

ARQGItem::ARQGItem(systemDataSet *dataSet, QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    this->setZValue(0);
    this->data=dataSet;

    bodyRect=new QRectF();

    bodyShadowEff=new QGraphicsDropShadowEffect();
    bodyShadowEff->setOffset(5,5);
    bodyShadowEff->setColor(Qt::gray);
    bodyShadowEff->setBlurRadius(15);

    body=new QGraphicsRectItem(this);
    body->setPen(registerBodyPen);
    body->setBrush(registerBodyBrush);

    body->setGraphicsEffect(bodyShadowEff);

//    this->body->setZValue(105);

    nameText=new QGraphicsSimpleTextItem(this);
    this->nameText->setText("AR");
    this->nameText->setPen(lightTextPen);
    this->nameText->setBrush(ligthTextBrush);
    this->nameText->setFont(smallNameTextFont);

//    this->nameText->setZValue(105);

    dataText=new QGraphicsSimpleTextItem(this);
    this->dataText->setPen(lightTextPen);
    this->dataText->setBrush(ligthTextBrush);
    this->dataText->setFont(smallDataTextFont);

//    this->dataText->setZValue(105);

    signalsInText=new QGraphicsSimpleTextItem(this);
    this->signalsInText->setFont(smallSignalsFont);

//    signalsOutText=new QGraphicsSimpleTextItem(this);
//    this->signalsOutText->setFont(smallSignalsFont);

    toBusLine=new QGraphicsPathItem(this);
    fromBusLine=new QGraphicsPathItem(this);

}
