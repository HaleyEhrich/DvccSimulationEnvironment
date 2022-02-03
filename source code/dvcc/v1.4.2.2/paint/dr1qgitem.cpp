#include "dr1qgitem.h"

QRectF Dr1QGItem::boundingRect() const
{
    return QRectF(this->mapFromScene(-265*this->data->zoomXPer,-100*this->data->zoomYPer),
                  QSizeF(70*this->data->zoomXPer,45*this->data->zoomYPer));
}

void Dr1QGItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    if(this->data->load_dr1==false){
        return;
    }

    //数据准备
    double zoomX=this->data->zoomXPer;
    double zoomY=this->data->zoomYPer;

    //body draw
    this->setPos(-265*zoomX,-100*zoomY);

    this->bodyRect->setTopLeft(QPointF(0,0));
    this->bodyRect->setWidth(70*zoomX);
    this->bodyRect->setHeight(45*zoomY);

    this->body->setRect(*this->bodyRect);


    //Name draw
    this->nameText->setPos(5*zoomX,0);

    //Data draw
    this->dataText->setPos(35*zoomX-this->dataText->boundingRect().width()/2,15*zoomY);
    this->dataText->setText(QString("%1").arg(this->data->data_dr1,2,16,QLatin1Char('0'))+"H");

    //Sig--lddr1 draw
    if(this->data->statu_lddr1){
        this->signalsInText->setPen(darkSignalsPenAct);
        this->signalsInText->setBrush(darkSignalsBrushAct);
        this->signalsInText->setText("|LDDR1:1");
        this->signalsInText->setPos(45*zoomX,45*zoomY);
    }else{
        this->signalsInText->setPen(darkSignalsPen);
        this->signalsInText->setBrush(darkSignalsBrush);
        this->signalsInText->setText("|LDDR1:0");
        this->signalsInText->setPos(45*zoomX,45*zoomY);
    }

    //line dr1-->alu
    QPainterPath dr1ToAluPath;
    dr1ToAluPath.moveTo(32*zoomX,-3);
    dr1ToAluPath.lineTo(32*zoomX,-50*zoomY+3);
    this->toBusLine->setPath(dr1ToAluPath);
    if(this->data->statu_alub){
        this->toBusLine->setPen(linePenAct);
        this->toBusLine->setZValue(100);
        this->setZValue(100);
    }else{
        this->toBusLine->setPen(linePen);
        this->toBusLine->setZValue(0);
        this->setZValue(0);
    }


    //line bus-->dr1
    QPainterPath busToDr1Path;
    busToDr1Path.moveTo(32*zoomX,45*zoomY+3);
    busToDr1Path.lineTo(32*zoomX,100*zoomY);

    this->fromBusLine->setPath(busToDr1Path);
    if(this->data->statu_lddr1){
        this->fromBusLine->setPen(linePenAct);
        this->fromBusLine->setZValue(100);
        this->setZValue(100);
    }else{
        this->fromBusLine->setPen(linePen);
        this->fromBusLine->setZValue(0);
        this->setZValue(0);
    }
}

Dr1QGItem::Dr1QGItem(systemDataSet *dataSet, QGraphicsItem *parent)
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
    this->nameText->setText("DR1");
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
