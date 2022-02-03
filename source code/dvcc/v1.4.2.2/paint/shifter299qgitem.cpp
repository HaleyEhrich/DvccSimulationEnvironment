#include "shifter299qgitem.h"

QRectF Shifter299QGItem::boundingRect() const
{
//    this->mapFromScene(-480*this->data->zoomXPer,-250*this->data->zoomYPer  QPointF(-480*this->data->zoomXPer,-250*this->data->zoomYPer)
    return QRectF(this->mapFromScene(-480*this->data->zoomXPer,-250*this->data->zoomYPer),QSizeF(170*this->data->zoomXPer,100*this->data->zoomYPer));
}

void Shifter299QGItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
     Q_UNUSED(widget)

    if(this->data->load_shifter_299b==false){
        return;
    }

    //数据准备
    double zoomX=this->data->zoomXPer;
    double zoomY=this->data->zoomYPer;

    //
    this->setPos(-480*zoomX,-250*zoomY);

    QPainterPath lineShifterToBus;
    lineShifterToBus.moveTo(85*zoomX,-3*zoomY);
    lineShifterToBus.lineTo(85*zoomX,-30*zoomY);
    lineShifterToBus.lineTo(this->mapFromScene(0,-280*zoomY));
    lineShifterToBus.lineTo(this->mapFromScene(0,0));

    //Body draw
    bodyRect->setTopLeft(QPointF(0,0));
    bodyRect->setWidth(170*this->data->zoomXPer);
    bodyRect->setHeight(100*this->data->zoomYPer);

//    if(!this->data->data_shifter_299b){
//        bodyShadowEff->setColor(Qt::red);
//        bodyShadowEff->setBlurRadius(30);
//    }else{
//        bodyShadowEff->setColor(Qt::gray);
//    }

    body->setRect(*bodyRect);

    //Name
    this->nameText->setPos(5*zoomX,0);

    //Data
    this->dataText->setPos(85*zoomX-this->dataText->boundingRect().width()/2,30*zoomY);
    this->dataText->setText(QString("%1").arg(this->data->data_shifter_299b,2,16,QLatin1Char('0'))+"H");

    //Signals shifter-bus
    this->signalsText->setPos(85*zoomX-this->signalsText->boundingRect().width()/2,70*zoomY);

    if(this->data->statu_299b){
        this->signalsText->setPen(lightSignalsPenAct);
        this->signalsText->setBrush(lightSignalsBrushAct);
        this->signalsText->setText("299-Bus: 1");
    }else{
        this->signalsText->setPen(lightSignalsPen);
        this->signalsText->setBrush(lightSignalsBrush);
        this->signalsText->setText("299-Bus: 0");
    }


    //line shifter--bus
    if(this->data->statu_299b){
        this->toBusLine->setPen(linePenAct);
        this->setZValue(100);
        this->toBusLine->setZValue(100);
    }else{
        this->toBusLine->setPen(linePen);
        this->setZValue(0);
        this->toBusLine->setZValue(0);
    }
    this->toBusLine->setPath(lineShifterToBus);
}

Shifter299QGItem::Shifter299QGItem(systemDataSet *dataSet, QGraphicsItem *parent)
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
    body->setPen(shifterBodyPen);
    body->setBrush(shifterBodyBrush);

    body->setGraphicsEffect(bodyShadowEff);

    nameText=new QGraphicsSimpleTextItem(this);
    this->nameText->setText("299B");
    this->nameText->setPen(lightTextPen);
    this->nameText->setBrush(ligthTextBrush);
    this->nameText->setFont(bigNameTextFont);

    dataText=new QGraphicsSimpleTextItem(this);
    this->dataText->setPen(lightTextPen);
    this->dataText->setBrush(ligthTextBrush);
    this->dataText->setFont(bigDataTextFont);

    signalsText=new QGraphicsSimpleTextItem(this);
    this->signalsText->setFont(bigSignalsFont);

    toBusLine=new QGraphicsPathItem(this);
}
