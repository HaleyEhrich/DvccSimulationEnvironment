#include "r2qgitem.h"


QRectF R2QGItem::boundingRect() const
{
    return QRectF(this->mapFromScene(-240*this->data->zoomXPer,55*this->data->zoomYPer),
                  QSizeF(70*this->data->zoomXPer,45*this->data->zoomYPer));
}

void R2QGItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     Q_UNUSED(widget)
    if(this->data->load_r2==false){
        return;
    }

    //数据准备
    double zoomX=this->data->zoomXPer;
    double zoomY=this->data->zoomYPer;

    //body draw
    this->setPos(-240*zoomX,55*zoomY);

    this->bodyRect->setTopLeft(QPointF(0,0));
    this->bodyRect->setWidth(70*zoomX);
    this->bodyRect->setHeight(45*zoomY);

    this->body->setRect(*this->bodyRect);

    //Name draw
    this->nameText->setPos(5*zoomX,0);

    //Data draw
    this->dataText->setPos(35*zoomX-this->dataText->boundingRect().width()/2,15*zoomY);
    this->dataText->setText(QString("%1").arg(this->data->data_r2,2,16,QLatin1Char('0'))+"H");

    //sig--r2-bus
    if(this->data->statu_r2b){
        this->signalsOutText->setPen(darkSignalsPenAct);
        this->signalsOutText->setBrush(darkSignalsBrushAct);
        this->signalsOutText->setText("|R2-Bus:1");
        this->signalsOutText->setPos(45*zoomX,0-this->signalsOutText->boundingRect().height());
    }else{
        this->signalsOutText->setPen(darkSignalsPen);
        this->signalsOutText->setBrush(darkSignalsBrush);
        this->signalsOutText->setText("|R2-Bus:0");
        this->signalsOutText->setPos(45*zoomX,0-this->signalsOutText->boundingRect().height());
    }

    //Sig--ldr2 draw
    if(this->data->statu_ldr2){
        this->signalsInText->setPen(darkSignalsPenAct);
        this->signalsInText->setBrush(darkSignalsBrushAct);
        this->signalsInText->setText("|LDR2:1");
        this->signalsInText->setPos(45*zoomX,45*zoomY);
    }else{
        this->signalsInText->setPen(darkSignalsPen);
        this->signalsInText->setBrush(darkSignalsBrush);
        this->signalsInText->setText("|LDR2:0");
        this->signalsInText->setPos(45*zoomX,45*zoomY);
    }

    //line r2-->bus
    QPainterPath r2ToBusPath;
    r2ToBusPath.moveTo(32*zoomX,-3);
    r2ToBusPath.lineTo(32*zoomX,-55*zoomY);
    this->toBusLine->setPath(r2ToBusPath);
    if(this->data->statu_r2b){
        this->toBusLine->setPen(linePenAct);
        this->toBusLine->setZValue(100);
        this->setZValue(100);
    }else{
        this->toBusLine->setPen(linePen);
        this->toBusLine->setZValue(0);
        this->setZValue(0);
    }


    //line bus-->r2
    QPainterPath busToR2Path;
    busToR2Path.moveTo(32*zoomX,45*zoomY+3);
    busToR2Path.lineTo(32*zoomX,100*zoomY);
    busToR2Path.lineTo(240*zoomX,100*zoomY);
    busToR2Path.lineTo(240*zoomX,-55*zoomY);

    this->fromBusLine->setPath(busToR2Path);
    if(this->data->statu_ldr2){
        this->fromBusLine->setPen(linePenAct);
        this->fromBusLine->setZValue(100);
        this->setZValue(100);
    }else{
        this->fromBusLine->setPen(linePen);
        this->fromBusLine->setZValue(0);
        this->setZValue(0);
    }
}

R2QGItem::R2QGItem(systemDataSet *dataSet, QGraphicsItem *parent)
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
    this->nameText->setText("R2");
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
