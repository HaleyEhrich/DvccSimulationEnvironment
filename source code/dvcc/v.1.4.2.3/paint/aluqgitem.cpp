#include "aluqgitem.h"

QRectF ALUQGItem::boundingRect() const
{
    return QRectF(this->mapFromScene(-280*this->data->zoomXPer,-250*this->data->zoomYPer),
                  QSizeF(240*this->data->zoomXPer,100*this->data->zoomYPer));
}

void ALUQGItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)

    if(this->data->load_alu==false){
        return;
    }

    painter->save();

    //数据准备
    double zoomX=this->data->zoomXPer;
    double zoomY=this->data->zoomYPer;

    //Body draw
    this->setPos(-270*zoomX,-250*zoomY);

    this->bodyPath->clear();
    this->bodyPath->moveTo(40*zoomX,0);//start point
    this->bodyPath->lineTo(180*zoomX,0);//right top
    this->bodyPath->lineTo(230*zoomX,100*zoomY);//right bottom
    this->bodyPath->lineTo(120*zoomX,100*zoomY);//right mid
    this->bodyPath->lineTo(110*zoomX,80*zoomY);//mid
    this->bodyPath->lineTo(100*zoomX,100*zoomY);//left mid
    this->bodyPath->lineTo(-10*zoomX,100*zoomY);//left bottom
    this->bodyPath->closeSubpath();//end

    this->body->setPath(*this->bodyPath);

    //name text
    this->nameText->setPos(40*zoomX,0);

    //data
    if(this->data->statu_alub){
        this->dataText->setText(this->data->data_bus+"H");
    }else{
        this->dataText->setText("");
    }
    this->dataText->setPos(110*zoomX-this->dataText->boundingRect().width()/2,35*zoomY);

    //Signals
    //M
    if(this->data->data_rom[this->data->data_mroAddress][mm]){
        this->signalsMText->setPen(darkSignalsPenAct);
        this->signalsMText->setBrush(darkSignalsBrushAct);
        this->signalsMText->setText("M-1");
        this->signalsMText->setPos(-25*zoomX
                                   ,25*zoomY-this->signalsMText->boundingRect().height()/2);

        painter->setPen(sigLinePenAct);
        painter->drawLine(-40*zoomX,25*zoomY
                          ,-30*zoomX,25*zoomY);
        painter->drawLine(-20*zoomX+this->signalsMText->boundingRect().width(),25*zoomY
                          ,50*zoomX,25*zoomY);

    }else{
        this->signalsMText->setPen(darkSignalsPen);
        this->signalsMText->setBrush(darkSignalsBrush);
        this->signalsMText->setText("M-0");
        this->signalsMText->setPos(-25*zoomX
                                   ,25*zoomY-this->signalsMText->boundingRect().height()/2);

        painter->setPen(sigLinePen);
        painter->drawLine(-40*zoomX,25*zoomY
                          ,-30*zoomX,25*zoomY);
        painter->drawLine(-20*zoomX+this->signalsMText->boundingRect().width(),25*zoomY
                          ,50*zoomX,25*zoomY);
    }


    //S0
    if(this->data->data_rom[this->data->data_mroAddress][ms0]){
        this->signalsS0Text->setPen(darkSignalsPenAct);
        this->signalsS0Text->setBrush(darkSignalsBrushAct);
        this->signalsS0Text->setText("S0-1");
        this->signalsS0Text->setPos(-25*zoomX
                                   ,50*zoomY-this->signalsS0Text->boundingRect().height()/2);

        painter->setPen(sigLinePenAct);
        painter->drawLine(-40*zoomX,50*zoomY
                          ,-30*zoomX,50*zoomY);
        painter->drawLine(-20*zoomX+this->signalsS0Text->boundingRect().width(),50*zoomY
                          ,50*zoomX,50*zoomY);
    }else{
        this->signalsS0Text->setPen(darkSignalsPen);
        this->signalsS0Text->setBrush(darkSignalsBrush);
        this->signalsS0Text->setText("S0-1");
        this->signalsS0Text->setPos(-25*zoomX
                                   ,50*zoomY-this->signalsS0Text->boundingRect().height()/2);

        painter->setPen(sigLinePen);
        painter->drawLine(-40*zoomX,50*zoomY
                          ,-30*zoomX,50*zoomY);
        painter->drawLine(-20*zoomX+this->signalsS0Text->boundingRect().width(),50*zoomY
                          ,50*zoomX,50*zoomY);
    }


    //S1
    if(this->data->data_rom[this->data->data_mroAddress][ms1]){
        this->signalsS1Text->setPen(darkSignalsPenAct);
        this->signalsS1Text->setBrush(darkSignalsBrushAct);
        this->signalsS1Text->setText("S1-1");
        this->signalsS1Text->setPos(-25*zoomX
                                   ,75*zoomY-this->signalsS1Text->boundingRect().height()/2);

        painter->setPen(sigLinePenAct);
        painter->drawLine(-40*zoomX,75*zoomY
                          ,-30*zoomX,75*zoomY);
        painter->drawLine(-20*zoomX+this->signalsS1Text->boundingRect().width(),75*zoomY
                          ,50*zoomX,75*zoomY);
    }else{
        this->signalsS1Text->setPen(darkSignalsPen);
        this->signalsS1Text->setBrush(darkSignalsBrush);
        this->signalsS1Text->setText("S1-0");
        this->signalsS1Text->setPos(-25*zoomX
                                   ,75*zoomY-this->signalsS1Text->boundingRect().height()/2);

        painter->setPen(sigLinePen);
        painter->drawLine(-40*zoomX,75*zoomY
                          ,-30*zoomX,75*zoomY);
        painter->drawLine(-20*zoomX+this->signalsS1Text->boundingRect().width(),75*zoomY
                          ,50*zoomX,75*zoomY);
    }

    //s2
    if(this->data->data_rom[this->data->data_mroAddress][ms2]){
        this->signalsS2Text->setPen(darkSignalsPenAct);
        this->signalsS2Text->setBrush(darkSignalsBrushAct);
        this->signalsS2Text->setText("S2-1");
        this->signalsS2Text->setPos(220*zoomX
                                   ,25*zoomY-this->signalsS2Text->boundingRect().height()/2);

        painter->setPen(sigLinePenAct);
        painter->drawLine(180*zoomX,25*zoomY
                          ,215*zoomX,25*zoomY);
    }else{
        this->signalsS2Text->setPen(darkSignalsPen);
        this->signalsS2Text->setBrush(darkSignalsBrush);
        this->signalsS2Text->setText("S2-0");
        this->signalsS2Text->setPos(220*zoomX
                                   ,25*zoomY-this->signalsS2Text->boundingRect().height()/2);

        painter->setPen(sigLinePen);
        painter->drawLine(180*zoomX,25*zoomY
                          ,215*zoomX,25*zoomY);
    }

    //s3
    if(this->data->data_rom[this->data->data_mroAddress][ms3]){
        this->signalsS3Text->setPen(darkSignalsPenAct);
        this->signalsS3Text->setBrush(darkSignalsBrushAct);
        this->signalsS3Text->setText("S3-1");
        this->signalsS3Text->setPos(220*zoomX
                                   ,50*zoomY-this->signalsS3Text->boundingRect().height()/2);

        painter->setPen(sigLinePenAct);
        painter->drawLine(180*zoomX,50*zoomY
                          ,215*zoomX,50*zoomY);
    }else{
        this->signalsS3Text->setPen(darkSignalsPen);
        this->signalsS3Text->setBrush(darkSignalsBrush);
        this->signalsS3Text->setText("S3-0");
        this->signalsS3Text->setPos(220*zoomX
                                   ,50*zoomY-this->signalsS3Text->boundingRect().height()/2);

        painter->setPen(sigLinePen);
        painter->drawLine(180*zoomX,50*zoomY
                          ,215*zoomX,50*zoomY);
    }

    //cn
    if(this->data->data_rom[this->data->data_mroAddress][mcn]){
        this->signalsCnText->setPen(darkSignalsPenAct);
        this->signalsCnText->setBrush(darkSignalsBrushAct);
        this->signalsCnText->setText("Cn-1");
        this->signalsCnText->setPos(220*zoomX
                                   ,75*zoomY-this->signalsCnText->boundingRect().height()/2);

        painter->setPen(sigLinePenAct);
        painter->drawLine(180*zoomX,75*zoomY
                          ,215*zoomX,75*zoomY);
    }else{
        this->signalsCnText->setPen(darkSignalsPen);
        this->signalsCnText->setBrush(darkSignalsBrush);
        this->signalsCnText->setText("Cn-0");
        this->signalsCnText->setPos(220*zoomX
                                   ,75*zoomY-this->signalsCnText->boundingRect().height()/2);

        painter->setPen(sigLinePen);
        painter->drawLine(180*zoomX,75*zoomY
                          ,215*zoomX,75*zoomY);
    }

    QPainterPath aluToBus;
    aluToBus.moveTo(110*zoomX,-3);
    aluToBus.lineTo(110*zoomX,-30*zoomY);
    aluToBus.lineTo(270*zoomX,-30*zoomY);
    aluToBus.lineTo(270*zoomX,250*zoomY);

    if(this->data->statu_alub){
        this->toBusLine->setPen(linePenAct);
        this->toBusLine->setPath(aluToBus);
        this->setZValue(100);
        this->toBusLine->setZValue(100);
    }else{
        this->toBusLine->setPen(linePen);
        this->toBusLine->setPath(aluToBus);
        this->setZValue(0);
        this->toBusLine->setZValue(0);
    }
    painter->restore();
}

ALUQGItem::ALUQGItem()
{
    this->data=nullptr;
}

ALUQGItem::ALUQGItem(systemDataSet* dataSet,QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
    this->setZValue(0);
    this->data=dataSet;

    bodyPath=new QPainterPath();

    bodyShadowEff=new QGraphicsDropShadowEffect();
    bodyShadowEff->setOffset(5,5);
    bodyShadowEff->setColor(Qt::gray);
    bodyShadowEff->setBlurRadius(15);

    body=new QGraphicsPathItem(this);
    body->setPen(aluBodyPen);
    body->setBrush(aluBodyBrush);

    body->setGraphicsEffect(bodyShadowEff);

    nameText=new QGraphicsSimpleTextItem(this);
    this->nameText->setText("ALU");
    this->nameText->setPen(lightTextPen);
    this->nameText->setBrush(ligthTextBrush);
    this->nameText->setFont(bigNameTextFont);

    dataText=new QGraphicsSimpleTextItem(this);
    this->dataText->setPen(lightTextPen);
    this->dataText->setBrush(ligthTextBrush);
    this->dataText->setFont(bigDataTextFont);

    signalsMText=new QGraphicsSimpleTextItem(this);
    this->signalsMText->setFont(smallSignalsFont);

    signalsCnText=new QGraphicsSimpleTextItem(this);
    this->signalsCnText->setFont(smallSignalsFont);

    signalsS0Text=new QGraphicsSimpleTextItem(this);
    this->signalsS0Text->setFont(smallSignalsFont);

    signalsS1Text=new QGraphicsSimpleTextItem(this);
    this->signalsS1Text->setFont(smallSignalsFont);

    signalsS2Text=new QGraphicsSimpleTextItem(this);
    this->signalsS2Text->setFont(smallSignalsFont);

    signalsS3Text=new QGraphicsSimpleTextItem(this);
    this->signalsS3Text->setFont(smallSignalsFont);

    toBusLine=new QGraphicsPathItem(this);
}
