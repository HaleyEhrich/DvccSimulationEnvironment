#include "r1qgitem.h"

QRectF R1QGItem::boundingRect() const
{
    return QRectF(this->mapFromScene(-360*this->data->zoomXPer,55*this->data->zoomYPer),
                  QSizeF(70*this->data->zoomXPer,45*this->data->zoomYPer));
}

void R1QGItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     Q_UNUSED(widget)

    if(this->data->load_r1==false){
        return;
    }

    //数据准备
    double zoomX=this->data->zoomXPer;
    double zoomY=this->data->zoomYPer;

    //
    this->setPos(-360*zoomX,55*zoomY);

    //body draw
    this->setPos(-360*zoomX,55*zoomY);

    this->bodyRect->setTopLeft(QPointF(0,0));
    this->bodyRect->setWidth(70*zoomX);
    this->bodyRect->setHeight(45*zoomY);

    this->body->setRect(*this->bodyRect);

    //Name draw
    this->nameText->setPos(5*zoomX,0);

    //Data draw
    this->dataText->setPos(35*zoomX-this->dataText->boundingRect().width()/2,15*zoomY);
    this->dataText->setText(QString("%1").arg(this->data->data_r1,2,16,QLatin1Char('0'))+"H");

    //sig--r1-bus
    if(this->data->statu_r1b){
        this->signalsOutText->setPen(darkSignalsPenAct);
        this->signalsOutText->setBrush(darkSignalsBrushAct);
        this->signalsOutText->setText("|R1-Bus:1");
        this->signalsOutText->setPos(45*zoomX,0-this->signalsOutText->boundingRect().height());
    }else{
        this->signalsOutText->setPen(darkSignalsPen);
        this->signalsOutText->setBrush(darkSignalsBrush);
        this->signalsOutText->setText("|R1-Bus:0");
        this->signalsOutText->setPos(45*zoomX,0-this->signalsOutText->boundingRect().height());
    }

    //Sig--ldr1 draw
    if(this->data->statu_ldr1){
        this->signalsInText->setPen(darkSignalsPenAct);
        this->signalsInText->setBrush(darkSignalsBrushAct);
        this->signalsInText->setText("|LDR1:1");
        this->signalsInText->setPos(45*zoomX,45*zoomY);
    }else{
        this->signalsInText->setPen(darkSignalsPen);
        this->signalsInText->setBrush(darkSignalsBrush);
        this->signalsInText->setText("|LDR1:0");
        this->signalsInText->setPos(45*zoomX,45*zoomY);
    }

    //line r1-->bus
    QPainterPath r1ToBusPath;
    r1ToBusPath.moveTo(32*zoomX,-3);
    r1ToBusPath.lineTo(32*zoomX,-55*zoomY);
    this->toBusLine->setPath(r1ToBusPath);
    if(this->data->statu_r1b){
        this->toBusLine->setPen(linePenAct);
        this->toBusLine->setZValue(100);
        this->setZValue(100);
    }else{
        this->toBusLine->setPen(linePen);
        this->toBusLine->setZValue(0);
        this->setZValue(0);
    }


    //line bus-->r1
    QPainterPath busToR1Path;
    busToR1Path.moveTo(32*zoomX,45*zoomY+3);
    busToR1Path.lineTo(32*zoomX,100*zoomY);
    busToR1Path.lineTo(360*zoomX,100*zoomY);
    busToR1Path.lineTo(360*zoomX,-55*zoomY);

    this->fromBusLine->setPath(busToR1Path);
    if(this->data->statu_ldr1){
        this->fromBusLine->setPen(linePenAct);
        this->fromBusLine->setZValue(100);
        this->setZValue(100);
    }else{
        this->fromBusLine->setPen(linePen);
        this->fromBusLine->setZValue(0);
        this->setZValue(0);
    }
}

R1QGItem::R1QGItem(systemDataSet *dataSet, QGraphicsItem *parent)
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
    this->nameText->setText("R1");
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
