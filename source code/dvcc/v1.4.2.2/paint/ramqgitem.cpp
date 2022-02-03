#include "ramqgitem.h"
QRectF RamQGItem::boundingRect() const
{
    return QRectF(this->mapFromScene(200*this->data->zoomXPer,-250*this->data->zoomYPer),
                  QSizeF(150*this->data->zoomXPer,390*this->data->zoomYPer));
}

void RamQGItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    if(this->data->load_ram==false){
        return;
    }

    //数据准备
    double zoomX=this->data->zoomXPer;
    double zoomY=this->data->zoomYPer;

    //位置设定
    this->setPos(200*zoomX,-250*zoomY);

    //Body draw
    bodyPath->clear();
    bodyPath->moveTo(0,0);
    bodyPath->addRoundedRect(QRectF(0,0,150*zoomX,190*zoomY),10,10);
    bodyPath->closeSubpath();

    this->body->setPath(*this->bodyPath);

    //Cir draw
    cirPath->clear();
    cirPath->addEllipse(QRectF(110*zoomX,10*zoomY,25*zoomX,25*zoomX));
    this->cir->setPath(*this->cirPath);

    //Name draw
    this->nameText->setPos(5*zoomX,0);

    //Data draw
    if(this->data->signal_ce==true){
        this->dataText->setPos(75*zoomX-this->dataText->boundingRect().width()/2,40*zoomY);
        if(this->data->signal_we==WRITE){//Write--read data from bus
            this->dataText->setText(this->data->data_bus+"H");
        }else{//Read--read data from ram
            this->dataText->setText(QString("%0%1H")
                                        .arg(this->data->data_ram[this->data->data_ar][0])
                                        .arg(this->data->data_ram[this->data->data_ar][1])
                                    );
        }
    }else{
        this->dataText->setText("");
    }

    //sig--ce draw
    if(this->data->signal_ce){
        this->signalsText->setPen(lightSignalsPenAct);
        this->signalsText->setBrush(lightSignalsBrushAct);
        this->signalsText->setText("CE: Valid");
        this->signalsText->setPos(75*zoomX-this->signalsText->boundingRect().width()/2,90*zoomY);
    }else{
        this->signalsText->setPen(lightSignalsPen);
        this->signalsText->setBrush(lightSignalsBrush);
        this->signalsText->setText("CE: Invalid");
        this->signalsText->setPos(75*zoomX-this->signalsText->boundingRect().width()/2,90*zoomY);
    }

    //sig--we draw
    if(this->data->signal_we==WRITE){
        this->signalsText2->setPen(lightSignalsPenAct);
        this->signalsText2->setBrush(lightSignalsBrushAct);
        this->signalsText2->setText("WE: 1-Write");
        this->signalsText2->setPos(75*zoomX-this->signalsText->boundingRect().width()/2,120*zoomY);
    }else{
        this->signalsText2->setPen(lightSignalsPen);
        this->signalsText2->setBrush(lightSignalsBrush);
        this->signalsText2->setText("WE: 0-Read");
        this->signalsText2->setPos(75*zoomX-this->signalsText->boundingRect().width()/2,120*zoomY);
    }

    //Ram<--Bus line
    if(this->data->signal_ce==true){
        this->toBusLine->setPen(linePenAct);
        this->setZValue(100);
    }else{
        this->toBusLine->setPen(linePen);
        this->setZValue(0);
    }
    this->toBusLine->setLine(75*zoomX+3,190*zoomY+4,75*zoomX+3,250*zoomY);
}

RamQGItem::RamQGItem(systemDataSet *data,QGraphicsItem *parent)
    :QGraphicsItem(parent)
{
//    this->setZValue(0);
    this->data=data;

    bodyPath=new QPainterPath();

    bodyShadowEff=new QGraphicsDropShadowEffect();
    bodyShadowEff->setOffset(5,5);
    bodyShadowEff->setColor(Qt::gray);
    bodyShadowEff->setBlurRadius(15);

    body=new QGraphicsPathItem(this);
    body->setPen(ramBodyPen);
    body->setBrush(ramBodyBrush);

    body->setGraphicsEffect(bodyShadowEff);

    cirPath=new QPainterPath();
    cir=new QGraphicsPathItem(this);
    cir->setPen(ramCirPen);
    cir->setBrush(ramCirBrush);

    nameText=new QGraphicsSimpleTextItem(this);

    this->nameText->setText("RAM");
    this->nameText->setPen(lightTextPen);
    this->nameText->setBrush(ligthTextBrush);
    this->nameText->setFont(bigNameTextFont);

    dataText=new QGraphicsSimpleTextItem(this);
    this->dataText->setPen(lightTextPen);
    this->dataText->setBrush(ligthTextBrush);
    this->dataText->setFont(bigDataTextFont);

    signalsText=new QGraphicsSimpleTextItem(this);
    this->signalsText->setFont(bigSignalsFont);

    signalsText2=new QGraphicsSimpleTextItem(this);
    this->signalsText2->setFont(bigSignalsFont);

    toBusLine=new QGraphicsLineItem(this);
}
