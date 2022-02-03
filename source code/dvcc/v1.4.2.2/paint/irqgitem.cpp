#include "irqgitem.h"

QRectF IrQGItem::boundingRect() const
{
    return QRectF(this->mapFromScene(60*this->data->zoomXPer,55*this->data->zoomYPer),
                  QSizeF(70*this->data->zoomXPer,45*this->data->zoomYPer));
}

void IrQGItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->data->load_ir==false){
        return;
    }

    //数据准备
    double zoomX=this->data->zoomXPer;
    double zoomY=this->data->zoomYPer;

    //body draw
    this->setPos(60*zoomX,55*zoomY);

    this->bodyRect->setTopLeft(QPointF(0,0));
    this->bodyRect->setWidth(70*zoomX);
    this->bodyRect->setHeight(45*zoomY);

    this->body->setRect(*this->bodyRect);

    //Name draw
    this->nameText->setPos(5*zoomX,0);

    //Data draw
    this->dataText->setPos(35*zoomX-this->dataText->boundingRect().width()/2,15*zoomY);
    this->dataText->setText(QString("%1").arg(this->data->data_ir,2,16,QLatin1Char('0'))+"H");

    //Sig--ldir draw
    if(this->data->statu_ldir){
        this->signalsInText->setPen(darkSignalsPenAct);
        this->signalsInText->setBrush(darkSignalsBrushAct);
        this->signalsInText->setText("|LDIR:1");
        this->signalsInText->setPos(45*zoomX,45*zoomY);
    }else{
        this->signalsInText->setPen(darkSignalsPen);
        this->signalsInText->setBrush(darkSignalsBrush);
        this->signalsInText->setText("|LDIR:0");
        this->signalsInText->setPos(45*zoomX,45*zoomY);
    }

    //line bus-->ir
    QPainterPath busToIrPath;
    busToIrPath.moveTo(-3,22*zoomY);
    busToIrPath.lineTo(-60*zoomX,22*zoomY);
    busToIrPath.lineTo(-60*zoomX,-55*zoomY);

    this->fromBusLine->setPath(busToIrPath);
    if(this->data->statu_ldir){
        this->fromBusLine->setPen(linePenAct);
        this->fromBusLine->setZValue(100);
        this->setZValue(100);
    }else{
        this->fromBusLine->setPen(linePen);
        this->fromBusLine->setZValue(0);
        this->setZValue(0);
    }

    //line pc-->bus
    QPainterPath irToMConPath;
    irToMConPath.moveTo(70*zoomX+3,22*zoomY);
    irToMConPath.lineTo(130*zoomX,22*zoomY);

    this->toBusLine->setPath(irToMConPath);

}

IrQGItem::IrQGItem(systemDataSet *dataSet, QGraphicsItem *parent)
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
    this->nameText->setText("IR");
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

//    signalsLeftText=new QGraphicsSimpleTextItem(this);
//    this->signalsLeftText->setFont(smallSignalsFont);

    toBusLine=new QGraphicsPathItem(this);
    this->toBusLine->setPen(linePen);
    this->toBusLine->setZValue(0);
    this->setZValue(0);

    fromBusLine=new QGraphicsPathItem(this);

}

