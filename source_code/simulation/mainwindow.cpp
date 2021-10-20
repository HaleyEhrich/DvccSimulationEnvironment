#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functionSet.h"

#include <QPainter>

using namespace std;

//窗体构建
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //主界面构建
    ui->setupUi(this);

    //statuBar初始化

    QFont ft;
    ft.setPointSize(10);
    ft.setBold(true);
    //
    this->statusBarLable=new QLabel(this);
    this->statusBarLable->setTextFormat(Qt::RichText);
    this->statusBarLable->setFont(ft);
    this->statusBarLable->setText("<div>produced by HE STUDIO</div>");
    statusBar()->addPermanentWidget(this->statusBarLable);//永久信息窗口 - 不会被一般消息覆盖

    this->statusBarLable=new QLabel(this);
    this->statusBarLable->setFont(ft);
    this->statusBarLable->setTextFormat(Qt::RichText);
    this->statusBarLable->setText("<div>自动运行|微程序文件未加载</div>");
    statusBar()->addWidget(this->statusBarLable);
    //数据集生成
    this->data=new _data();

    //开始微地址
    dataDTransH(this->data->startMroAd,this->data->tempString);
    this->ui->startMircoADInput->setText(QString::fromStdString(this->data->tempString));
    //起始微地址输入内容约束
    this->ui->startMircoADInput->setValidator(new QRegularExpressionValidator(*new QRegularExpression("[0-9ABCDEF]{0,2}"), this));

    //KD7-KD1 开关数据
    dataDTransH(this->data->swiInputData,this->data->tempString);
    this->ui->swiInput->setText(QString::fromStdString(this->data->tempString));
    this->ui->swiInput->setValidator(new QRegularExpressionValidator(*new QRegularExpression("[0-9ABCDEF]{0,2}"), this));

    //S3-S0 M CN 功能开关设置
    this->ui->functionInput->setText("000000");
    this->ui->functionInput->setValidator(new QRegularExpressionValidator(*new QRegularExpression("[01]{6,6}"), this));

    //ram check pannel set
    this->ramPannel=new RAMCheck(nullptr,this->data);
    this->ramPannel->hide();

    //rom check pannel set
    this->romPannel=new ROMCheck(nullptr,this->data);
    this->romPannel->hide();


    //open file set
    this->proFile=nullptr;
}

//窗口关闭
MainWindow::~MainWindow()
{
    delete this->ramPannel;
    delete this->romPannel;
    delete this->data;
    delete this->statusBarLable;
    delete this->proFile;
    delete ui;
}


//---------------------------文件菜单实现-------------------
//新窗口
void MainWindow::on_FMnewWin_triggered()
{
    MainWindow *newWindow=new MainWindow;
    newWindow->show();
}

//复制内容识别
void MainWindow::on_FMpasteFile_triggered()
{

    QString text = QInputDialog::getMultiLineText(this,tr("输入微程序代码"),tr("黏贴于此处"));
    if (text.isEmpty())
    {
        QMessageBox::information(this,"","empty");
    }
    else
    {
        QMessageBox::information(this,"","Unempty");
        string line;
        QStringList list=text.split("\n");
        for(int i=0;i<list.length();++i){
            line=list[i].toStdString();
            if (line[0] == '$') {
                int address = dataHTransD(line[2], line[3]);
                if (line[1] == 'P') {//程序区
                    this->data->ram[address][0] = line[4];
                    this->data->ram[address][1] = line[5];
                }
                else if (line[1] == 'M') {
                    string trans="0000";
                    dataHTransB(line[8], trans);
                    this->data->rom[address][24] = trans[0];
                    this->data->rom[address][23] = trans[1];
                    this->data->rom[address][22] = trans[2];
                    this->data->rom[address][21] = trans[3];
                    dataHTransB(line[9], trans);
                    this->data-> rom[address][20] = trans[0];
                    this->data->rom[address][19] = trans[1];
                    this->data->rom[address][18] = trans[2];
                    this->data->rom[address][17] = trans[3];
                    dataHTransB(line[6], trans);
                    this->data->rom[address][16] = trans[0];
                    this->data->rom[address][15] = trans[1];
                    this->data->rom[address][14] = trans[2];
                    this->data->rom[address][13] = trans[3];
                    dataHTransB(line[7], trans);
                    this->data->rom[address][12] = trans[0];
                    this->data->rom[address][11] = trans[1];
                    this->data->rom[address][10] = trans[2];
                    this->data->rom[address][9] = trans[3];
                    dataHTransB(line[4], trans);
                    this->data->rom[address][8] = trans[0];
                    this->data->rom[address][7] = trans[1];
                    this->data->rom[address][6] = trans[2];
                    this->data->rom[address][5] = trans[3];
                    dataHTransB(line[5], trans);
                    this->data->rom[address][4] = trans[0];
                    this->data->rom[address][3] = trans[1];
                    this->data->rom[address][2] = trans[2];
                    this->data->rom[address][1] = trans[3];
                }

        }

        }
    }
}

//打开文件读取到内存内
void MainWindow::on_FMopenFile_triggered()
{

    QString filePath=QFileDialog::getOpenFileName(this,
                tr("打开文件"),
                QDir::currentPath(),
                "txt(*.txt);;other(*.*)");
    statusBar()->showMessage("程序文件:"+filePath,1000);
    filePath.replace("/","\\");
    this->proFile=new QFile(filePath);
    this->proFile->open(QIODevice::ReadWrite | QIODevice::Text);
    retryOpen:
    if(this->proFile->isOpen()==false){
        switch (QMessageBox::critical(this,tr("错误"),tr("文件打开失败!"),QMessageBox::Retry,QMessageBox::Cancel)){
        case QMessageBox::Retry:{
            goto retryOpen;
            break;
        }
        case QMessageBox::Cancel:{
            return;
            break;
        }
        }
    }else{
        string line;
        while (this->proFile->atEnd() == false) {
            line=this->proFile->readLine();
            if (line[0] == '$') {
                int address = dataHTransD(line[2], line[3]);
                if (line[1] == 'P') {//程序区
                    this->data->ram[address][0] = line[4];
                    this->data->ram[address][1] = line[5];
                }
                else if (line[1] == 'M') {
                    string trans="0000";
                    dataHTransB(line[8], trans);
                    this->data->rom[address][24] = trans[0];
                    this->data->rom[address][23] = trans[1];
                    this->data->rom[address][22] = trans[2];
                    this->data->rom[address][21] = trans[3];
                    dataHTransB(line[9], trans);
                    this->data-> rom[address][20] = trans[0];
                    this->data->rom[address][19] = trans[1];
                    this->data->rom[address][18] = trans[2];
                    this->data->rom[address][17] = trans[3];
                    dataHTransB(line[6], trans);
                    this->data->rom[address][16] = trans[0];
                    this->data->rom[address][15] = trans[1];
                    this->data->rom[address][14] = trans[2];
                    this->data->rom[address][13] = trans[3];
                    dataHTransB(line[7], trans);
                    this->data->rom[address][12] = trans[0];
                    this->data->rom[address][11] = trans[1];
                    this->data->rom[address][10] = trans[2];
                    this->data->rom[address][9] = trans[3];
                    dataHTransB(line[4], trans);
                    this->data->rom[address][8] = trans[0];
                    this->data->rom[address][7] = trans[1];
                    this->data->rom[address][6] = trans[2];
                    this->data->rom[address][5] = trans[3];
                    dataHTransB(line[5], trans);
                    this->data->rom[address][4] = trans[0];
                    this->data->rom[address][3] = trans[1];
                    this->data->rom[address][2] = trans[2];
                    this->data->rom[address][1] = trans[3];
                }
            }
        }
        this->ramPannel->freshData();
        this->romPannel->freshData();
        this->ui->FMsaveFile->setEnabled(true);
        this->statusBarLable->setText("自动运行|微程序文件已加载!");
    }

}

//保存文件
void MainWindow::on_FMsaveFile_triggered()
{
    QTextStream out(this->proFile);
    QString dataOut;
    int a1=0;
    int a2=0;
    bool flag=true;//输出换行标志

    out<<"//-------Ram程序区域-------\n";
    for(int i=0;i<256;++i){
        dataOut="$P";
        dataOut.append(this->romPannel->hexNumberSet[a1]);
        dataOut.append(this->romPannel->hexNumberSet[a2]);
        dataOut.append(this->data->ram[i][0]);
        dataOut.append(this->data->ram[i][1]);
        if(this->data->ram[i][0]=='0'&&this->data->ram[i][1]=='0'){
            if(flag){
                flag=false;
                out<<"\n";
            }
        }else{
            out<<dataOut<<"\n";
        }
        if(a2==15){
            a2=0;
            a1++;
        }else{
            a2++;
        }
    }
    a1=a2=0;
    flag=true;

    out<<"//-------Rom程序区域-------\n";
    for(int i=0;i<100;++i){
        this->romPannel->getHex(i,dataOut);
        if(dataOut!="000000"){
            dataOut.insert(0,this->romPannel->hexNumberSet[a2]);
            dataOut.insert(0,this->romPannel->hexNumberSet[a1]);
            dataOut.insert(0,"$M");
            out<<dataOut<<"\n";
        }else{
            if(flag){
                flag=false;
                out<<'\n';
            }
        }
        if(a2==15){
            a2=0;
            a1++;
        }else{
            a2++;
        }
    }
    out<<"//生成时间: "<<QTime::currentTime().toString();
    statusBar()->showMessage("文件保存成功",2);
}

//另存文件
void MainWindow::on_FMSaveAs_triggered()
{
    QString filePath=QFileDialog::getExistingDirectory(this,
                tr("选择保存位置"),
                QDir::currentPath());
    if(filePath.isEmpty()){
       statusBar()->showMessage("文件路径不存在，另存失败",3);
    }
    filePath+="/fileSave_"+QDateTime::currentDateTime().toString("yy-MM-dd_hh-mm-ss")+".txt";
    retryOpen:
    QFile saveAs(filePath);
    saveAs.open(QIODevice::ReadWrite | QIODevice::Text);
    //QMessageBox::information(this,"",filePath);
    if(saveAs.isOpen()==false){
        switch (QMessageBox::critical(this,tr("错误"),tr("文件保存失败!"),QMessageBox::Retry,QMessageBox::Cancel)){
        case QMessageBox::Retry:{
            goto retryOpen;
            break;
        }
        case QMessageBox::Cancel:{
            return;
            break;
        }
        }
    }else{
        QTextStream out(&saveAs);
        QString dataOut;
        int a1=0;
        int a2=0;
        bool flag=true;//输出换行标志

        for(int i=0;i<256;++i){
            dataOut="$P";
            dataOut.append(this->romPannel->hexNumberSet[a1]);
            dataOut.append(this->romPannel->hexNumberSet[a2]);
            dataOut.append(this->data->ram[i][0]);
            dataOut.append(this->data->ram[i][1]);
            if(this->data->ram[i][0]=='0'&&this->data->ram[i][1]=='0'){
                if(flag){
                    flag=false;
                    out<<"\n";
                }
            }else{
                out<<dataOut<<"\n";
            }
            if(a2==15){
                a2=0;
                a1++;
            }else{
                a2++;
            }
        }
        a1=a2=0;
        flag=true;

        out<<"\n";
        for(int i=0;i<100;++i){
            this->romPannel->getHex(i,dataOut);
            if(dataOut!="000000"){
                dataOut.insert(0,this->romPannel->hexNumberSet[a2]);
                dataOut.insert(0,this->romPannel->hexNumberSet[a1]);
                dataOut.insert(0,"$M");
                out<<dataOut<<"\n";
            }else{
                if(flag){
                    flag=false;
                    out<<'\n';
                }
            }
            if(a2==15){
                a2=0;
                a1++;
            }else{
                a2++;
            }
        }
        statusBar()->showMessage("文件另存成功",2);
    }
}

//内存编辑器
void MainWindow::on_FMeditor_triggered()
{
    this->ramPannel->editModel();
    this->romPannel->editModel();
}


//-------------------------------面板菜单实现--------------------
//RAM查看面板
void MainWindow::on_PMRAM_triggered()
{
    if(this->ramPannel->isHidden()==true){
        this->ramPannel->freshData();
        this->ramPannel->show();
    }
}

//ROM查看面板
void MainWindow::on_PMROM_triggered()
{
    if(this->romPannel->isHidden()==true){
        this->romPannel->freshData();
        this->romPannel->show();
    }
}

//控制开关面板
//void MainWindow::on_PMswitch_triggered()
//{

//}


//--------------------------选项菜单实现-------------------------
//恢复窗口的默认大小
void MainWindow::on_OMdefaultWinSize_triggered()
{
    if(this->width()==1300&&this->height()==775){
        //可设置为居中显示
    }else{
        this->resize(1300,775);
    }
}

//AR部件接入实现
void MainWindow::on_ALUAcess_triggered()
{
    if(this->ui->ALUAcess->isChecked()==true){
        this->data->Acess_ALU=true;
        this->ui->swi_LDDR1->setEnabled(true);
        this->ui->swi_LDDR2->setEnabled(true);
        this->ui->swi_ALUB->setEnabled(true);
        this->ui->swi_AR->setEnabled(true);
    }else{
        this->data->Acess_ALU=false;
        this->ui->swi_LDDR1->setEnabled(false);
        this->ui->swi_LDDR2->setEnabled(false);
        this->ui->swi_ALUB->setEnabled(false);
        this->ui->swi_AR->setEnabled(false);
    }
}

//RAM接入电路
void MainWindow::on_RAMAcess_triggered()
{
    if(this->ui->RAMAcess->isChecked()==true){
        this->data->Acess_RAM=true;
        this->ui->swi_LDAR->setEnabled(true);
        this->ui->swi_CE->setEnabled(true);
        this->ui->swi_WE->setEnabled(true);
    }else{
        this->data->Acess_RAM=false;
        this->ui->swi_LDAR->setEnabled(false);
        this->ui->swi_CE->setEnabled(false);
        this->ui->swi_WE->setEnabled(false);
    }
}

//299移位寄存器接入实现
void MainWindow::on_a299Acess_triggered()
{
    if(this->ui->a299Acess->isChecked()==true){
        this->data->Acess_299=true;
        this->ui->swi_299B->setEnabled(true);
    }else{
        this->data->Acess_299=false;
        this->ui->swi_299B->setEnabled(false);
    }
}

//寄存器组接入电路实现
void MainWindow::on_registerAcess_triggered()
{
    if(this->ui->registerAcess->isChecked()==true){
        this->data->Acess_res=true;
    }else{
        this->data->Acess_res=false;
    }
}

//微控器接入电路实现
void MainWindow::on_microControlAcess_triggered()
{
    if(this->ui->microControlAcess->isChecked()==true){
        this->data->Acess_Mro=true;
        this->ui->swi_PCB->setEnabled(true);
        this->ui->swi_LDPC->setEnabled(true);
        this->ui->swi_LDAD->setEnabled(true);
        this->ui->microAdressSetGroup->setEnabled(true);
        //解决重复调用函数autoRun
        if(this->ui->autoRun->isChecked()==false){
            this->ui->autoRun->setChecked(true);
            on_autoRun_clicked();
        }
    }else{
        this->data->Acess_Mro=false;
        this->ui->swi_PCB->setEnabled(false);
        this->ui->swi_LDPC->setEnabled(false);
        this->ui->swi_LDAD->setEnabled(false);
        this->ui->microAdressSetGroup->setEnabled(false);
        this->ui->autoRun->setChecked(false);
        on_autoRun_clicked();
    }
}


//--------------------------关于菜单实现-------------------------
//使用说明
void MainWindow::on_AMinstructions_triggered()
{
    //todo：使用说明
}

//制作信息
void MainWindow::on_AMInfo_triggered()
{
    QMessageBox aboutMsg(this);
    aboutMsg.setTextInteractionFlags(Qt::TextSelectableByMouse);
    aboutMsg.setTextFormat(Qt::RichText);
    aboutMsg.addButton(tr("跳转GitHub"), QMessageBox::ActionRole);
    aboutMsg.addButton(QMessageBox::Close);
    aboutMsg.setText("<h4>软件开源地址</h4>https://github.com/HaleyEhrich/DvccSimulationEnvironment<br/>"
                     "<h4>问题反馈联系方式</h4> <a>haley_ehrich@outlook.com</a> <br>"
                     "<h4>软件构造平台</h4> Qt 5.15.2 (MSVC 2019, 64 bit)");
    aboutMsg.setWindowTitle("制作信息");
    aboutMsg.show();
    int res=aboutMsg.exec();
    if(res==QMessageBox::Close){
        aboutMsg.close();
    }else{
        QDesktopServices::openUrl(QUrl("https://github.com/HaleyEhrich/DvccSimulationEnvironment"));
    }

}


//---------------------------------------电路图绘制------------------------------
void MainWindow::resizeEvent(QResizeEvent *event){
    this->data->zoomPerX=(double)MainWindow::width()/1300;
    this->data->zoomPerY=(double)MainWindow::height()/775;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    //根据data内数据的值确定画的类型

    //笔刷初始化
    QPainter *painter=new QPainter(this);
    painter->setRenderHint(QPainter::Antialiasing, true);
    // 设置字体
    QFont font;
    font.setFamily("阿里巴巴普惠体 R");
    font.setPointSize(15);
    painter->setFont(font);

    this->paintBusLine(false,painter);
    this->paint299(painter);
    this->paintAlu(painter);
    this->paintDr1(painter);
    this->paintDr2(painter);
    this->paintPc(painter);
    this->paintAr(painter);
    this->paintRam(painter);
    this->paintR0(painter);
    this->paintR1(painter);
    this->paintR2(painter);
    this->paintIr(painter);
    this->paintMroCon(painter);
    this->paintInput(painter);
    this->paintOutput(painter);
    this->paintSignal(painter);
    delete painter;

}

//总线绘制
void MainWindow::paintBusLine(bool choose,QPainter *paint){
    if(choose){
        paint->setPen(chooseBusPen);
    }else{
        paint->setPen(busPen);
    }
    paint->drawLine(60,MainWindow::height()/2,960*this->data->zoomPerX,MainWindow::height()/2);
    paint->setPen(signalPen);
    paint->drawText(20,MainWindow::height()/2+8,QString::fromStdString(this->data->busData)+"H");
}

//299
void MainWindow::paint299(QPainter *paint){

    //数据准备
    double zoomX=this->data->zoomPerX;
    double zoomY=this->data->zoomPerY;
    int x=30*zoomX;
    int y=110*zoomY;
    int width=140*zoomX;
    int height=80*zoomY;
    int lineStartX=x+width-50*zoomX;
    int lineStartY=y+height/2;

    //299输入输出冲突判定
    bool flag=false;

    //主体描绘
    paint->setBrush(bodyBrush);
    paint->setPen(bodyPen);
    paint->drawRect(x,y,width,height);
    //paint->drawRoundedRect(x,y,width,height,10,10);
    //信号源，说明符号描绘
    paint->setPen(QColor(desWordColor));
    paint->drawText(x,y-5*zoomY,"299");

    //4条信号线
    paint->setPen(signalPen);
    //line signal 299-BUS
    paint->drawLine(lineStartX,y,lineStartX,y-20);
    //line signal s0
    paint->drawLine(x+width,lineStartY-20*zoomY,x+width+20*zoomX,lineStartY-20*zoomY);
    //line signal s1
    paint->drawLine(x+width,lineStartY,x+width+20*zoomX,lineStartY);
    //line signal m
    paint->drawLine(x+width,lineStartY+20*zoomY,x+width+20*zoomX,lineStartY+20*zoomY);

    //299作为输入
    if(this->data->statu_ld299==true){
        paint->setPen(chooseSignalPen);
        flag=true;
    }else{
        paint->setPen(signalPen);
    }

    if(_s0){
        paint->setPen(chooseSignalPen);
        flag=true;
    }else{
        paint->setPen(signalPen);
    }
    paint->drawText(x+width+25*zoomX,lineStartY+6*zoomY,"S0");
    if(_s1){
        paint->setPen(chooseSignalPen);
        flag=true;
    }else{
        paint->setPen(signalPen);
    }
    paint->drawText(x+width+25*zoomX,lineStartY+26*zoomY,"S1");
    if(_m==true){
        paint->setPen(chooseSignalPen);
    }else{
        paint->setPen(signalPen);
    }
    paint->drawText(x+width+25*zoomX,lineStartY-14*zoomY,"M");

    //299作为输出
    if(this->data->statu_299b==true){
        //总线更新
        this->paintBusLine(true,paint);

        paint->setPen(chooseSignalPen);
//        if(flag) statusBar()->showMessage("[Warning]299总线冲突!",2);
        flag=true;
    }else{
        paint->setPen(signalPen);
    }
    paint->drawText(lineStartX+5*zoomX,y-5*zoomY,"299-BUS");

    //判定是否选中总线
    if(flag==true){
        paint->setPen(chooseBusPen);
    }else{
        paint->setPen(busPen);
    }
    //line 299->bus
    //part 1
    paint->drawLine(x+width/2,y,x+width/2,y-40*zoomY);
    //part 2
    paint->drawLine(x+width/2,y-40*zoomY,x+width/2+360*zoomX,y-40*zoomY);
    //part 3
    paint->drawLine(x+width/2+360*zoomX,y-40*zoomY,x+width/2+360*zoomX,MainWindow::height()/2);

    //数据
    paint->setPen(QColor(dataColor));
    dataDTransH(this->data->_299,this->data->tempString);
    paint->drawText(x+width/2,y+height/2,QString::fromStdString(this->data->tempString)+"H");
}

//ALU
void MainWindow::paintAlu(QPainter *paint){
    //数据准备
    double zoomX=this->data->zoomPerX;
    double zoomY=this->data->zoomPerY;
    int x=250*zoomX;
    int y=110*zoomY;
    int width=140*zoomX;
    int height=80*zoomY;
    int lineStartX=x+width-50*zoomX;
    int lineStartY=y+height/2;
    QPointF bodyPosPoint[7]={
        QPointF(x+25*zoomX,y),
        QPointF(x+width-25*zoomX,y),
        QPointF(x+width+20*zoomX,y+height),
        QPointF(x+width/2+20*zoomX,y+height),
        QPointF(x+width/2,y+height-30*zoomY),
        QPointF(x+width/2-20*zoomX,y+height),
        QPointF(x-20*zoomX,y+height)
    };

    //7条信号线
    paint->setPen(signalPen);
    //line signal alu-bus
    paint->drawLine(lineStartX,y,lineStartX,y-20);
    //line signal M
    paint->drawLine(x+20*zoomX,lineStartY-20*zoomY,x-25*zoomX,lineStartY-20*zoomY);
    //line signal s3
    paint->drawLine(x+20*zoomX,lineStartY,x-25*zoomX,lineStartY);
    //line signal cn
    paint->drawLine(x+20*zoomX,lineStartY+20*zoomY,x-25*zoomX,lineStartY+20*zoomY);
    //line signal S2
    paint->drawLine(x+width-20*zoomX,lineStartY-20*zoomY,x+width+20*zoomX,lineStartY-20*zoomY);
    //line signal S3
    paint->drawLine(x+width-20*zoomX,lineStartY,x+width+20*zoomX,lineStartY);
    //line signal Cn
    paint->drawLine(x+width-20*zoomX,lineStartY+20*zoomY,x+width+20*zoomX,lineStartY+20*zoomY);

    //主体描绘
    paint->setBrush(bodyBrush);
    paint->setPen(bodyPen);
    paint->drawPolygon(bodyPosPoint, 7);

    //信号源，说明符号描绘
    paint->setPen(QColor(desWordColor));
    paint->drawText(x,y-5*zoomY,"ALU");

    //左侧3信号
    if(_s2){
        paint->setPen(chooseSignalPen);
    }else{
        paint->setPen(signalPen);
    }
    paint->drawText(x+width+25*zoomX,lineStartY-14*zoomY,"S2");
    if(_s2){
        paint->setPen(chooseSignalPen);
    }else{
        paint->setPen(signalPen);
    }
    paint->drawText(x+width+25*zoomX,lineStartY+6*zoomY,"S3");
    if(_cn){
        paint->setPen(chooseSignalPen);
    }else{
        paint->setPen(signalPen);
    }
    paint->drawText(x+width+25*zoomX,lineStartY+26*zoomY,"CN");

    //ALU作为输出
    if(this->data->statu_alub==true){
        //总线更新
        this->paintBusLine(true,paint);

        //数据
        paint->setPen(QColor(dataColor));
        paint->drawText(x+width/2,y+height/2,QString::fromStdString(this->data->busData)+"H");

        paint->setPen(chooseSignalPen);
        paint->drawText(lineStartX+5*zoomX,y-5*zoomY,"ALU-BUS");
        //总线
        paint->setPen(chooseBusPen);
        //line alu->bus
        paint->drawLine(x+width/2,y-40*zoomY,x+width/2+140*zoomX,y-40*zoomY);
        //line alu->bus
        paint->drawLine(x+width/2+140*zoomX,y-40*zoomY,x+width/2+140*zoomX,MainWindow::height()/2);

    }else{
        paint->setPen(signalPen);
        paint->drawText(lineStartX+5*zoomX,y-5*zoomY,"ALU-BUS");
        paint->setPen(busPen);
    }

    //line alu->bus
    paint->drawLine(x+width/2,y,x+width/2,y-40*zoomY);
}

//dr1
void MainWindow::paintDr1(QPainter *paint){
    //数据准备
    double zoomX=this->data->zoomPerX;
    double zoomY=this->data->zoomPerY;
    int x=230*zoomX;
    int y=270*zoomY;
    int width=80*zoomX;
    int height=50*zoomY;
    int lineStartX=x+width-20*zoomX;

//    bool flag=false;
    //主体描绘
    paint->setBrush(bodyBrush);
    paint->setPen(bodyPen);
    paint->drawRect(x,y,width,height);
    //paint->drawRoundedRect(x,y,width,height,10,10);

    //信号源，说明符号描绘
    paint->setPen(QColor(desWordColor));
    paint->drawText(x,y-5*zoomY,"DR1");

    //信号线
    paint->setPen(signalPen);
    //line signal lddr1
    paint->drawLine(lineStartX,y+50,lineStartX,y+70);

    //DR1作为输入
    if(this->data->statu_lddr1==true){
        paint->setPen(chooseSignalPen);
        paint->drawText(lineStartX+5,y+70,"LDDR1");
        paint->setPen(chooseBusPen);
//        flag=true;
    }else{
        paint->setPen(signalPen);
        paint->drawText(lineStartX+5,y+70,"LDDR1");
        paint->setPen(busPen);
    }
    paint->drawLine(x+width/2,y+50,x+width/2,MainWindow::height()/2);

    //DR1作为输出
    if(this->data->statu_alub==true){
        paint->setPen(chooseBusPen);
//        if(flag==true) statusBar()->showMessage("[Warning]DR1同时输出输入!",2);
    }else{
        paint->setPen(busPen);
    }
    //line-dr1->alu
    paint->drawLine(x+width/2,y,x+width/2,y-80);


    //数据
    paint->setPen(QColor(dataColor));
    dataDTransH(this->data->dr1,this->data->tempString);
    paint->drawText(x+width/2,y+height/2,QString::fromStdString(this->data->tempString)+"H");
}

//dr2
void MainWindow::paintDr2(QPainter *paint){
    //数据准备
    double zoomX=this->data->zoomPerX;
    double zoomY=this->data->zoomPerY;
    int x=330*zoomX;
    int y=270*zoomY;
    int width=80*zoomX;
    int height=50*zoomY;
    int lineStartX=x+width-20*zoomX;

//    bool flag=false;
    //主体描绘
    paint->setBrush(bodyBrush);
    paint->setPen(bodyPen);
    paint->drawRect(x,y,width,height);
    //paint->drawRoundedRect(x,y,width,height,10,10);

    //信号源，说明符号描绘
    paint->setPen(QColor(desWordColor));
    paint->drawText(x,y-5*zoomY,"DR2");

    //信号线
    paint->setPen(signalPen);
    //line signal lddr1
    paint->drawLine(lineStartX,y+50,lineStartX,y+70);


    //DR2作为输入
    if(this->data->statu_lddr2==true){
        paint->setPen(chooseSignalPen);
        paint->drawText(lineStartX+5,y+70,"LDDR2");
        paint->setPen(chooseBusPen);
//        flag=true;
    }else{
        paint->setPen(signalPen);
        paint->drawText(lineStartX+5,y+70,"LDDR2");
        paint->setPen(busPen);
    }
    paint->drawLine(x+width/2,y+50,x+width/2,MainWindow::height()/2);

    //DR2作为输出
    if(this->data->statu_alub==true){
        paint->setPen(chooseBusPen);
//        if(flag==true) statusBar()->showMessage("[Warning]DR2同时输出输入!",2);
    }else{
        paint->setPen(busPen);
    }
    //line-dr1->alu
    paint->drawLine(x+width/2,y,x+width/2,y-80);


    //数据
    paint->setPen(QColor(dataColor));
    dataDTransH(this->data->dr2,this->data->tempString);
    paint->drawText(x+width/2,y+height/2,QString::fromStdString(this->data->tempString)+"H");
}

//pc
void MainWindow::paintPc(QPainter *paint){
    //数据准备
    double zoomX=this->data->zoomPerX;
    double zoomY=this->data->zoomPerY;
    int x=510*zoomX;
    int y=270*zoomY;
    int width=80*zoomX;
    int height=50*zoomY;
    int lineStartX=x+width-20*zoomX;

//    bool flag=false;
    //主体描绘
    paint->setBrush(bodyBrush);
    paint->setPen(bodyPen);
    paint->drawRect(x,y,width,height);
    //paint->drawRoundedRect(x,y,width,height,10,10);

    //信号源，说明符号描绘
    paint->setPen(QColor(desWordColor));
    paint->drawText(x,y-5*zoomY,"PC");


    paint->setPen(signalPen);

    //line signal ldad
    paint->drawLine(lineStartX,y+height,lineStartX,y+height+20*zoomY);
    //line siganl ldpc
    paint->drawLine(lineStartX,y,lineStartX,y-20*zoomY);
    //line siganl pc-Bus
    paint->drawLine(x+width/2-20*zoomX,y+height,x+width/2-20*zoomX,y+height+20*zoomY);



    //pc选中
    if(this->data->statu_ldpc==true){
        paint->setPen(chooseSignalPen);
    }else{
        paint->setPen(signalPen);
    }
    paint->drawText(lineStartX+5,y-5*zoomY,"LDPC");

    //pc作为输入
    if(this->data->statu_ldad==true){
        paint->setPen(chooseSignalPen);
        paint->drawText(lineStartX+5*zoomX,y+70*zoomY,"LDAD");
        if(this->data->statu_ldpc!=true){
            paint->setPen(busPen);
            statusBar()->showMessage("[Warning]PC未选中但PC选中输入!",2);
        }else{
            paint->setPen(chooseBusPen);
        }
    }else{
        paint->setPen(signalPen);
        paint->drawText(lineStartX+5*zoomX,y+70*zoomY,"LDAD");
        paint->setPen(busPen);
    }
    //line bus->PC
    paint->drawLine(x+width/2,y+50*zoomY,x+width/2,MainWindow::height()/2);


    //PC作为输出
    if(this->data->statu_pcb==true){
        //busLien updata
        if(this->data->statu_ldpc)this->paintBusLine(true,paint);
        paint->setPen(chooseSignalPen);
        paint->drawText(x+width/2-70*zoomX,y+height+20*zoomY,"PC-B");
        if(this->data->statu_ldpc!=true){
            paint->setPen(busPen);
//            statusBar()->showMessage("[Warning]PC未选中但PC选中输出!",2);
        }else{
            paint->setPen(chooseBusPen);
            //line pc->bus
            //part 3
            paint->drawLine(x+width/2-90*zoomX,y-40*zoomY,x+width/2-90*zoomX,MainWindow::height()/2);
        }
//        if(flag==true) statusBar()->showMessage("[Warning]PC同时输出输入!",2);
    }else{
        paint->setPen(signalPen);
        paint->drawText(x+width/2-70*zoomX,y+height+20*zoomY,"PC-B");
        paint->setPen(busPen);
    }
    //line pc->bus
    //part 1
    paint->drawLine(x+width/2,y,x+width/2,y-40*zoomY);
    //part 2
    paint->drawLine(x+width/2,y-40*zoomY,x+width/2-90*zoomX,y-40*zoomY);


    //数据
    paint->setPen(QColor(dataColor));
    dataDTransH(this->data->pc,this->data->tempString);
    paint->drawText(x+width/2,y+height/2,QString::fromStdString(this->data->tempString)+"H");
}

//ar
void MainWindow::paintAr(QPainter *paint){
    //数据准备
    double zoomX=this->data->zoomPerX;
    double zoomY=this->data->zoomPerY;
    int x=510*zoomX;
    int y=140*zoomY;
    int width=80*zoomX;
    int height=50*zoomY;
    int lineStartX=x+width-20*zoomX;

    //主体描绘
    paint->setBrush(bodyBrush);
    paint->setPen(bodyPen);
    paint->drawRect(x,y,width,height);
    //paint->drawRoundedRect(x,y,width,height,10,10);

    //信号源，说明符号描绘
    paint->setPen(QColor(desWordColor));
    paint->drawText(x,y-5*zoomY,"AR");


    paint->setPen(signalPen);
    //line signal ldar
    paint->drawLine(lineStartX,y+height,lineStartX,y+height+20*zoomY);

    //AR作为输入
    if(this->data->statu_ldar==true){
        paint->setPen(chooseSignalPen);
        paint->drawText(lineStartX+5*zoomX,y+70*zoomY,"LDAR");

        paint->setPen(chooseBusPen);
        //line bus->AR
        //part 2
        paint->drawLine(x+width/2-90*zoomX,y+height+40*zoomY,x+width/2,y+height+40*zoomY);
        //part 3
        paint->drawLine(x+width/2-90*zoomX,y+height+40*zoomY,x+width/2-90*zoomX,MainWindow::height()/2);
//        flag=true;
    }else{
        paint->setPen(signalPen);
        paint->drawText(lineStartX+5*zoomX,y+70*zoomY,"LDAR");
        paint->setPen(busPen);
    }

    //line bus->AR
    //part 1
    paint->drawLine(x+width/2,y+height+40*zoomY,x+width/2,y+height);

    //AR作为输出
    if(this->data->signal_ce==true){
        paint->setPen(chooseBusPen);
        //if(flag==true) statusBar()->showMessage("[Warning]AR同时输出输入!",2);
    }else{
        paint->setPen(busPen);
    }
    //line ar->ram
    //part 1
    paint->drawLine(x+width/2,y,x+width/2,y-70*zoomY);
    //part 2
    paint->drawLine(x+width/2,y-70*zoomY,x+width/2+160*zoomX,y-70*zoomY);
    //part 3
    paint->drawLine(x+width/2+160*zoomX,y-70*zoomY,x+width/2+160*zoomX,y-30*zoomY);

    //数据
    paint->setPen(QColor(dataColor));
    dataDTransH(this->data->ar,this->data->tempString);
    paint->drawText(x+width/2,y+height/2,QString::fromStdString(this->data->tempString)+"H");

}

//ram
void MainWindow::paintRam(QPainter *paint){
    //数据准备
    double zoomX=this->data->zoomPerX;
    double zoomY=this->data->zoomPerY;
    int x=630*zoomX;
    int y=110*zoomY;
    int width=160*zoomX;
    int height=160*zoomY;
    int lineStartX=x+width-40*zoomX;

    //主体描绘
    paint->setBrush(bodyBrush);
    paint->setPen(bodyPen);
    paint->drawRect(x,y,width,height);
    //paint->drawRoundedRect(x,y,width,height,10,10);

    //信号源，说明符号描绘
    paint->setPen(QColor(desWordColor));
    paint->drawText(x,y-5*zoomY,"RAM");

    paint->setPen(signalPen);
    //line signal we
    paint->drawLine(lineStartX,y+height,lineStartX,y+height+20*zoomY);
    //line signal ce
    paint->drawLine(x+width/2,y+height,x+width/2,y+height+20*zoomY);

    //片选信号判断
    if(this->data->signal_ce==true){
        paint->setPen(chooseSignalPen);
        paint->drawText(x+width/2+5,y+height+20*zoomY,"CE");
        paint->setPen(chooseBusPen);
    }else{
        paint->setPen(signalPen);
        paint->drawText(x+width/2+5,y+height+20*zoomY,"CE");
        paint->setPen(busPen);
    }
    //line ram<->bus
    paint->drawLine(x+40*zoomX,y+height,x+40*zoomX,MainWindow::height()/2);

    //RAM读写判断
    if(this->data->signal_we==WRITE){
        paint->setPen(chooseSignalPen);
    }else{
        paint->setPen(signalPen);
        //总线更新
        if(this->data->signal_ce) this->paintBusLine(true,paint);
    }
    paint->drawText(lineStartX+5,y+height+20*zoomY,"WE");

    //数据
    if(this->data->signal_ce){
        paint->setPen(QColor(dataColor));
        paint->drawText(x+width/2,y+height/2,QString::fromStdString(this->data->busData)+"H");
    }
}

//r0
void MainWindow::paintR0(QPainter *paint){
    //数据准备
    double zoomX=this->data->zoomPerX;
    double zoomY=this->data->zoomPerY;
    int x=30*zoomX;
    int y=560*zoomY;
    int width=80*zoomX;
    int height=50*zoomY;
    int lineStartX=x+width-30*zoomX;

    bool flag=false;
    //主体描绘
    paint->setBrush(bodyBrush);
    paint->setPen(bodyPen);
    paint->drawRect(x,y,width,height);
    //paint->drawRoundedRect(x,y,width,height,10,10);


    //信号源，说明符号描绘
    paint->setPen(QColor(desWordColor));
    paint->drawText(x,y-5*zoomY,"R0");

    paint->setPen(signalPen);
    //line r0-bus
    paint->drawLine(lineStartX,y,lineStartX,y-20*zoomY);
    //line ldr0
    paint->drawLine(lineStartX,y+height,lineStartX,y+height+20*zoomY);

    //r0输出
    if(this->data->statu_r0b==true){
        this->paintBusLine(true,paint);
        paint->setPen(chooseSignalPen);
        paint->drawText(lineStartX+5*zoomX,y-5*zoomY,"R0-B");
        paint->setPen(chooseBusPen);

        flag=true;
    }else{
        paint->setPen(signalPen);
        paint->drawText(lineStartX+5*zoomX,y-5*zoomY,"R0-B");
        paint->setPen(busPen);
    }
    //line r0->bus
    paint->drawLine(x+width/2,y,x+width/2,MainWindow::height()/2);

    //r0输入
    if(this->data->statu_ldr0==true){
        paint->setPen(chooseSignalPen);
        paint->drawText(lineStartX+5*zoomX,y+height+20*zoomY,"LDR0");
        paint->setPen(chooseBusPen);
        if(flag) statusBar()->showMessage("[Warning] R0同时输入输出",2);
    }else{
        paint->setPen(signalPen);
        paint->drawText(lineStartX+5*zoomX,y+height+20*zoomY,"LDR0");
        paint->setPen(busPen);
    }
    //line bus->r0
    //part 1
    paint->drawLine(x+width/2,y+height,x+width/2,y+height+40*zoomY);
    //part 2
    paint->drawLine(x+width/2,y+height+40*zoomY,x+width/2+315*zoomX,y+height+40*zoomY);
    //part 3
    paint->drawLine(x+width/2+315*zoomX,y+height+40*zoomY,x+width/2+315*zoomX,MainWindow::height()/2);

    //数据
    paint->setPen(QColor(dataColor));
    dataDTransH(this->data->r0,this->data->tempString);
    paint->drawText(x+width/2,y+height/2,QString::fromStdString(this->data->tempString)+"H");
}

//r1
void MainWindow::paintR1(QPainter *paint){
    //数据准备
    double zoomX=this->data->zoomPerX;
    double zoomY=this->data->zoomPerY;
    int x=145*zoomX;
    int y=560*zoomY;
    int width=80*zoomX;
    int height=50*zoomY;
    int lineStartX=x+width-30*zoomX;

    //主体描绘
    paint->setBrush(bodyBrush);
    paint->setPen(bodyPen);
    paint->drawRect(x,y,width,height);
    //paint->drawRoundedRect(x,y,width,height,10,10);

    //信号源，说明符号描绘
    paint->setPen(QColor(desWordColor));
    paint->drawText(x,y-5*zoomY,"R1");

    paint->setPen(signalPen);
    //line r1-bus
    paint->drawLine(lineStartX,y,lineStartX,y-20*zoomY);
    //line ldr1
    paint->drawLine(lineStartX,y+height,lineStartX,y+height+20*zoomY);

    //r1输出
    if(this->data->statu_r1b==true){
        this->paintBusLine(true,paint);
        paint->setPen(chooseSignalPen);
        paint->drawText(lineStartX+5*zoomX,y-5*zoomY,"R1-B");
        paint->setPen(chooseBusPen);
    }else{
        paint->setPen(signalPen);
        paint->drawText(lineStartX+5*zoomX,y-5*zoomY,"R1-B");
        paint->setPen(busPen);
    }
    //line r1->bus
    paint->drawLine(x+width/2,y,x+width/2,MainWindow::height()/2);


    //r1输入
    if(this->data->statu_ldr1==true){
        paint->setPen(chooseSignalPen);
        paint->drawText(lineStartX+5*zoomX,y+height+20*zoomY,"LDR1");
        paint->setPen(chooseBusPen);
        //part 2
        paint->drawLine(x+width/2,y+height+40*zoomY,x+width/2+200*zoomX,y+height+40*zoomY);
        //part 3
        paint->drawLine(x+width/2+200*zoomX,y+height+40*zoomY,x+width/2+200*zoomX,MainWindow::height()/2);
    }else{
        paint->setPen(signalPen);
        paint->drawText(lineStartX+5*zoomX,y+height+20*zoomY,"LDR0");
        paint->setPen(busPen);
    }
    //line bus->r1
    //part 1
    paint->drawLine(x+width/2,y+height,x+width/2,y+height+40*zoomY);


    //数据
    paint->setPen(QColor(dataColor));
    dataDTransH(this->data->r1,this->data->tempString);
    paint->drawText(x+width/2,y+height/2,QString::fromStdString(this->data->tempString)+"H");
}

//r2
void MainWindow::paintR2(QPainter *paint){
    //数据准备
    double zoomX=this->data->zoomPerX;
    double zoomY=this->data->zoomPerY;
    int x=260*zoomX;
    int y=560*zoomY;
    int width=80*zoomX;
    int height=50*zoomY;
    int lineStartX=x+width-30*zoomX;

    //主体描绘
    paint->setBrush(bodyBrush);
    paint->setPen(bodyPen);
    paint->drawRect(x,y,width,height);
    //paint->drawRoundedRect(x,y,width,height,10,10);


    //信号源，说明符号描绘
    paint->setPen(QColor(desWordColor));
    paint->drawText(x,y-5*zoomY,"R2");

    paint->setPen(signalPen);
    //line r2-bus
    paint->drawLine(lineStartX,y,lineStartX,y-20*zoomY);
    //line ldr2
    paint->drawLine(lineStartX,y+height,lineStartX,y+height+20*zoomY);

    //r0输出
    if(this->data->statu_r0b==true){
        this->paintBusLine(true,paint);
        paint->setPen(chooseSignalPen);
        paint->drawText(lineStartX+5*zoomX,y-5*zoomY,"R2-B");
        paint->setPen(chooseBusPen);
    }else{
        paint->setPen(signalPen);
        paint->drawText(lineStartX+5*zoomX,y-5*zoomY,"R2-B");
        paint->setPen(busPen);
    }
    //line r2->bus
    paint->drawLine(x+width/2,y,x+width/2,MainWindow::height()/2);


    //r1输入
    if(this->data->statu_ldr2==true){
        paint->setPen(chooseSignalPen);
        paint->drawText(lineStartX+5*zoomX,y+height+20*zoomY,"LDR2");
        paint->setPen(chooseBusPen);
        //part 2
        paint->drawLine(x+width/2,y+height+40*zoomY,x+width/2+85*zoomX,y+height+40*zoomY);
        //part 3
        paint->drawLine(x+width/2+85*zoomX,y+height+40*zoomY,x+width/2+85*zoomX,MainWindow::height()/2);
    }else{
        paint->setPen(signalPen);
        paint->drawText(lineStartX+5*zoomX,y+height+20*zoomY,"LDR2");
        paint->setPen(busPen);
    }
    //line bus->r2
    //part 1
    paint->drawLine(x+width/2,y+height,x+width/2,y+height+40*zoomY);


    //数据
    paint->setPen(QColor(dataColor));
    dataDTransH(this->data->r2,this->data->tempString);
    paint->drawText(x+width/2,y+height/2,QString::fromStdString(this->data->tempString)+"H");
}

//ir
void MainWindow::paintIr(QPainter *paint){
    //数据准备
    double zoomX=this->data->zoomPerX;
    double zoomY=this->data->zoomPerY;
    int x=460*zoomX;
    int y=560*zoomY;
    int width=80*zoomX;
    int height=50*zoomY;
    int lineStartX=x+width-30*zoomX;

    //主体描绘
    paint->setBrush(bodyBrush);
    paint->setPen(bodyPen);
    paint->drawRect(x,y,width,height);
    //paint->drawRoundedRect(x,y,width,height,10,10);


    //信号源，说明符号描绘
    paint->setPen(QColor(desWordColor));
    paint->drawText(x,y-5*zoomY,"IR");

    paint->setPen(signalPen);
    //line ldir
    paint->drawLine(lineStartX,y+height,lineStartX,y+height+20*zoomY);

    //ir输出
    if(this->data->statu_irb==true){
        paint->setPen(chooseBusPen);
    }else{
        paint->setPen(busPen);
    }
    //line ir->bus
    paint->drawLine(x+width/2,y,x+width/2,y-30*zoomY);


    //r1输入
    if(this->data->statu_ldir==true){
        paint->setPen(chooseSignalPen);
        paint->drawText(lineStartX+5*zoomX,y+height+20*zoomY,"LDIR");
        paint->setPen(chooseBusPen);
        //part 3
        paint->drawLine(x+width/2-115*zoomX,y+height+40*zoomY,x+width/2-115*zoomX,MainWindow::height()/2);
    }else{
        paint->setPen(signalPen);
        paint->drawText(lineStartX+5*zoomX,y+height+20*zoomY,"LDR0");
        paint->setPen(busPen);
    }
    //line bus->r1
    //part 1
    paint->drawLine(x+width/2,y+height,x+width/2,y+height+40*zoomY);
    //part 2
    paint->drawLine(x+width/2,y+height+40*zoomY,x+width/2-115*zoomX,y+height+40*zoomY);


    //数据
    paint->setPen(QColor(dataColor));
    dataDTransH(this->data->ir,this->data->tempString);
    paint->drawText(x+width/2,y+height/2,QString::fromStdString(this->data->tempString)+"H");
}

//微控器，显示跳转方式/LDPC，PC+1等
void MainWindow::paintMroCon(QPainter *paint){
    //数据准备
    double zoomX=this->data->zoomPerX;
    double zoomY=this->data->zoomPerY;
    int x=430*zoomX;
    int y=460*zoomY;
    int width=140*zoomX;
    int height=80*zoomY;

    //主体描绘
    paint->setBrush(bodyBrush);
    paint->setPen(bodyPen);
    paint->drawRect(x,y,width,height);
    //paint->drawRoundedRect(x,y,width,height,10,10);


    //信号源，说明符号描绘
    paint->setPen(QColor(desWordColor));
    paint->drawText(x,y-5*zoomY,"微控器");
}

//输入，在输入框变化后需要注意数据改变
void MainWindow::paintInput(QPainter *paint){
    //数据准备
    double zoomX=this->data->zoomPerX;
    double zoomY=this->data->zoomPerY;
    int x=820*zoomX;
    int y=430*zoomY;
    int width=120*zoomX;
    int height=60*zoomY;
    int lineStartX=x+width-40*zoomX;

    //主体描绘
    paint->setBrush(bodyBrush);
    paint->setPen(bodyPen);
    paint->drawRect(x,y,width,height);
    //paint->drawRoundedRect(x,y,width,height,10,10);

    //信号源，说明符号描绘
    paint->setPen(QColor(desWordColor));
    paint->drawText(x,y-5*zoomY,"INPUT");

    paint->setPen(signalPen);
    //line signal sw-bus
    paint->drawLine(lineStartX,y,lineStartX,y-20*zoomY);


    //sw选中
    if(this->data->statu_swb==true){
        //总线更新
        this->paintBusLine(true,paint);
        paint->setPen(chooseSignalPen);
        paint->drawText(lineStartX+5*zoomX,y-5*zoomY,"SW-B");
        paint->setPen(chooseBusPen);
    }else{
        paint->setPen(signalPen);
        paint->drawText(lineStartX+5*zoomX,y-5*zoomY,"SW-B");
        paint->setPen(busPen);
    }
    paint->drawLine(x+width/2,y,x+width/2,MainWindow::height()/2);

    //数据显示
    paint->setPen(QColor(dataColor));
    dataDTransH(this->data->swiInputData,this->data->tempString);
    paint->drawText(x+width/2,y+height/2,QString::fromStdString(this->data->tempString)+"H");
}

//输出
void MainWindow::paintOutput(QPainter *paint){
    //数据准备
    double zoomX=this->data->zoomPerX;
    double zoomY=this->data->zoomPerY;
    int x=820*zoomX;
    int y=250*zoomY;
    int width=120*zoomX;
    int height=60*zoomY;
    int lineStartX=x+width-40*zoomX;

    bool flag=false;

    //主体描绘
    paint->setBrush(bodyBrush);
    paint->setPen(bodyPen);
    paint->drawRect(x,y,width,height);
    //paint->drawRoundedRect(x,y,width,height,10,10);

    //信号源，说明符号描绘
    paint->setPen(QColor(desWordColor));
    paint->drawText(x,y-5*zoomY,"OUTPUT");

    paint->setPen(signalPen);
    //line signal led-bus
    paint->drawLine(lineStartX,y+height,lineStartX,y+height+20*zoomY);
    //line signal W/R
    paint->drawLine(x+15*zoomX,y+height,x+15*zoomX,y+height+20*zoomY);

    //led具有写信号
    if(this->data->signal_we==WRITE){
        paint->setPen(chooseSignalPen);
        flag=true;
    }else{
        paint->setPen(signalPen);
    }
    paint->drawText(x+15*zoomX,y+height+20*zoomY,"W/R");

    //led选中
    if(this->data->statu_ldled==true){
        paint->setPen(chooseSignalPen);
    }else{
        paint->setPen(signalPen);
    }
    paint->drawText(lineStartX+5*zoomX,y+height+20*zoomY,"LED-B");

    if(flag && this->data->statu_ldled){
        paint->setPen(chooseBusPen);
    }else{
        paint->setPen(busPen);
    }
    //line bus->led
    paint->drawLine(x+width/2,y+height,x+width/2,MainWindow::height()/2);

    //数据显示
    if(this->data->statu_ldled){
        paint->setPen(QColor(dataColor));
        paint->drawText(x+width/2,y+height/2,QString::fromStdString(this->data->busData)+"H");
    }
}

//信号源
void MainWindow::paintSignal(QPainter *paint){
    //数据准备
    double zoomX=this->data->zoomPerX;
    double zoomY=this->data->zoomPerY;
    int x=750*zoomX;
    int y=600*zoomY;
    int rad=20*zoomX;

//绘制CY
    if(this->data->signal_cy==true){
        paint->setPen(chooseSignalPen);
        paint->setBrush(QColor(223, 80, 80));
    }else{
        paint->setPen(signalPen);
        paint->setBrush(QColor(0, 128, 0));
    }
    paint->drawChord(x,y,rad,rad,0,360*16);
    paint->drawText(x,y-10*zoomY,"CY");

//绘制ZI
    if(this->data->signal_zi==true){
        paint->setPen(chooseSignalPen);
        paint->setBrush(QColor(223, 80, 80));
    }else{
        paint->setPen(signalPen);
        paint->setBrush(QColor(0, 128, 0));
    }
    paint->drawChord(x+4*rad,y,rad,rad,0,360*16);
    paint->drawText(x+4*rad,y-10*zoomY,"ZI");
}


//------------------------------------------主界面按钮实现-----------------------------
//总清
void MainWindow::on_AR_BUT_clicked()
{
    this->data->pc=0;
    this->repaint();
}

//选择(自动|手动)运行
void MainWindow::on_autoRun_clicked()
{
    if(this->ui->autoRun->isChecked()==true){
        this->statusBarLable->setText("<div>自动运行|微程序文件未加载</div>");
        //auto run
        this->ui->switchGroup->setEnabled(false);
        this->ui->microAdressSetGroup->setEnabled(true);
        //恢复各部件的连接状态，在自动运行的状态下必须部件全部加载
        this->ui->microControlAcess->setChecked(true);
        this->ui->RAMAcess->setChecked(true);
        this->ui->a299Acess->setChecked(true);
        this->ui->ALUAcess->setChecked(true);
        this->ui->registerAcess->setChecked(true);
        on_microControlAcess_triggered();
        on_ALUAcess_triggered();
        on_RAMAcess_triggered();
        on_registerAcess_triggered();
        on_a299Acess_triggered();
        //取消菜单可选
        this->ui->OMcomponentAccess->setEnabled(false);
        this->ui->functionInputGroup->setEnabled(false);

        //开始微地址
        dataDTransH(this->data->startMroAd,this->data->tempString);
        this->ui->startMircoADInput->setText(QString::fromStdString(this->data->tempString));

        //KD7-KD1 开关数据
        dataDTransH(this->data->swiInputData,this->data->tempString);
        this->ui->swiInput->setText(QString::fromStdString(this->data->tempString));

        //S3-S0 M CN 功能开关设置
        this->ui->functionInput->setText("000000");

    }else{
        if(!this->data->reSet()) QMessageBox::information(this,"Error","数据初始化错误!");
        this->statusBarLable->setText("<div>手动运行</div>");
        this->ui->switchGroup->setEnabled(true);
        this->ui->microAdressSetGroup->setEnabled(false);
        this->ui->OMcomponentAccess->setEnabled(true);
        this->ui->functionInputGroup->setEnabled(true);
    }
    this->repaint();
}

//微指令信号处理
void MainWindow::signalPro(_data* data){
    data->reSetSig();
    if (_b3 == 0 && _b2 == 0 && _b1 == 0) {//内部输出设备不存在
        if (_B1 == 0 && _B0 == 0) {//SW
            data->statu_swb=true;
        }else if(_B1==0 && _B0==1){//RAM
            data->signal_ce=true;
        }
    }
    else if (_b3 == 0 && _b2 == 0 && _b1 == 1) {//RS-B
        switch ((data->ir%8)/4){
        case 0:{
            data->statu_r0b=true;
            break;
        }
        case 1:{
            data->statu_r1b=true;
            break;
        }
        case 2:{
            data->statu_r2b=true;
            break;
        }
        }
    }
    else if (_b3 == 0 && _b2 == 1 && _b1 == 0) {//RD-B
        switch ((data->ir % 4)){
        case 0:{
            data->statu_r0b=true;
            break;
        }
        case 1:{
            data->statu_r1b=true;
            break;
        }
        case 2:{
            data->statu_r2b=true;
            break;
        }
        }
    }
    else if (_b3 == 0 && _b2 == 1 && _b1 == 1) {//RI-B(选R2）
       data->statu_r2b=true;
    }
    else if (_b3 == 1 && _b2 == 0 && _b1 == 0) {//299-B
        data->statu_299b=true;
    }
    else if (_b3 == 1 && _b2 == 0 && _b1 == 1) {//ALU-B
        data->statu_alub=true;
    }
    else if (_b3 == 1 && _b2 == 1 && _b1 == 0) {//PC-B
        data->statu_pcb=true;
    }

    //输入部件运行
    if (_a3 == 0 && _a2 == 0 && _a1 == 0) {//内部输入设备不选中
        if (_B1 == 1 && _B0 == 0) {//LED
            data->statu_ldled=true;
        }else if(_B1==0 && _B0==1){//RAM
            data->signal_ce=true;
        }else {
            if (_s1 == -1 && _s0 == 1) {//299装数
                data->statu_ld299=true;
            }
        }
    }
    else if (_a3 == 0 && _a2 == 0 && _a1 == 1) {//RiIN
        switch ((data->ir % 4)){
        case 0:{
            data->statu_ldr0=true;
            break;
        }
        case 1:{
            data->statu_ldr1=true;
            break;
        }
        case 2:{
            data->statu_ldr2=true;
            break;
        }
        }
    }
    else if (_a3 == 0 && _a2 == 1 && _a1 == 0) {//DR1
        data->statu_lddr1=true;
    }
    else if (_a3 == 0 && _a2 == 1 && _a1 == 1) {//DR2
        data->statu_lddr2=true;
    }
    else if (_a3 == 1 && _a2 == 0 && _a1 == 0) {//LDIR
        data->statu_ldir=true;
    }
    else if (_a3 == 1 && _a2 == 0 && _a1 == 1) {//LDAD(PC)
        data->statu_ldad=true;
    }
    else if (_a3 == 1 && _a2 == 1 && _a1 == 0) {//LDAR
        data->statu_ldar=true;
    }
    else if (_a3 == 1 && _a2 == 1 && _a1 == 1) {//NONE
        if (_s1 == -1 && _s0 == 1) {//299装数
            data->statu_ld299=true;
        }
    }
    data->signal_we=_we;
    if (_c3 == 1 && _c2 == 0 && _c1 == 1) {//AR
        data->signal_ar=true;
    }
    else if (_c3 == 1 && _c2 == 1 && _c1 == 0) {//LDPC
        data->statu_ldpc=true;
    }

}

//单步运行，Contral 部件实现
void MainWindow::on_runInMicroCmd_clicked()
{
    //微地址2进制显示
    //"<div> S3 S2 S1 S0 M Cn WE B<sub>1</sub> B<sub>0</sub>  A   B    C    U5~U0 "

    dataDTransH(this->data->mroAddress,this->data->tempString);
    QString a="<strong>$M"+QString::fromStdString(this->data->tempString)+"</strong> | "+QString::number(_s3)+"   "+QString::number(_s2)+"   "+QString::number(_s1)+"   "+QString::number(_s0)+"   "\
                +QString::number(_m)+"   "+QString::number(_cn)+"   "+QString::number(_we)+" | "\
                +QString::number(_B1)+"   "+QString::number(_B0)+"  | "\
                +QString::number(_a3)+"   "+QString::number(_a2)+"   "+QString::number(_a1)+"  | "\
                +QString::number(_b3)+"   "+QString::number(_b2)+"   "+QString::number(_b1)+"  | "\
                +QString::number(_c3)+"   "+QString::number(_c2)+"   "+QString::number(_c1)+"  | "\
                +QString::number(_u6)+"   " +QString::number(_u5)+"   " +QString::number(_u4)+"   "\
                +QString::number(_u3)+"   " +QString::number(_u2)+"   " +QString::number(_u1)+" | ";

    //信号处理
    this->signalPro(this->data);

    if (_b3 == 0 && _b2 == 0 && _b1 == 0) {//内部输出设备不存在
        if (_B1 == 0 && _B0 == 1 && _we == 0) {//RAM
            a+="  RAM\t---->";
            RAM(this->data);
        }
        else if (_B1 == 0 && _B0 == 0) {//SW
            a+=" SW\t---->";
            SW(this->data);
        }
        else {
           a+="None\t---->";
        }
    }
    else if (_b3 == 0 && _b2 == 0 && _b1 == 1) {//RS-B
       if(this->data->statu_ldr0==true){
           a+="R0\t---->";
       }else if(this->data->statu_ldr1==true){
           a+="R1\t---->";
       }else if(this->data->statu_ldr2==true){
           a+="R2\t---->";
       }
       RIOut(this->data);
    }
    else if (_b3 == 0 && _b2 == 1 && _b1 == 0) {//RD-B

        if(this->data->statu_ldr0==true){
            a+="R0\t---->";
        }else if(this->data->statu_ldr1==true){
            a+="R1\t---->";
        }else if(this->data->statu_ldr2==true){
            a+="R2\t---->";
        }
        RIOut(this->data);
    }
    else if (_b3 == 0 && _b2 == 1 && _b1 == 1) {//RI-B(选R2）
        a+="R2\t---->";
        RIOut(this->data);
    }
    else if (_b3 == 1 && _b2 == 0 && _b1 == 0) {//299-B
        a+="299\t---->";
        _299(this->data);
    }
    else if (_b3 == 1 && _b2 == 0 && _b1 == 1) {//ALU-B
        if(this->data->statu_alub==true){
            a+="Alu\t---->";
        }else{
            a+="None\t---->";
        }
        ALU(this->data);
    }
    else if (_b3 == 1 && _b2 == 1 && _b1 == 0) {//PC-B

        if (_c3 == 1 && _c2 == 1 && _c1 == 0) {
            a+="PC\t---->";
        }
        else {
            a+="None\t---->";
        }
         PC(this->data);
    }
    else if (_b3 == 1 && _b2 == 1 && _b1 == 1) {//NONE
        a+="None\t---->";
    }
    a+="(";
    a.append(this->data->busData[0]);
    a.append(this->data->busData[1]);
    a+=")\t---->";

    //输入部件运行
    if (_a3 == 0 && _a2 == 0 && _a1 == 0) {//内部输入设备不选中
        if (_B1 == 1 && _B0 == 0) {//LED
            if(this->data->signal_we==WRITE){
                a+="LED\t";

            }else{
                a+="None\t";
            }
            LED(this->data);
        }
        else if (_B1 == 0 && _B0 == 1) {//RAM
            a+="RAM";
            RAM(this->data);
        }
        else {
            if (_s1 == -1 && _s0 == 1) {//299装数
                a+="299\t";
                _299(this->data);
            }
            else {
                a+="None\t";
            }
        }
    }
    else if (_a3 == 0 && _a2 == 0 && _a1 == 1) {//RiIN
        if(this->data->statu_r0b==true){
            a+="R0\t";
        }else if(this->data->statu_r1b==true){
            a+="R1\t";
        }else if(this->data->statu_r2b==true){
            a+="R2\t";
        }
        RIIn(this->data);
    }
    else if (_a3 == 0 && _a2 == 1 && _a1 == 0) {//DR1
        a+="DR1\t";
        DR1(this->data);
    }
    else if (_a3 == 0 && _a2 == 1 && _a1 == 1) {//DR2
        a+="DR2\t";
        DR2(this->data);
    }
    else if (_a3 == 1 && _a2 == 0 && _a1 == 0) {//LDIR
        a+="IR\t";
        IR(this->data);
    }
    else if (_a3 == 1 && _a2 == 0 && _a1 == 1) {//LDAD(PC)
        if (_c3 == 1 && _c2 == 1 && _c1 == 0) {
            PC(this->data);
            a+="PC\t";
        }
        else {
            a+="None\t";
        }
    }
    else if (_a3 == 1 && _a2 == 1 && _a1 == 0) {//LDAR
        a+="AR\t";
        AR(this->data);
    }
    else if (_a3 == 1 && _a2 == 1 && _a1 == 1) {//NONE
        if (_s1 == -1 && _s0 == 1) {//299装数
            a+="299\t";
            _299(this->data);
        }
        else {
            a+="None\t";
        }
    }

    //跳转
    if (_c3 == 0 && _c2 == 0 && _c1 == 0) {//顺序执行
        a+="顺序执行";
        this->data->mroAddress=dataBTransD(_u6, _u5, _u4, _u3, _u2, _u1);
    }
    else if (_c3 == 0 && _c2 == 0 && _c1 == 1) {//P(1)
        this->data->mroAddress=dataBTransD(_u6, _u5, _u4, _u3, _u2, _u1);
        P1(this->data);
        a+="P(1)";
    }
    else if (_c3 == 0 && _c2 == 1 && _c1 == 0) {//P(2)
        this->data->mroAddress=dataBTransD(_u6, _u5, _u4, _u3, _u2, _u1);
        P2(this->data);
        a+="p(2)";
    }
    else if (_c3 == 0 && _c2 == 1 && _c1 == 1) {//P(3)
        this->data->mroAddress=dataBTransD(_u6, _u5, _u4, _u3, _u2, _u1);
        if (P3(this->data) == true) {//跳转
            a+="P(3)[True]";
        }else{
            a+="P(3)[False]";
        }
    }
    else if (_c3 == 1 && _c2 == 0 && _c1 == 0) {//P(4)
        a+="P(4)[";
        a.append((char)(this->data->signal_swc+'0'));
        a.append((char)(this->data->signal_swa+'0'));
        a.append(']');
        P4(this->data);
    }
    else if (_c3 == 1 && _c2 == 0 && _c1 == 1) {//AR
        a+="顺序执行";
        a+="AR[True]";
        this->data->mroAddress=dataBTransD(_u6, _u5, _u4, _u3, _u2, _u1);
    }
    else if (_c3 == 1 && _c2 == 1 && _c1 == 0) {//LDPC
        a+="顺序执行";
        this->data->mroAddress=dataBTransD(_u6, _u5, _u4, _u3, _u2, _u1);
        if (_b3 == 1 && _b2 == 1 && _b1 == 0) {
            if(this->data->statu_pcb==false){
                PC(this->data);
                a+="PC+1";
            }
        }
    }
    else if (_c3 == 1 && _c2 == 1 && _c1 == 1) {//NONE
        a+="None";
    }
    dataDTransH(this->data->mroAddress,this->data->tempString);
    a+=" 下一微地址:["+QString::fromStdString(this->data->tempString)+']';
    this->repaint();
    this->statusBarLable->setText(a);
    this->statusBarLable->setTextFormat(Qt::RichText);
}

//避免文件不存在
bool MainWindow::isFileLoad(){
    for(int i=0;i<100;i++){
        for(int j=1;j<24;++j){
            if(this->data->rom[i][j])
                return true;
        }
    }
    return false;
}

//单步指令运行，在微地址变为预设的开始停止
void MainWindow::on_runInCmd_clicked()
{
    if(this->isFileLoad()==false){
        switch (QMessageBox::information(this,tr("警告"),tr("微程序文件不存在，继续运行会造成不可预知的错误，是否继续运行？"),QMessageBox::Ok,QMessageBox::Cancel)){
        case QMessageBox::Ok:{

            break;
        }
        case QMessageBox::Cancel:{
            return;
        }
        }

    }
    do{
        on_runInMicroCmd_clicked();
        if(this->data->pc==256){
            QMessageBox::warning(this,tr("RAM访问越界"),tr("RAM内存文件已达末尾"));
            break;
        }else{
            QEventLoop eventloop;
            QTimer::singleShot(1000, &eventloop, SLOT(quit()));
            eventloop.exec();
        }
    }while(this->data->mroAddress!=this->data->startMroAd);
}

//手动运行，可直接复用单步运行函数
void MainWindow::on_T4pulse_clicked()
{
    //要先处理完所有的数据，然后将该上总线的数据上总线，但是ar等有存储功能的部件，数据应该交换完再绘图
    //总线数据每次清0
    //pc++等逻辑必须处理完再绘图
    //299的信号更新别忘了,尤其是299作为输入
    ///ram、SW、299、alu、pc
    ///ram,led,299,dr1,dr2,IR,PC,AR,

    bool flag=false;//用于监测是否已经有了输出
    //输出检测
    if(this->data->Acess_RAM && this->data->signal_we==READ && this->data->signal_ce){
        flag=true;
        RAM(this->data);
    }
    if(this->data->statu_swb){
        if(flag) statusBar()->showMessage("[Error]输出冲突",4);
        flag=true;
        SW(this->data);
    }
    if(this->data->Acess_299 && this->data->statu_299b){
        if(flag) statusBar()->showMessage("[Error]输出冲突",4);
        flag=true;
        _299(this->data);
    }
    if(this->data->Acess_ALU && this->data->statu_alub){
        if(flag) statusBar()->showMessage("[Error]输出冲突",4);
        flag=true;
        ALU(this->data);
    }
    if(this->data->statu_pcb){
        if(flag) statusBar()->showMessage("[Error]输出冲突",4);
        PC(this->data);
    }

    //输入检测，必备的在下侧，不能删去避免重复执行
    if(this->data->Acess_RAM && this->data->signal_we==WRITE && this->data->signal_ce){
        RAM(this->data);
    }
    if(this->data->statu_ldled && this->data->signal_we==WRITE){
        LED(this->data);
    }
    if(this->data->Acess_299 && this->data->statu_ld299){
        _299(this->data);
    }
    DR1(this->data);
    DR2(this->data);
    IR(this->data);
    PC(this->data);
    AR(this->data);
    //绘图
    this->repaint();

    //总线数据清0
    this->data->busData="00";
}

//swc
void MainWindow::on_SWC_clicked()
{
    if(this->ui->SWC->isChecked()==true){
        this->data->signal_swc=true;
    }else{
        this->data->signal_swc=false;
    }
}

//swa
void MainWindow::on_SWA_clicked()
{
    if(this->ui->SWA->isChecked()==true){
        this->data->signal_swa=true;
    }else{
        this->data->signal_swa=false;
    }
}


//------------------------手动开关设置-------------------
//LDAR
void MainWindow::on_swi_LDAR_clicked()
{
    this->data->statu_ldar=this->ui->swi_LDAR->isChecked();
}

//LDDR1
void MainWindow::on_swi_LDDR1_clicked()
{
    this->data->statu_lddr1=this->ui->swi_LDDR1->isChecked();
}

//LLDR2
void MainWindow::on_swi_LDDR2_clicked()
{
    this->data->statu_lddr2=this->ui->swi_LDDR2->isChecked();
}

//LDAD
void MainWindow::on_swi_LDAD_clicked()
{
    this->data->statu_ldled=this->data->statu_ldad=this->ui->swi_LDAD->isChecked();
}

//LDPC
void MainWindow::on_swi_LDPC_clicked()
{
    this->data->statu_ldpc=this->ui->swi_LDPC->isChecked();
}

//PCB
void MainWindow::on_swi_PCB_clicked()
{
    this->data->statu_pcb=this->ui->swi_PCB->isChecked();
}

//ALUB
void MainWindow::on_swi_ALUB_clicked()
{
    this->data->statu_alub=this->ui->swi_ALUB->isChecked();
}

//299B
void MainWindow::on_swi_299B_clicked()
{
    this->data->statu_299b=this->ui->swi_299B->isChecked();
}

//SWB
void MainWindow::on_swi_SWB_clicked()
{
    this->data->statu_swb=this->ui->swi_SWB->isChecked();
}

//WE
void MainWindow::on_swi_WE_clicked()
{
    this->data->signal_we=this->ui->swi_WE->isChecked();
}

//AR
void MainWindow::on_swi_AR_clicked()
{
    this->data->signal_ar=this->ui->swi_AR->isChecked();
}

//CE
void MainWindow::on_swi_CE_clicked()
{
     this->data->signal_ce=this->ui->swi_CE->isChecked();
}

//微地址输入框
void MainWindow::on_startMircoADInput_editingFinished()
{
    if(this->ui->startMircoADInput->text().length()==2){
        this->data->tempString=this->ui->startMircoADInput->text().toStdString();
        this->data->startMroAd=dataHTransD( this->data->tempString[0], this->data->tempString[1]);
    }else if(this->ui->startMircoADInput->text().length()==1){
        this->data->tempString=this->ui->startMircoADInput->text().toStdString();
        this->data->startMroAd=dataHTransD('0', this->data->tempString[0]);
        dataDTransH(this->data->startMroAd,this->data->tempString);
        this->ui->startMircoADInput->setText(QString::fromStdString(this->data->tempString));
    }else{
        this->on_startMircoADInput_inputRejected();
    }
}

//微地址输入 输入不符合规范的数据，恢复原来的数据
void MainWindow::on_startMircoADInput_inputRejected()
{
    dataDTransH(this->data->startMroAd,this->data->tempString);
    this->ui->startMircoADInput->setText(QString::fromStdString(this->data->tempString));
}

//开关输入框
void MainWindow::on_swiInput_editingFinished()
{
    if(this->ui->swiInput->text().length()==2){
        this->data->tempString=this->ui->swiInput->text().toStdString();
        this->data->swiInputData=dataHTransD( this->data->tempString[0], this->data->tempString[1]);
        this->repaint();
    }else if(this->ui->swiInput->text().length()==1){
        this->data->tempString=this->ui->swiInput->text().toStdString();
        this->data->swiInputData=dataHTransD('0', this->data->tempString[0]);
        dataDTransH(this->data->swiInputData,this->data->tempString);
        this->ui->swiInput->setText(QString::fromStdString(this->data->tempString));
        this->repaint();
    }else{
       this->on_swiInput_inputRejected();
    }
}

//数据开关输入不符合规范的数据，恢复原来的数据
void MainWindow::on_swiInput_inputRejected()
{
    dataDTransH(this->data->swiInputData,this->data->tempString);
    this->ui->swiInput->setText(QString::fromStdString(this->data->tempString));
}

//功能开关输入
void MainWindow::on_functionInput_editingFinished()
{
    if(this->ui->functionInput->text().length()==6){
        this->data->tempString=this->ui->functionInput->text().toStdString();
        _s3=this->data->tempString[0]-'0';
        _s2=this->data->tempString[1]-'0';
        _s1=this->data->tempString[2]-'0';
        _s0=this->data->tempString[3]-'0';
        _m=this->data->tempString[4]-'0';
        _cn=this->data->tempString[5]-'0';
        this->data->tempString="00";
        //299装载信号更新
        this->data->statu_ld299=_s0 && _s1;
    }else{
        this->on_functionInput_inputRejected();
    }
}

//功能开关 输入不符合规范的数据，恢复原来的数据
void MainWindow::on_functionInput_inputRejected()
{
    this->data->tempString=_s3+_s2+_s1+_s0+_m+_cn;
    this->ui->functionInput->setText(QString::fromStdString(this->data->tempString));
}



