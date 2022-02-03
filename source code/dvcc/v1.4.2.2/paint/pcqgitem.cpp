#include "pcqgitem.h"

QRectF PCQGItem::boundingRect() const
{
    return QRectF(this->mapFromScene(30*this->data->zoomXPer,-100*this->data->zoomYPer),
                  QSizeF(70*this->data->zoomXPer,45*this->data->zoomYPer));
}

void PCQGItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->data->load_pc==false){
        return;
    }

    //数据准备
    double zoomX=this->data->zoomXPer;
    double zoomY=this->data->zoomYPer;

    //body draw
    this->setPos(30*zoomX,-100*zoomY);

    this->bodyRect->setTopLeft(QPointF(0,0));
    this->bodyRect->setWidth(70*zoomX);
    this->bodyRect->setHeight(45*zoomY);

    this->body->setRect(*this->bodyRect);


    //Name draw
    this->nameText->setPos(5*zoomX,0);

    //Data draw
    this->dataText->setPos(35*zoomX-this->dataText->boundingRect().width()/2,15*zoomY);
    this->dataText->setText(QString("%1").arg(this->data->data_pc,2,16,QLatin1Char('0'))+"H");

    //Sig--ldpc draw
    if(this->data->statu_ldpc){
        this->signalsInText->setPen(darkSignalsPenAct);
        this->signalsInText->setBrush(darkSignalsBrushAct);
        this->signalsInText->setText("|LDPC:1");
        this->signalsInText->setPos(45*zoomX,45*zoomY);
    }else{
        this->signalsInText->setPen(darkSignalsPen);
        this->signalsInText->setBrush(darkSignalsBrush);
        this->signalsInText->setText("|LDPC:0");
        this->signalsInText->setPos(45*zoomX,45*zoomY);
    }

    //Sig--pc-bus draw
    if(this->data->statu_pcb){
        this->signalsOutText->setPen(darkSignalsPenAct);
        this->signalsOutText->setBrush(darkSignalsBrushAct);
        this->signalsOutText->setText("|PC-Bus:1");
        this->signalsOutText->setPos(45*zoomX,0-this->signalsOutText->boundingRect().height());
    }else{
        this->signalsOutText->setPen(darkSignalsPen);
        this->signalsOutText->setBrush(darkSignalsBrush);
        this->signalsOutText->setText("|PC-Bus:0");
        this->signalsOutText->setPos(45*zoomX,0-this->signalsOutText->boundingRect().height());
    }

    //Sig--ldad draw
    if(this->data->statu_ldad){
        this->signalsLeftText->setPen(darkSignalsPenAct);
        this->signalsLeftText->setBrush(darkSignalsBrushAct);
        this->signalsLeftText->setText("-LDAD:1");
        this->signalsLeftText->setPos(70*zoomX,22*zoomY-this->signalsLeftText->boundingRect().height()/2);
    }else{
        this->signalsLeftText->setPen(darkSignalsPen);
        this->signalsLeftText->setBrush(darkSignalsBrush);
        this->signalsLeftText->setText("-LDAD:0");
        this->signalsLeftText->setPos(70*zoomX,22*zoomY-this->signalsLeftText->boundingRect().height()/2);
    }

    //line bus-->pc
    QPainterPath busToPcPath;
    busToPcPath.moveTo(32*zoomX,45*zoomY+3);
    busToPcPath.lineTo(32*zoomX,100*zoomY);

    this->fromBusLine->setPath(busToPcPath);
    if((this->data->statu_ldad
                        && this->data->statu_ldpc)){
        this->fromBusLine->setPen(linePenAct);
        this->fromBusLine->setZValue(100);
        this->setZValue(100);
    }else{
        this->fromBusLine->setPen(linePen);
        this->fromBusLine->setZValue(0);
        this->setZValue(0);
    }

    //line pc-->bus
    QPainterPath pcToBusPath;
    pcToBusPath.moveTo(32*zoomX,0-3);
    pcToBusPath.lineTo(32*zoomX,-37*zoomY);
    pcToBusPath.lineTo(-30*zoomX,-37*zoomY);
    pcToBusPath.lineTo(-30*zoomX,100*zoomY);

    this->toBusLine->setPath(pcToBusPath);
    if((this->data->statu_pcb
                        && this->data->statu_ldpc)){
        this->toBusLine->setPen(linePenAct);
        this->toBusLine->setZValue(100);
        this->setZValue(100);
    }else{
        this->toBusLine->setPen(linePen);
        this->toBusLine->setZValue(0);
        this->setZValue(0);
    }



}

PCQGItem::PCQGItem(systemDataSet *dataSet, QGraphicsItem *parent)
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
    this->nameText->setText("PC");
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

    signalsOutText=new QGraphicsSimpleTextItem(this);
    this->signalsOutText->setFont(smallSignalsFont);

    signalsLeftText=new QGraphicsSimpleTextItem(this);
    this->signalsLeftText->setFont(smallSignalsFont);

    toBusLine=new QGraphicsPathItem(this);
    fromBusLine=new QGraphicsPathItem(this);

}

