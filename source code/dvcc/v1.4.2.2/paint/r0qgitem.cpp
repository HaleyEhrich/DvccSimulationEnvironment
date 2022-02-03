#include "r0qgitem.h"

QRectF R0QGItem::boundingRect() const
{
    return QRectF(this->mapFromScene(-480*this->data->zoomXPer,55*this->data->zoomYPer),
                  QSizeF(70*this->data->zoomXPer,45*this->data->zoomYPer));
}

void R0QGItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     Q_UNUSED(widget)

    if(this->data->load_r0==false){
        return;
    }

    //数据准备
    double zoomX=this->data->zoomXPer;
    double zoomY=this->data->zoomYPer;

    //body draw
    this->setPos(-480*zoomX,55*zoomY);

    this->bodyRect->setTopLeft(QPointF(0,0));
    this->bodyRect->setWidth(70*zoomX);
    this->bodyRect->setHeight(45*zoomY);

    this->body->setRect(*this->bodyRect);

    //Name draw
    this->nameText->setPos(5*zoomX,0);

    //Data draw
    this->dataText->setPos(35*zoomX-this->dataText->boundingRect().width()/2,15*zoomY);
    this->dataText->setText(QString("%1").arg(this->data->data_r0,2,16,QLatin1Char('0'))+"H");

    //sig--r0-bus
    if(this->data->statu_r0b){
        this->signalsOutText->setPen(darkSignalsPenAct);
        this->signalsOutText->setBrush(darkSignalsBrushAct);
        this->signalsOutText->setText("|R0-Bus:1");
        this->signalsOutText->setPos(45*zoomX,0-this->signalsOutText->boundingRect().height());
    }else{
        this->signalsOutText->setPen(darkSignalsPen);
        this->signalsOutText->setBrush(darkSignalsBrush);
        this->signalsOutText->setText("|R0-Bus:0");
        this->signalsOutText->setPos(45*zoomX,0-this->signalsOutText->boundingRect().height());
    }

    //Sig--ldr0 draw
    if(this->data->statu_ldr0){
        this->signalsInText->setPen(darkSignalsPenAct);
        this->signalsInText->setBrush(darkSignalsBrushAct);
        this->signalsInText->setText("|LDR0:1");
        this->signalsInText->setPos(45*zoomX,45*zoomY);
    }else{
        this->signalsInText->setPen(darkSignalsPen);
        this->signalsInText->setBrush(darkSignalsBrush);
        this->signalsInText->setText("|LDR0:0");
        this->signalsInText->setPos(45*zoomX,45*zoomY);
    }

    //line r0-->bus
    QPainterPath r0ToBusPath;
    r0ToBusPath.moveTo(32*zoomX,-3);
    r0ToBusPath.lineTo(32*zoomX,-55*zoomY);
    this->toBusLine->setPath(r0ToBusPath);
    if(this->data->statu_r0b){
        this->toBusLine->setPen(linePenAct);
        this->toBusLine->setZValue(100);
        this->setZValue(100);
    }else{
        this->toBusLine->setPen(linePen);
        this->toBusLine->setZValue(0);
        this->setZValue(0);
    }


    //line bus-->r0
    QPainterPath busToR0Path;
    busToR0Path.moveTo(32*zoomX,45*zoomY+3);
    busToR0Path.lineTo(32*zoomX,100*zoomY);
    busToR0Path.lineTo(480*zoomX,100*zoomY);
    busToR0Path.lineTo(480*zoomX,-55*zoomY);

    this->fromBusLine->setPath(busToR0Path);
    if(this->data->statu_ldr0){
        this->fromBusLine->setPen(linePenAct);
        this->fromBusLine->setZValue(100);
        this->setZValue(100);
    }else{
        this->fromBusLine->setPen(linePen);
        this->fromBusLine->setZValue(0);
        this->setZValue(0);
    }
}

R0QGItem::R0QGItem(systemDataSet *dataSet, QGraphicsItem *parent)
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

    nameText=new QGraphicsSimpleTextItem(this);
    this->nameText->setText("R0");
    this->nameText->setPen(lightTextPen);
    this->nameText->setBrush(ligthTextBrush);
    this->nameText->setFont(smallNameTextFont);

    dataText=new QGraphicsSimpleTextItem(this);
    this->dataText->setPen(lightTextPen);
    this->dataText->setBrush(ligthTextBrush);
    this->dataText->setFont(smallDataTextFont);

    signalsInText=new QGraphicsSimpleTextItem(this);
    this->signalsInText->setFont(smallSignalsFont);

    signalsOutText=new QGraphicsSimpleTextItem(this);
    this->signalsOutText->setFont(smallSignalsFont);

    toBusLine=new QGraphicsPathItem(this);
    fromBusLine=new QGraphicsPathItem(this);
}
