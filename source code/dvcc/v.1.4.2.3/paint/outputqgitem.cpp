#include "outputqgitem.h"

QRectF OutputQGItem::boundingRect() const
{
    return QRectF(this->mapFromScene(390*this->data->zoomXPer,-100*this->data->zoomYPer),
                  QSizeF(90*this->data->zoomXPer,50*this->data->zoomYPer));

}

void OutputQGItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //数据准备
    double zoomX=this->data->zoomXPer;
    double zoomY=this->data->zoomYPer;

    //body draw
    this->setPos(390*zoomX,-100*zoomY);

    this->bodyRect->setTopLeft(QPointF(0,0));
    this->bodyRect->setWidth(90*zoomX);
    this->bodyRect->setHeight(50*zoomY);

    this->body->setRect(*this->bodyRect);

    //Name draw
    this->nameText->setPos(5*zoomX,0);

    //Data draw
    this->dataText->setPos(45*zoomX-this->dataText->boundingRect().width()/2,15*zoomY);
    if(this->data->statu_ldled
            && this->data->signal_we){
        this->dataText->setText(this->data->data_bus+"H");
    }else{
        this->dataText->setText("");
    }



    //sig--out-bus
    if(this->data->statu_ldled){
        this->signalsOutText->setPen(darkSignalsPenAct);
        this->signalsOutText->setBrush(darkSignalsBrushAct);
        this->signalsOutText->setText("| LED-Bus:1");
        this->signalsOutText->setPos(5,0-this->signalsOutText->boundingRect().height());
    }else{
        this->signalsOutText->setPen(darkSignalsPen);
        this->signalsOutText->setBrush(darkSignalsBrush);
        this->signalsOutText->setText("| LED-Bus:0");
        this->signalsOutText->setPos(5,0-this->signalsOutText->boundingRect().height());

    }

    //we draw
    if(this->data->signal_we){
        this->signalsInText->setPen(darkSignalsPenAct);
        this->signalsInText->setBrush(darkSignalsBrushAct);
        this->signalsInText->setText("|W/R:W");
        this->signalsInText->setPos(55*zoomX,50*zoomY);
    }else{
        this->signalsInText->setPen(darkSignalsPen);
        this->signalsInText->setBrush(darkSignalsBrush);
        this->signalsInText->setText("|W/R:R");
        this->signalsInText->setPos(55*zoomX,50*zoomY);
    }

    //line bus-->led
    QPainterPath busToOutPath;
    busToOutPath.moveTo(45*zoomX,50*zoomY+3);
    busToOutPath.lineTo(45*zoomX,100*zoomY);
    this->fromBusLine->setPath(busToOutPath);
    if(this->data->statu_ldled
            && this->data->signal_we){
        this->fromBusLine->setPen(linePenAct);
        this->fromBusLine->setZValue(100);
        this->setZValue(100);
    }else{
        this->fromBusLine->setPen(linePen);
        this->fromBusLine->setZValue(0);
        this->setZValue(0);
    }

//    //Body draw
//    QRectF outputBody;
//    outputBody.setTopLeft(this->mapFromScene(390*zoomX,-100*zoomY));
//    outputBody.setWidth(90*zoomX);
//    outputBody.setHeight(50*zoomY);
//    painter->setPen(outputBodyPen);
//    painter->setBrush(outputBodyBrush);
//    painter->drawRect(outputBody);

//    painter->setPen(lightTextPen);

//    //Name draw
//    QPointF outputNameText;
//    outputNameText=this->mapFromScene(395*zoomX,-85*zoomY);
//    painter->setFont(smallNameTextFont);
//    painter->drawText(outputNameText,"OUT");

//    //Data
//    if(this->data->statu_ldled
//            && this->data->signal_we){
//        QPointF outputDataText;
//        outputDataText=this->mapFromScene(412*zoomX,-60*zoomY);
//        painter->setFont(smallDataTextFont);
//        painter->drawText(outputDataText,this->data->data_bus+"H");
//    }

//    //siganls
//    painter->setFont(smallSignalsFont);
//    //-- led-bus
//    QPointF outputSLEDBText=this->mapFromScene(400*zoomX,-102*zoomY);
//    if(this->data->statu_ldled){
//        painter->setPen(darkSignalsPenAct);
//        painter->drawText(outputSLEDBText,"| LEB-Bus:1");
//    }else{
//        painter->setPen(darkSignalsPen);
//        painter->drawText(outputSLEDBText,"| LEB-Bus:0");
//    }

//    //-- we
//    QPointF outputSWEText=this->mapFromScene(445*zoomX,-33*zoomY);
//    if(this->data->signal_we){
//        painter->setPen(darkSignalsPenAct);
//        painter->drawText(outputSWEText,"| W/R:W");
//    }else{
//        painter->setPen(darkSignalsPen);
//        painter->drawText(outputSWEText,"| W/R:R");
//    }

//    //Line

//    //bus-->output
//    if(this->data->statu_ldled
//            && this->data->signal_we){
//        painter->setPen(linePenAct);
//    }else{
//        painter->setPen(linePen);
//    }
//    painter->drawLine(this->mapFromScene(435*zoomX,-47*zoomY),this->mapFromScene(435*zoomX,0));

}

OutputQGItem::OutputQGItem(systemDataSet *dataSet, QGraphicsItem *parent)
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
    this->nameText->setText("OUTPUT");
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

//    toBusLine=new QGraphicsPathItem(this);
    fromBusLine=new QGraphicsPathItem(this);
}
