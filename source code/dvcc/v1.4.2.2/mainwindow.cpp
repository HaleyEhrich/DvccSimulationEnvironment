#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose,true);

    //Set logo info
    QFont ft;
    ft.setPointSize(10);
    ft.setBold(true);
    QLabel* statusBarLable=new QLabel(this);
    statusBarLable->setTextFormat(Qt::RichText);
    statusBarLable->setFont(ft);
    statusBarLable->setText("<div>produced by HE STUDIO</div>");
    statusBar()->addPermanentWidget(statusBarLable);//永久信息窗口 - 不会被一般消息覆盖

    this->loadEnviroMent();

    this->initGraphics();

    this->setTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/// \brief Load env(Such exists style file and exsits micro code set and settings)
/// \param envPath working dir
/// \return when load sucs return true or return false
bool MainWindow::loadEnviroMent(QString envPath)
{
    envPath+="/resource/file_resource";

    this->config_set.loadConfig(envPath+"/configuration.ini");

    this->ram_row_size=this->config_set.ramRow;
    this->ram_col_size=this->config_set.ramCol/4;//4 bits as one ram col
    this->rom_row_size=this->config_set.romRow;
    this->rom_col_size=this->config_set.romCol;

    //stylesheet
    QString conThemePath=envPath+"/theme/"+this->config_set.themeName+".qss";
    QFile conThemeFile(conThemePath);
    conThemeFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream conThemeStream(&conThemeFile);
    QString styleSheetReadIn=conThemeStream.readAll();
    this->setStyleSheet(styleSheetReadIn);
    conThemeFile.close();
    statusBar()->showMessage(tr("主题加载成功"),1000);

    //font
    this->setFont(this->config_set.font);
    statusBar()->showMessage(tr("字体加载成功"),1000);

    if(!this->config_set.openDesigner){
        this->ui->pm_designer->setVisible(false);
        statusBar()->showMessage(tr("设计器关闭"),1000);
    }


    //判断路径是否存在
    QDir dir(envPath+"/presetcode");
    if(dir.exists()){
        //查看路径中后缀为.cfg格式的文件
        QStringList filters;
        filters<<QString("*.dvc");
        dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
        dir.setNameFilters(filters);  //设置文件名称过滤器，只为filters格式
        int file_count=dir.count();
        if(file_count>0){
            for(int i=0; i<file_count; i++)
            {
                this->ui->qs_preset_combobox->addItem(dir[i],envPath+"/presetcode/"+dir[i]);
            }
        }
    }
    statusBar()->showMessage(tr("预设代码扫描完成"),1000);

    //阴影效果
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(QColor(43, 43, 43));
    shadow_effect->setBlurRadius(8);
    this->ui->circuit_diagram->setGraphicsEffect(shadow_effect);

    QGraphicsDropShadowEffect *shadow_effect1 = new QGraphicsDropShadowEffect(this);
    shadow_effect1->setOffset(0, 0);
    shadow_effect1->setColor(QColor(43, 43, 43));
    shadow_effect1->setBlurRadius(8);
    this->ui->tw_quick_set->setGraphicsEffect(shadow_effect1);

    QGraphicsDropShadowEffect *shadow_effect2 = new QGraphicsDropShadowEffect(this);
    shadow_effect2->setOffset(0, 0);
    shadow_effect2->setColor(QColor(43, 43, 43));
    shadow_effect2->setBlurRadius(8);
    this->ui->micro_code_info_table->setGraphicsEffect(shadow_effect2);

    this->ui->qs_auto_run_set_btn_group->hide();
    this->ui->alu_cmd_input_box->hide();

    this->ui->micro_code_info_table->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    this->ui->micro_code_info_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui->micro_code_info_table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    this->data.setPara(this->ram_row_size,this->ram_col_size,this->rom_row_size,this->rom_col_size);
    this->ram_checker=new RAMCheck(nullptr,&this->data);
    this->rom_checker=new ROMCheck(nullptr,&this->data);
    this->log_checker=new LogPannel(nullptr);

    return true;
}

bool MainWindow::initGraphics()
{
    scene=new QGraphicsScene();   // 定义一个场景，设置背景色为红色
    scene->setSceneRect(QRectF(-200,-200,400,400));

    //Ram
    ram=new RamQGItem(&this->data);
    scene->addItem(ram);

    //299b
    shifter=new Shifter299QGItem(&this->data);
    scene->addItem(shifter);

    //alu
    alu=new ALUQGItem(&this->data);
    scene->addItem(alu);

    //dr1
    dr1=new Dr1QGItem(&this->data);
    scene->addItem(dr1);

    //dr2
    dr2=new Dr2QGItem(&this->data);
    scene->addItem(dr2);

    //pc
    pc=new PCQGItem(&this->data);
    scene->addItem(pc);

    //AR
    ar=new ARQGItem(&this->data);
    scene->addItem(ar);

    //output
    led=new OutputQGItem(&this->data);
    scene->addItem(led);

    //Input
    switcher=new InputQGItem(&this->data);
    scene->addItem(switcher);

    //Micro con
    microCon=new MicroConQGItem(&this->data);
    scene->addItem(microCon);

    //R0
    r0=new R0QGItem(&this->data);
    scene->addItem(r0);

    //R1
    r1=new R1QGItem(&this->data);
    scene->addItem(r1);

    //R2
    r2=new R2QGItem(&this->data);
    scene->addItem(r2);

    //Ir
    ir=new IrQGItem(&this->data);
    scene->addItem(ir);

    //signals
    signalsLed=new SignalsQGItem(&this->data);
    scene->addItem(signalsLed);


    //BUS draw
    busLine=new QGraphicsLineItem();
    busLine->setLine(-1000*this->data.zoomXPer,0,1000*this->data.zoomXPer,0);
    busLine->setPen(linePen);
    scene->addItem(busLine);

    this->ui->circuit_diagram->setRenderHint(QPainter::Antialiasing);

//    busText=new QGraphicsSimpleTextItem();
//    busText->setPos(0,0);
//    busText->setPen(QPen(Qt::black));
//    busText->setFont(bigDataTextFont);
//    busText->setText(QString("%1").arg(this->data.data_bus,2,QLatin1Char('0')));


    this->ui->circuit_diagram->setScene(scene);
    this->ui->circuit_diagram->show();
    return true;
}

/// Load a line of microcode
/// \return Return 0 Load failed
/// \return Return 1 Load ram
/// \return Return 2 Load rom
/// \return Return 3 Address out of range
inline int MainWindow::loadMCLine(QString &mcLine)
{
    if(mcLine.length()>=2){
        int base=0;
        int address=0;

        if (mcLine[1] == 'P') {//程序区
            if(ramLineNewPattern.match(mcLine).hasMatch()){//new pattern
                //$P|0000|12
                //01 2345 67
                address=mcLine.mid(2,4).toInt(nullptr,16);
                base=2;
            }else if(ramLineOldPattern.match(mcLine).hasMatch()){
                //$P|00|12
                //01 23 45
                address=mcLine.mid(2,2).toInt(nullptr,16);
                base=0;
            }else{
                return 0;
            }

            if(address >= this->data.ram_row_size){
                return 3;
            }

            this->data.data_ram[address][0] = mcLine[4+base];
            this->data.data_ram[address][1] = mcLine[5+base];
            return 1;
        }
        else if (mcLine[1] == 'M') {//微代码区域
            if(romLineNewPattern.match(mcLine).hasMatch()){
                //$M|0000|000000
                //01 2345 6789AB
                address=mcLine.mid(2,4).toInt(nullptr,16);
                base=2;
            }else if(romLineOldPattern.match(mcLine).hasMatch()){
                //$M|00|000000
                //01 23 456789
                address=mcLine.mid(2,2).toInt(nullptr,16);
                base=0;
            }else{
                return 0;
            }

            if(address >= this->data.ram_row_size){
                return 3;
            }

            int trans=hexcToDec(mcLine[8+base]);
            this->data.data_rom[address][ms3] = trans /8;
            this->data.data_rom[address][ms2] = trans % 8 / 4;
            this->data.data_rom[address][ms1] = trans % 8 % 4/2;
            this->data.data_rom[address][ms0] = trans % 8 % 4 % 2;
            trans=hexcToDec(mcLine[9+base]);
            this->data.data_rom[address][mm] = trans /8;
            this->data.data_rom[address][mcn] = trans % 8 / 4;
            this->data.data_rom[address][mwe] = trans % 8 % 4/2;
            this->data.data_rom[address][mB1] = trans % 8 % 4 % 2;
            trans=hexcToDec(mcLine[6+base]);
            this->data.data_rom[address][mB0] = trans /8;
            this->data.data_rom[address][ma3] = trans % 8 / 4;
            this->data.data_rom[address][ma2] = trans % 8 % 4/2;
            this->data.data_rom[address][ma1] = trans % 8 % 4 % 2;
            trans=hexcToDec(mcLine[7+base]);
            this->data.data_rom[address][mb3] = trans /8;
            this->data.data_rom[address][mb2] = trans % 8 / 4;
            this->data.data_rom[address][mb1] = trans % 8 % 4/2;
            this->data.data_rom[address][mc3] = trans % 8 % 4 % 2;
            trans=hexcToDec(mcLine[4+base]);
            this->data.data_rom[address][mc2] = trans /8;
            this->data.data_rom[address][mc1] = trans % 8 / 4;
            this->data.data_rom[address][mu6] = trans % 8 % 4/2;
            this->data.data_rom[address][mu5] = trans % 8 % 4 % 2;
            trans=hexcToDec(mcLine[5+base]);
            this->data.data_rom[address][mu4] = trans /8;
            this->data.data_rom[address][mu3] = trans % 8 / 4;
            this->data.data_rom[address][mu2] = trans % 8 % 4/2;
            this->data.data_rom[address][mu1] = trans % 8 % 4 % 2;
            return 2;
        }
    }
    return 0;
}

/// \brief 重置数据集，但是不会重新生成ram、rom内存
void MainWindow::resetSystem(bool freshRaom)
{

    //重置信号\ram\rom数据
    if(freshRaom){
        this->data.resetRaomData();
    }

    this->data.reSetSig();
    this->data.signal_zi=false;
    this->data.signal_cy=false;

    //刷新ram、rom面板
    this->ram_checker->freshData();
    this->rom_checker->freshData();

    //设置表格
    this->setTable();

    this->ui->circuit_diagram->viewport()->update();
}

void MainWindow::setTable()
{
    QString res;
    //No
    this->ui->micro_code_info_table->setItem(0,0,new QTableWidgetItem(QString("%1").arg(this->data.data_mroAddress,4,16,QLatin1Char('0'))));
    //Hexc
    this->rom_checker->getMCInHex(this->data.data_mroAddress,res);
    this->ui->micro_code_info_table->setItem(0,1,new QTableWidgetItem(res));

    //S3-0
    this->rom_checker->getS3S0(this->data.data_mroAddress,res);
    this->ui->micro_code_info_table->setItem(0,2,new QTableWidgetItem(res));

    //M
    this->rom_checker->getM(this->data.data_mroAddress,res);
    this->ui->micro_code_info_table->setItem(0,3,new QTableWidgetItem(res));

    //Cn
    this->rom_checker->getCn(this->data.data_mroAddress,res);
    this->ui->micro_code_info_table->setItem(0,4,new QTableWidgetItem(res));

    //WE
    this->rom_checker->getWe(this->data.data_mroAddress,res);
    this->ui->micro_code_info_table->setItem(0,5,new QTableWidgetItem(res));

    //B1B0
    this->rom_checker->getB1B0(this->data.data_mroAddress,res);
    this->ui->micro_code_info_table->setItem(0,6,new QTableWidgetItem(res));

    this->rom_checker->getA(this->data.data_mroAddress,res);
    this->ui->micro_code_info_table->setItem(0,7,new QTableWidgetItem(res));

    this->rom_checker->getB(this->data.data_mroAddress,res);
    this->ui->micro_code_info_table->setItem(0,8,new QTableWidgetItem(res));

    this->rom_checker->getC(this->data.data_mroAddress,res);
    this->ui->micro_code_info_table->setItem(0,9,new QTableWidgetItem(res));

    this->rom_checker->getNextMroAD(this->data.data_mroAddress,res);
    this->ui->micro_code_info_table->setItem(0,10,new QTableWidgetItem(res));

    //From
    this->rom_checker->getBStatu(this->data.data_mroAddress,res);
    if(res=="NONE"){
        this->rom_checker->getB1B0Statu(this->data.data_mroAddress,res);
        if(res=="Input" || (res=="RAM" && this->data.signal_we)){
            res="NONE";
        }
    }
    this->ui->micro_code_info_table->setItem(0,11,new QTableWidgetItem(res));

    //To
    this->rom_checker->getAStatu(this->data.data_mroAddress,res);
    if(res=="NONE"){
        this->rom_checker->getB1B0Statu(this->data.data_mroAddress,res);
        if(res=="Output"){
            res="LED";
        }
        if(res=="RAM" && this->data.signal_we==WRITE){
            res="RAM";
        }

//        if(res!="Output" || (res=="RAM" && this->data.signal_we==false)){
//            res="NONE";
//        }
    }
    this->ui->micro_code_info_table->setItem(0,12,new QTableWidgetItem(res));

    this->rom_checker->getCStatu(this->data.data_mroAddress,res);
    this->ui->micro_code_info_table->setItem(0,13,new QTableWidgetItem(res));

    //-----next mc info

    //No
    this->ui->micro_code_info_table->setItem(1,0,new QTableWidgetItem(QString("%1").arg(this->data.data_nextMroAddress,4,16,QLatin1Char('0'))));
    //Hexc
    this->rom_checker->getMCInHex(this->data.data_nextMroAddress,res);
    this->ui->micro_code_info_table->setItem(1,1,new QTableWidgetItem(res));

    //S3-0
    this->rom_checker->getS3S0(this->data.data_nextMroAddress,res);
    this->ui->micro_code_info_table->setItem(1,2,new QTableWidgetItem(res));

    //M
    this->rom_checker->getM(this->data.data_nextMroAddress,res);
    this->ui->micro_code_info_table->setItem(1,3,new QTableWidgetItem(res));

    //Cn
    this->rom_checker->getCn(this->data.data_nextMroAddress,res);
    this->ui->micro_code_info_table->setItem(1,4,new QTableWidgetItem(res));

    //WE
    this->rom_checker->getWe(this->data.data_nextMroAddress,res);
    this->ui->micro_code_info_table->setItem(1,5,new QTableWidgetItem(res));

    //B1B0
    this->rom_checker->getB1B0(this->data.data_nextMroAddress,res);
    this->ui->micro_code_info_table->setItem(1,6,new QTableWidgetItem(res));

    this->rom_checker->getA(this->data.data_nextMroAddress,res);
    this->ui->micro_code_info_table->setItem(1,7,new QTableWidgetItem(res));

    this->rom_checker->getB(this->data.data_nextMroAddress,res);
    this->ui->micro_code_info_table->setItem(1,8,new QTableWidgetItem(res));

    this->rom_checker->getC(this->data.data_nextMroAddress,res);
    this->ui->micro_code_info_table->setItem(1,9,new QTableWidgetItem(res));

    this->rom_checker->getNextMroAD(this->data.data_nextMroAddress,res);
    this->ui->micro_code_info_table->setItem(1,10,new QTableWidgetItem(res));


    //From
    this->rom_checker->getBStatu(this->data.data_nextMroAddress,res);
    if(res=="NONE"){
        this->rom_checker->getB1B0Statu(this->data.data_nextMroAddress,res);
        if(res=="Input" || (res=="RAM" && this->data.signal_we)){
            res="NONE";
        }
    }
    this->ui->micro_code_info_table->setItem(1,11,new QTableWidgetItem(res));

    //To
    this->rom_checker->getAStatu(this->data.data_nextMroAddress,res);
    if(res=="NONE"){
        this->rom_checker->getB1B0Statu(this->data.data_nextMroAddress,res);
        if(res=="Output" || (res=="RAM" && this->data.signal_we==false)){
            res="NONE";
        }
    }
    this->ui->micro_code_info_table->setItem(1,12,new QTableWidgetItem(res));

    this->rom_checker->getCStatu(this->data.data_nextMroAddress,res);
    this->ui->micro_code_info_table->setItem(1,13,new QTableWidgetItem(res));

    for(int row=this->ui->micro_code_info_table->rowCount()-1;row>=0;row--){
        for(int col=this->ui->micro_code_info_table->columnCount()-1;col>=0;col--){
            this->ui->micro_code_info_table->item(row,col)->setTextAlignment(Qt::AlignCenter);
        }
    }

}

void MainWindow::setSigBtn()
{
    this->ui->sig_299b_btn->setChecked(this->data.statu_299b);
    this->ui->sig_alub_btn->setChecked(this->data.statu_alub);
    this->ui->sig_ar_btn->setChecked(this->data.signal_ar);
    this->ui->sig_ce_btn->setChecked(this->data.signal_ce);
    this->ui->sig_ldad_btn->setChecked(this->data.statu_ldad);
    this->ui->sig_ldar_btn->setChecked(this->data.statu_ldar);
    this->ui->sig_lddr1_btn->setChecked(this->data.statu_lddr1);
    this->ui->sig_lddr2_btn->setChecked(this->data.statu_lddr2);
    this->ui->sig_ldpc_btn->setChecked(this->data.statu_ldpc);
    this->ui->sig_pcb_btn->setChecked(this->data.statu_pcb);
    this->ui->sig_swb_btn->setChecked(this->data.statu_swb);
    this->ui->sig_we->setChecked(this->data.signal_we);
}

/// \brief MainWindow::paintEvent
/// \param event
void MainWindow::paintEvent(QPaintEvent *event)
{
    //实时刷新电路图
    if(this->config_set.freshInRealTime){
        this->ui->circuit_diagram->viewport()->update();
    }

    QMainWindow::paintEvent(event);
}

/// \brief MainWindow::resizeEvent
/// \param event
void MainWindow::resizeEvent(QResizeEvent *event)
{
    this->data.zoomXPer= (double)event->size().width()/1400.0;
    this->data.zoomYPer= (double)event->size().height()/800.0;

    this->repaint();
    this->ui->circuit_diagram->repaint();

    QMainWindow::resizeEvent(event);
}

//---------------------------------文件菜单/File menu------------------------

///新建窗口
///Make a new empty window
void MainWindow::on_fm_new_win_triggered()
{
    QProcess process;
    process.startDetached(QDir::currentPath()+"\\DVCC.exe");
}

///Open code file
void MainWindow::on_fm_open_file_triggered()
{
    if(this->micro_code_file!=nullptr){
        int res=QMessageBox::information(this,tr("警告"),tr("已经打开一个微代码文件了，是否保存目前的文件？"),QMessageBox::Ok,QMessageBox::No);
        if(res==QMessageBox::Ok){
            this->on_fm_save_as_file_triggered();
        }else{
            this->data.resetRaomData();
        }
    }

    QString filePath=QFileDialog::getOpenFileName(this,
                                                  tr("打开文件"),
                                                  QDir::currentPath(),
                                                  "dvc(*.dvc);;txt(*.txt);;other(*.*)");
    if(filePath.size()==0){
        return;
    }

    statusBar()->showMessage(tr("程序文件:")+filePath,1000);

    filePath.replace("/","\\");

    this->micro_code_file=new QFile(filePath);
    this->micro_code_file->open(QIODevice::ReadWrite | QIODevice::Text);

retryOpen:
    if(this->micro_code_file->isOpen()==false){
        switch (QMessageBox::critical(this,tr("错误"),tr("文件打开失败!"),QMessageBox::Retry,QMessageBox::Cancel)){
        case QMessageBox::Retry:{
            goto retryOpen;
            break;
        }
        case QMessageBox::Cancel:{
            return;
        }
        }
    }else{
        QString line;
        int ramLine=0,romLine=0,outOfRange=0;
        while (this->micro_code_file->atEnd() == false) {
            line=this->micro_code_file->readLine();
            switch (this->loadMCLine(line)){
            case 0:{

                break;
            }
            case 1:{
                ramLine++;
                break;
            }
            case 2:{
                romLine++;
                break;
            }
            case 3:{
                outOfRange++;
                break;
            }
            }
        }
        QMessageBox::about(this,tr("完成"),
                           QString(tr("<h1>😶‍🌫️微代码文件载入成功。</h1>"
                                      "<ul><li>共载入<b>%1(D)</b>行Ram信息</li>"
                                      "<li>共载入<b>%2(D)</b>行Rom信息</li>"
                                      "<li>超范围<b>%3(D)</b>行</li></ul>"))
                           .arg(ramLine,4,10,QLatin1Char('0')).arg(romLine,4,10,QLatin1Char('0')).arg(outOfRange,4,10,QLatin1Char('0')));

        this->micro_code_file->close();
        this->resetSystem(false);

    }
}

///Paste code.
void MainWindow::on_fm_paste_code_triggered()
{
    QString text = QInputDialog::getMultiLineText(this,tr("输入微程序代码"),tr("黏贴于此处"));
    if (text.isEmpty())
    {
        QMessageBox::information(this,tr("警告"),tr("空内容，不会有任何内容被添加到内存"));
    }
    else
    {
        int ramLine=0,romLine=0,outOfRange=0;

        QString line;
        QStringList microCodeList=text.split("\n");

        for(int i=0;i<microCodeList.length();++i){
            line=microCodeList[i];

            switch (this->loadMCLine(line)){
            case 0:{

                break;
            }
            case 1:{
                ramLine++;
                break;
            }
            case 2:{
                romLine++;
                break;
            }
            case 3:{
                outOfRange++;
                break;
            }
            }

        }

        QMessageBox::about(this,tr("完成"),
                           QString(tr("<h1>😶‍🌫️hey,微代码黏贴成功。</h1>"
                                      "<ul><li>共读取了<b>%1(D)</b>行Ram信息</li>"
                                      "<li>共读取了<b>%2(D)</b>行Rom信息</li>"
                                      "<li>超范围<b>%3(D)</b>行</li></ul>"))
                           .arg(ramLine,4,10,QLatin1Char('0')).arg(romLine,4,10,QLatin1Char('0')).arg(outOfRange,4,10,QLatin1Char('0')));

        //刷新ram、rom面板
        this->ram_checker->freshData();
        this->rom_checker->freshData();
        //重置信号
        this->data.reSetSig();
        this->data.signal_zi=false;
        this->data.signal_cy=false;

        //设置表格
        this->setTable();

        this->ui->circuit_diagram->viewport()->update();
    }
}

///Save code to open file
void MainWindow::on_fm_save_file_triggered()
{
    if(this->micro_code_file==nullptr){
        int res=QMessageBox::critical(this,tr("错误"),tr("未加载微代码文件，是否选择文件保存"),QMessageBox::Ok,QMessageBox::No);
        if(res==QMessageBox::Ok){
            QString filePath=QFileDialog::getOpenFileName(this,
                                                          tr("打开文件"),
                                                          QDir::currentPath(),
                                                          "dvc(*.dvc);txt(*.txt);other(*.*)");
            if(filePath.size()==0){
                QMessageBox::information(this,tr("提示"),tr("未选择文件，文件将不被保存。"));
                return;
            }

            filePath.replace("/","\\");

            this->micro_code_file=new QFile(filePath);

        }else{
            statusBar()->showMessage(tr("不保存"),1500);
        }
    }

    if(this->micro_code_file!=nullptr){
        this->micro_code_file->open(QIODevice::WriteOnly | QIODevice::Truncate);

        QTextStream out(this->micro_code_file);

        QString dataOut="";
        out<<tr("\n//-------Ram程序区域-------\n");
        for(int i=0;i<this->data.ram_row_size;++i){
            if(this->data.data_ram[i][0]=='0'&&this->data.data_ram[i][1]=='0'){
                continue;
            }
            dataOut="$P"+QString("%1").arg(i,4,16,QLatin1Char('0'));
            dataOut.append(this->data.data_ram[i][0]);
            dataOut.append(this->data.data_ram[i][1]);
            dataOut.append('\n');
            out<<dataOut;
        }

        out<<'\n';

        out<<tr("//-------Rom程序区域-------\n");
        for(int i=0;i<this->data.rom_row_size;++i){
            this->rom_checker->getMCInHex(i,dataOut);
            //全零代表无需保存
            if(dataOut!="000000"){
                dataOut.insert(0,QString("$M%1").arg(i,4,16,QLatin1Char('0')));
                out<<dataOut<<"\n";
            }
        }
        out<<tr("//生成时间: ")<<QTime::currentTime().toString();
        out<<"\n";
        statusBar()->showMessage(tr("文件保存成功"),2);


        this->resetSystem(true);

        this->micro_code_file->close();
        delete this->micro_code_file;
        this->micro_code_file=nullptr;
    }else{

    }
}

///Save file to another file
void MainWindow::on_fm_save_as_file_triggered()
{
    QString filePath=QFileDialog::getExistingDirectory(this,
                                                       tr("选择保存位置"),
                                                       QDir::currentPath());
    if(filePath.isEmpty()){
        statusBar()->showMessage(tr("路径不存在，另存失败"),1500);
    }

    filePath+="/Stander_file_ave_"+QDateTime::currentDateTime().toString("yy-MM-dd_hh-mm-ss")+".txt";

retrySaveAs:
    QFile saveAsFile(filePath);
    saveAsFile.open(QIODevice::ReadWrite | QIODevice::Text);
    if(saveAsFile.isOpen()==false){
        switch (QMessageBox::critical(this,tr("错误"),tr("文件另存失败!"),QMessageBox::Retry,QMessageBox::Cancel)){
        case QMessageBox::Retry:{
            goto retrySaveAs;
            break;
        }
        case QMessageBox::Cancel:{
            return;
            break;
        }
        }
    }else{
        QTextStream outStream(&saveAsFile);
        QString dataOut;
        for(int i=0;i<128;++i){
            if(this->data.data_ram[i][0]=='0'&&this->data.data_ram[i][1]=='0'){
                continue;
            }
            dataOut="＄P"+QString("%1").arg(i,2,16,QLatin1Char('0'));
            dataOut.append(this->data.data_ram[i][0]);
            dataOut.append(this->data.data_ram[i][1]);
            dataOut.append('\n');
            outStream<<dataOut;
        }
        outStream<<'\n';
        for(int i=0;i<64;++i){
            this->rom_checker->getMCInHex(i,dataOut);
            //全零代表无需保存
            if(dataOut!="000000"){
                dataOut.insert(0,QString("＄M%1").arg(i,2,16,QLatin1Char('0')));
                outStream<<dataOut<<"\n";
            }
        }
        saveAsFile.close();
        statusBar()->showMessage(tr("文件另存成功")+filePath,2000);
    }
}

///Open ram and rom checker
void MainWindow::on_fm_checker_triggered()
{
    this->on_pm_ram_checker_triggered();
    this->on_pm_rom_checker_triggered();
}

///Open or close micro code infomation table
void MainWindow::on_rm_run_micro_set_triggered(bool checked)
{
    if(checked){
        this->ui->micro_code_info_table->show();
    }else{
        this->ui->micro_code_info_table->hide();
    }
}

///Open run set window
void MainWindow::on_rm_run_setting_triggered()
{
    int minValue=100, maxValue=5000,stepValue=100; //范围，步长
    bool ok=false;
    int resValue = QInputDialog::getInt(this, tr("运行设置"),tr("输入运行间隔时长(ms)"),
                                        this->data.intervalTime, minValue,maxValue,stepValue,&ok);
    if (ok) //是否确认输入
    {
        this->ui->interval_time_slider->setValue(resValue);
    }
}

///Open run log file
void MainWindow::on_rm_run_log_file_triggered()
{
    if(!this->log_checker->isHidden()){
        this->log_checker->hide();
    }

    if(this->log_checker->isMinimized()){
        this->log_checker->showNormal();
    }else{
        this->log_checker->show();
    }
}

///Save run log file
void MainWindow::on_rm_save_run_log_triggered()
{
    this->log_checker->saveLog();
}

///Open or close ram check pannel
void MainWindow::on_pm_ram_checker_triggered()
{
    if(!this->ram_checker->isHidden()){
        this->ram_checker->hide();
    }

    if(this->ram_checker->isMinimized()){
        this->ram_checker->showNormal();
    }else{
        this->ram_checker->show();
    }
}

///Open or close rom check pannel
void MainWindow::on_pm_rom_checker_triggered()
{
    if(!this->rom_checker->isHidden()){
        this->rom_checker->hide();
    }

    if(this->rom_checker->isMinimized()){
        this->rom_checker->showNormal();
    }else{
        this->rom_checker->show();
    }
}

///Open or close formate code pannel
void MainWindow::on_pm_machine_code_translator_triggered()
{
    QProcess process;
//    process.startDetached("C:\\Users\\haley\\Desktop\\version1.4.0\\DVCC_format_converter.exe");
    process.startDetached(QDir::currentPath()+"\\DVCC_format_converter.exe");
}

///Open code desigin pannel
void MainWindow::on_pm_designer_triggered()
{
    QProcess process;
    //TODO change address
//    process.startDetached("C:\\Users\\haley\\Desktop\\version1.4.0\\DVCC_format_converter.exe");
    process.startDetached(QDir::currentPath()+"\\dvcc_designer.exe");
}

///Open other pannel
void MainWindow::on_pm_other_pannel_triggered()
{

}

//----部件选择----
//TODO make a component select pannel
void MainWindow::on_pm_load_ram_triggered(bool checked)
{
    this->data.load_ram=checked;
    this->data.load_ar=checked;
}

void MainWindow::on_pm_load_rom_triggered(bool checked)
{
    this->data.load_con=checked;
    this->data.load_rom=checked;
    this->data.load_ir=checked;
}

void MainWindow::on_pm_load_299b_triggered(bool checked)
{
    this->data.load_shifter_299b=checked;
}

void MainWindow::on_pm_load_alu_triggered(bool checked)
{
    this->data.load_alu=checked;
    this->data.load_dr1=checked;
    this->data.load_dr2=checked;
}

void MainWindow::on_pm_load_register_triggered(bool checked)
{
    this->data.load_r0=checked;
    this->data.load_r1=checked;
    this->data.load_r2=checked;
}

void MainWindow::on_pm_load_pc_triggered(bool checked)
{
    this->data.load_pc=checked;
}

//----------------------------------选项菜单/Option menu---------------
///Open setting pannel
void MainWindow::on_om_settings_triggered()
{
    SettingPannel* settingPannel=new SettingPannel(this);
    settingPannel->callPannel();
}

///Set window size to default size
void MainWindow::on_om_default_win_size_triggered()
{
    this->resize(this->config_set.defaultWinSize);
}

///Open skin set pannel
void MainWindow::on_om_style_triggered()
{
    //条目选择输入
    QStringList items; //ComboBox 列表的内容

    QDir dir(QDir::currentPath()+"/resource/file_resource/theme/");
    if(dir.exists()){
        //查看路径中后缀为.cfg格式的文件
        QStringList filters;
        filters<<QString("*.qss");
        dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
        dir.setNameFilters(filters);  //设置文件名称过滤器，只为filters格式
        int file_count=dir.count();
        if(file_count>0){
            for(int i=0; i<file_count; i++)
            {
                items<<dir[i].split(".")[0];
            }
        }
    }

    int     curIndex=0; //初始选择项
    bool    editable=false; //ComboBox是否可编辑
    bool    ok=false;

    QString selectThemeName = QInputDialog::getItem(this,tr("主题选择"),tr("请选择主题"),items,curIndex,editable,&ok);

    if (ok && !selectThemeName.isEmpty()){
        //stylesheet
        QString conThemePath=QDir::currentPath()+"/resource/file_resource/theme/"+selectThemeName+".qss";
        QFile conThemeFile(conThemePath);
        conThemeFile.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream conThemeStream(&conThemeFile);
        QString styleSheetReadIn=conThemeStream.readAll();
        this->setStyleSheet(styleSheetReadIn);
        conThemeFile.close();
        statusBar()->showMessage(tr("主题加载成功"),1000);
    }

}

///Open font set pannel
void MainWindow::on_om_font_set_triggered()
{
    QFont oldfont=this->ui->centralwidget->font();
    bool res;
    QFont newFontSet=QFontDialog::getFont(&res,oldfont,this);
    if(res){
        QString styleSheet=this->styleSheet();
        this->setStyleSheet("");
        this->setFont(newFontSet);
        this->ui->micro_code_info_table->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
        this->setStyleSheet(styleSheet);

    }
}

//--------------------------关于菜单/About menu----------------------------

///Open help
void MainWindow::on_am_use_handbook_triggered()
{
    QDesktopServices::openUrl(QUrl("https://haleyehrich.github.io/product/dvcc/dvcc_index.html"));
}

///Open constructer infomation pannel
void MainWindow::on_am_app_constructer_info_triggered()
{
    QMessageBox::aboutQt(this,"Qt information");
}

///Open copyright infomation pannel
void MainWindow::on_am_copyright_info_triggered()
{
    QMessageBox aboutMsg(this);
    aboutMsg.setTextInteractionFlags(Qt::TextSelectableByMouse);
    aboutMsg.setTextFormat(Qt::RichText);
    aboutMsg.addButton(tr("跳转GitHub"), QMessageBox::ActionRole);
    aboutMsg.addButton(QMessageBox::Close);
    aboutMsg.setText(tr("<h2>版权信息</h2>"
                        "<ul>"
                        "<li>开源协议：Apache License Version 2.0, January 2004.</li>"
                        "<li>Apache:  <a href=\"http://www.apache.org/licenses/\">http://www.apache.org/licenses/</a></li>"
                        "<li>软件开源地址 <a href=\"https://github.com/HaleyEhrich/DvccSimulationEnvironment\">https://github.com/HaleyEhrich/DvccSimulationEnvironment</a></li>"
                        "<li>个人主页:<a href=\"https://haleyehrich.github.io\">https://haleyehrich.github.io</a></li>"
                        "<li>问题反馈联系方式 <a href=\"haley_ehrich@outlook.com\">haley_ehrich@outlook.com</a> </li>"
                        "</ul>"));
    aboutMsg.setWindowTitle(tr("版权信息"));
    aboutMsg.show();
    int res=aboutMsg.exec();
    if(res==QMessageBox::Close){
        aboutMsg.close();
    }else{
        QDesktopServices::openUrl(QUrl("https://github.com/HaleyEhrich/DvccSimulationEnvironment"));
    }
}

///Open version info pannel
void MainWindow::on_am_app_version_info_triggered()
{
    QMessageBox a(this);
    a.setTextFormat(Qt::RichText);
    a.setText(tr("<h2>Version 1.4.2.2</h2>"
                 "<h2>Updata time 2022-1-27</h2>"
                 "<h4>自动检查更新功能会在后期上线，在此之前请关注Github release，或手动点击检查更新按钮.</h4>"));
    a.setIconPixmap(QPixmap(":/win_img/logo.png").scaled(120,120));
    a.addButton(QMessageBox::Ok);
    a.exec();
}

//-----------------------------工具按钮------------------------------------
///Open file
void MainWindow::on_qs_open_file_btn_clicked()
{
    this->on_fm_open_file_triggered();
}

///Save file
void MainWindow::on_qs_save_file_btn_clicked()
{
    this->on_fm_save_file_triggered();
}

///Open run set pannel
void MainWindow::on_qs_run_set_btn_clicked()
{
    this->on_rm_run_setting_triggered();
}

///Open or close micro code infomation table
void MainWindow::on_qs_micro_code_info_btn_clicked()
{
    this->ui->rm_run_micro_set->setChecked(!this->ui->rm_run_micro_set->isChecked());
    this->on_rm_run_micro_set_triggered(this->ui->rm_run_micro_set->isChecked());
}

///Load select preset code
void MainWindow::on_qs_load_preset_btn_clicked()
{
    //    qDebug()<<"load preset";
    QString filePath=this->ui->qs_preset_combobox->currentData().toString();
    statusBar()->showMessage("程序文件:"+filePath,1000);
    filePath.replace("/","\\");
    this->micro_code_file=new QFile(filePath);
    this->micro_code_file->open(QIODevice::ReadWrite | QIODevice::Text);
retryLoad:
    //    qDebug()<<"load start";
    if(this->micro_code_file->isOpen()==false){
        switch (QMessageBox::critical(this,tr("错误"),tr("文件打开失败!"),QMessageBox::Retry,QMessageBox::Cancel)){
        case QMessageBox::Retry:{
            goto retryLoad;
            break;
        }
        case QMessageBox::Cancel:{
            return;
        }
        }
    }else{
        QString line;
        int ramLine=0,romLine=0,outOfRange=0;
        while (this->micro_code_file->atEnd() == false) {

            line=this->micro_code_file->readLine();
            //            qDebug()<<"loading"<<line;
            switch (this->loadMCLine(line)){
            case 0:{

                break;
            }
            case 1:{
                ramLine++;
                break;
            }
            case 2:{
                romLine++;
                break;
            }
            case 3:{
                outOfRange++;
                break;
            }
            }
        }
        //        qDebug()<<"load end";
        QMessageBox::about(this,tr("完成"),
                           QString(tr("<h1>😶‍🌫️微代码文件载入成功。</h1>"
                                      "<ul><li>共载入<b>%1(D)</b>行Ram信息</li>"
                                      "<li>共载入<b>%2(D)</b>行Rom信息</li>"
                                      "<li>超范围<b>%3(D)</b>行</li></ul>"))
                           .arg(ramLine,4,10,QLatin1Char('0')).arg(romLine,4,10,QLatin1Char('0')).arg(outOfRange,4,10,QLatin1Char('0')));

        this->micro_code_file->close();

        delete this->micro_code_file;
        this->micro_code_file=nullptr;

        this->resetSystem(false);
    }

}

/// Clear PC register data
void MainWindow::on_qs_clear_pc_btn_clicked()
{
    this->data.data_pc=0;
}

///以指令为运行主体，一次运行一条指令
///Run in auto and step by cmd (means stop run when microcode No. == preset stop No.)
void MainWindow::on_qs_cmd_run_step_btn_clicked()
{

    if(this->ui->qs_auto_run_set_btn_group->isHidden()){
        this->ui->qs_auto_run_set_btn_group->show();
    }else{
        QMessageBox::information(this,tr("提示"),tr("您已经开始了运行一条指令"));
        return;
    }

    if(this->micro_code_file==nullptr){
        switch (QMessageBox::information(this,tr("警告"),tr("微程序文件不存在，继续运行会造成不可预知的错误，是否继续运行？"),QMessageBox::Ok,QMessageBox::Cancel)){
        case QMessageBox::Ok:{

            break;
        }
        case QMessageBox::Cancel:{
            return;
        }
        default:{
            return;
        }
        }
    }

    do{
        if(this->ui->qs_pause_run_btn->isChecked()){
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
            continue;
        }

        QTime _Timer = QTime::currentTime().addMSecs(this->data.intervalTime);
        while( QTime::currentTime() < _Timer )
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        on_qs_micro_run_step_btn_clicked();
    }while(this->data.data_nextMroAddress!=this->data.stopMroAddress
           && !this->ui->qs_stop_run_btn->isChecked()
           && this->data.data_pc<this->data.ram_row_size);

    //恢复按钮
    this->ui->qs_stop_run_btn->setChecked(false);
    this->ui->qs_pause_run_btn->setChecked(false);
    this->ui->qs_auto_run_set_btn_group->setHidden(true);
}

//TODO Optimize the process-->优化信号识别，避免重复判断
///以微代码为运行主体，一次运行一条微指令
///Run in auto and step by micro cmd
void MainWindow::on_qs_micro_run_step_btn_clicked()
{
    //更新微地址--每次运行都选择将下一微地址存入，nextMroAddress
    this->data.data_mroAddress=this->data.data_nextMroAddress;

    //信号识别
    signalsPreProcess(&this->data);

    //Save log file
    this->log_checker->addLog(this->data.getLogString());

    /// means have bus data, need paint bus
    bool busHaveData=true;
    if (data.data_rom[data.data_mroAddress][mb3]== 0
            && data.data_rom[data.data_mroAddress][mb2] == 0
            && data.data_rom[data.data_mroAddress][mb1] == 0) {//内部输出设备不存在
        if (data.data_rom[data.data_mroAddress][mB1] == 0
                && data.data_rom[data.data_mroAddress][mB0] == 1
                && data.data_rom[data.data_mroAddress][mwe] == 0) {//RAM
            RAM(&this->data);
        }
        else if (data.data_rom[data.data_mroAddress][mB1] == 0
                 && data.data_rom[data.data_mroAddress][mB0] == 0) {//SW
            SW(&this->data);
        }else {//None out
            busHaveData=false;
        }
    }
    else if (data.data_rom[data.data_mroAddress][mb3] == 0
             && data.data_rom[data.data_mroAddress][mb2] == 0
             && data.data_rom[data.data_mroAddress][mb1] == 1) {//RS-B
        RIOut(&this->data);
    }
    else if (data.data_rom[data.data_mroAddress][mb3] == 0
             && data.data_rom[data.data_mroAddress][mb2] == 1
             && data.data_rom[data.data_mroAddress][mb1] == 0) {//RD-B
        RIOut(&this->data);
    }
    else if (data.data_rom[data.data_mroAddress][mb3] == 0
             && data.data_rom[data.data_mroAddress][mb2] == 1
             && data.data_rom[data.data_mroAddress][mb1] == 1) {//RI-B(选R2）
        RIOut(&this->data);
    }
    else if (data.data_rom[data.data_mroAddress][mb3] == 1
             && data.data_rom[data.data_mroAddress][mb2] == 0
             && data.data_rom[data.data_mroAddress][mb1] == 0) {//299-B
        _299(&this->data);
    }
    else if (data.data_rom[data.data_mroAddress][mb3] == 1
             && data.data_rom[data.data_mroAddress][mb2] == 0
             && data.data_rom[data.data_mroAddress][mb1] == 1) {

        if(this->data.statu_alub==true){//ALU-B
            ALU(&this->data);
        }else{//None out
            busHaveData=false;
        }

    }
    else if (data.data_rom[data.data_mroAddress][mb3] == 1
             && data.data_rom[data.data_mroAddress][mb2] == 1
             && data.data_rom[data.data_mroAddress][mb1] == 0) {

        if (data.data_rom[data.data_mroAddress][mc3] == 1
                && data.data_rom[data.data_mroAddress][mc2] == 1
                && data.data_rom[data.data_mroAddress][mc1] == 0) {//PC-B
            PC(&this->data);
        }else {//None out
            busHaveData=false;
        }

    }
    else if (data.data_rom[data.data_mroAddress][mb3] == 1
             && data.data_rom[data.data_mroAddress][mb2] == 1
             && data.data_rom[data.data_mroAddress][mb1] == 1) {//NONE
        busHaveData=false;
    }


    //---------------------------设置总线/Set busline--------------------------
    //TODO 将该部分总线绘制移动到绘图，而非自动运行
    if(busHaveData){
        this->busLine->setPen(linePenAct);
    }else{
        this->busLine->setPen(linePen);
    }

    //----------------------------输入区域/Input------------------------------
    if (data.data_rom[data.data_mroAddress][ma3] == 0
            && data.data_rom[data.data_mroAddress][ma2] == 0
            && data.data_rom[data.data_mroAddress][ma1] == 0) {//内部输入设备不选中
        if (data.data_rom[data.data_mroAddress][mB1] == 1
                && data.data_rom[data.data_mroAddress][mB0] == 0) {//LED

            if(this->data.signal_we==WRITE){
                LED(&this->data);
            }else{//NONE in

            }

            LED(&this->data);
        }
        else if (data.data_rom[data.data_mroAddress][mB1] == 0
                 && data.data_rom[data.data_mroAddress][mB0] == 1) {//RAM
            RAM(&this->data);
            //Freash ram pannel data
            this->ram_checker->freshData();
        }
        else {
            if (data.data_rom[data.data_mroAddress][ms1] == 1
                    && data.data_rom[data.data_mroAddress][ms0] == 1) {//299装数
                _299(&this->data);
            }
            else {//NONE in
            }
        }
    }
    else if (data.data_rom[data.data_mroAddress][ma3] == 0
             && data.data_rom[data.data_mroAddress][ma2] == 0
             && data.data_rom[data.data_mroAddress][ma1] == 1) {//RiIN
        RIIn(&this->data);
    }
    else if (data.data_rom[data.data_mroAddress][ma3] == 0
             && data.data_rom[data.data_mroAddress][ma2] == 1
             && data.data_rom[data.data_mroAddress][ma1] == 0) {//DR1
        DR1(&this->data);
    }
    else if (data.data_rom[data.data_mroAddress][ma3] == 0
             && data.data_rom[data.data_mroAddress][ma2] == 1
             && data.data_rom[data.data_mroAddress][ma1] == 1) {//DR2
        DR2(&this->data);
    }
    else if (data.data_rom[data.data_mroAddress][ma3] == 1
             && data.data_rom[data.data_mroAddress][ma2] == 0
             && data.data_rom[data.data_mroAddress][ma1] == 0) {//LDIR
        IR(&this->data);
    }
    else if (data.data_rom[data.data_mroAddress][ma3] == 1
             && data.data_rom[data.data_mroAddress][ma2] == 0
             && data.data_rom[data.data_mroAddress][ma1] == 1) {//LDAD(PC)

        if (data.data_rom[data.data_mroAddress][mc3] == 1
                && data.data_rom[data.data_mroAddress][mc2] == 1
                && data.data_rom[data.data_mroAddress][mc1] == 0) {
            PC(&this->data);
        }
        else {//NONE in

        }
    }
    else if (data.data_rom[data.data_mroAddress][ma3] == 1
             && data.data_rom[data.data_mroAddress][ma2] == 1
             && data.data_rom[data.data_mroAddress][ma1] == 0) {//LDAR
        AR(&this->data);
    }
    else if (data.data_rom[data.data_mroAddress][ma3] == 1
             && data.data_rom[data.data_mroAddress][ma2] == 1
             && data.data_rom[data.data_mroAddress][ma1] == 1) {
        if (data.data_rom[data.data_mroAddress][ms1] == 1
                && data.data_rom[data.data_mroAddress][ms0] == 1) {//299装数
            _299(&this->data);
        }
        else {//NONE in

        }
    }

    //跳转
    if (data.data_rom[data.data_mroAddress][mc3] == 0
            && data.data_rom[data.data_mroAddress][mc2] == 0
            && data.data_rom[data.data_mroAddress][mc1] == 0) {//顺序执行
        this->data.data_nextMroAddress=Oreder(&this->data);
    }
    else if (data.data_rom[data.data_mroAddress][mc3] == 0
             && data.data_rom[data.data_mroAddress][mc2] == 0
             && data.data_rom[data.data_mroAddress][mc1] == 1) {//P(1)
        this->data.data_nextMroAddress=P1(&this->data);
    }
    else if (data.data_rom[data.data_mroAddress][mc3] == 0
             && data.data_rom[data.data_mroAddress][mc2] == 1
             && data.data_rom[data.data_mroAddress][mc1] == 0) {//P(2)
        this->data.data_nextMroAddress=P2(&this->data);
    }
    else if (data.data_rom[data.data_mroAddress][mc3] == 0
             && data.data_rom[data.data_mroAddress][mc2] == 1
             && data.data_rom[data.data_mroAddress][mc1] == 1) {//P(3)
        this->data.data_nextMroAddress=P3(&this->data);
    }
    else if (data.data_rom[data.data_mroAddress][mc3] == 1
             && data.data_rom[data.data_mroAddress][mc2] == 0
             && data.data_rom[data.data_mroAddress][mc1] == 0) {//P(4)
        this->data.data_nextMroAddress=P4(&this->data);
    }else{
        this->data.data_nextMroAddress=Oreder(&this->data);
    }

    this->setTable();

    this->ui->circuit_diagram->viewport()->update();
}

///Pause or start auto run (in cmd)
void MainWindow::on_qs_pause_run_btn_clicked(bool checked)
{
    if(checked){
        this->ui->qs_pause_run_btn->setIcon(QIcon(":/icon/play.svg"));
        this->ui->qs_pause_run_btn->setText(tr("继续运行"));
    }else{
        this->ui->qs_pause_run_btn->setIcon(QIcon(":/icon/pause.svg"));
        this->ui->qs_pause_run_btn->setText(tr("暂停"));
    }
}

///Stop auto run (in cmd)
void MainWindow::on_qs_stop_run_btn_clicked(bool checked)
{
    if(checked){
        this->ui->qs_auto_run_set_btn_group->hide();
    }else{
        this->ui->qs_stop_run_btn->setChecked(true);
        this->ui->qs_auto_run_set_btn_group->hide();
    }
}

//TODO auto run statu change opration set
///更改运行状态——自动运行/手动信号运行
///Change running state, run in auto(checked==true)/run in signal selected(checked==false)
void MainWindow::on_auto_run_ck_clicked(bool checked)
{
    //信号面板关闭/开启
    this->ui->tw_signal_btn_groups->setDisabled(checked);
    this->ui->sig_299b_btn->setDisabled(checked);

    if(this->config_set.clearDataWhenChangeStatu){
        this->data.reSetDataSet();
    }

    this->data.data_mroAddress=this->data.data_nextMroAddress=0;

    signalsPreProcess(&this->data);

    this->setSigBtn();

    this->setTable();

    //重置
    this->ui->switch_spb->setValue(this->data.data_swi_input);
    this->ui->alu_cmd_spb->setValue(this->data.data_function_swi);


    //Decide weather open real-time refresh cir paint
    this->ui->circuit_diagram->viewport()->update();

    if(checked==true){
        //关闭alu指令输入框
        this->ui->alu_cmd_input_box->hide();
        //
        this->ui->micro_start_set_box->show();
        //
        this->ui->qs_cmd_run_step_btn->show();
        this->ui->qs_micro_run_step_btn->show();

    }else{
        //开始alu指令输入框
        this->ui->alu_cmd_input_box->show();

        this->ui->micro_start_set_box->hide();
        //
        this->ui->qs_cmd_run_step_btn->hide();
        this->ui->qs_micro_run_step_btn->hide();

        //关闭运行
        if(this->ui->qs_auto_run_set_btn_group->isHidden()==false){
            this->ui->qs_stop_run_btn->setChecked(true);
            this->on_qs_stop_run_btn_clicked(true);
        }
    }


}

/// \brief Micro code start (No.) reset a number
/// \param arg1 value
void MainWindow::on_micro_start_spb_valueChanged(int arg1)
{
    this->data.stopMroAddress=arg1;
}

/// 开关按钮数据变化
void MainWindow::on_switch_spb_valueChanged(int arg1){
    this->data.data_swi_input=arg1;
}

/// Alu control signals change
void MainWindow::on_alu_cmd_spb_editingFinished()
{
    QString aluString=QString("%1").arg(this->ui->alu_cmd_spb->value(),6,2,QLatin1Char('0'));
    this->data.data_rom[this->data.data_mroAddress][ms3]=(aluString[0]=='1');
    this->data.data_rom[this->data.data_mroAddress][ms2]=(aluString[1]=='1');
    this->data.data_rom[this->data.data_mroAddress][ms1]=(aluString[2]=='1');
    this->data.data_rom[this->data.data_mroAddress][ms0]=(aluString[3]=='1');
    this->data.data_rom[this->data.data_mroAddress][mm]=(aluString[4]=='1');
    this->data.data_rom[this->data.data_mroAddress][mcn]=(aluString[5]=='1');
}

//
void MainWindow::on_interval_time_slider_valueChanged(int value)
{
    this->data.intervalTime=value;
    this->ui->mc_interval_time_lab->setText(QString("%1 (ms)").arg(value));
}

void MainWindow::on_swc_ck_stateChanged(int arg1)
{
    this->data.signal_swc=arg1;
}


void MainWindow::on_swa_ck_stateChanged(int arg1)
{
    this->data.signal_swa=arg1;
}

//------------------------------手动信号管理/hand signals manage---------------------------
void MainWindow::on_sig_ldar_btn_clicked(bool checked)
{
    this->data.statu_ldar=checked;
}
void MainWindow::on_sig_ldad_btn_clicked(bool checked)
{
    this->data.statu_ldad=checked;
    this->data.statu_ldled=checked;
}
void MainWindow::on_sig_lddr1_btn_clicked(bool checked)
{
    this->data.statu_lddr1=checked;
}
void MainWindow::on_sig_lddr2_btn_clicked(bool checked)
{
    this->data.statu_lddr2=checked;
}
void MainWindow::on_sig_ldpc_btn_clicked(bool checked)
{
    this->data.statu_ldpc=checked;
}
void MainWindow::on_sig_ce_btn_clicked(bool checked)
{
    this->data.signal_ce=checked;
}
void MainWindow::on_sig_we_clicked(bool checked)
{
    this->data.signal_we=checked;
}
void MainWindow::on_sig_ar_btn_clicked(bool checked)
{
    this->data.signal_ar=checked;
}
void MainWindow::on_sig_swb_btn_clicked(bool checked)
{
    this->data.statu_swb=checked;
}
void MainWindow::on_sig_alub_btn_clicked(bool checked)
{
    this->data.statu_alub=checked;
}
void MainWindow::on_sig_pcb_btn_clicked(bool checked)
{
    this->data.statu_pcb=checked;
}
void MainWindow::on_sig_299b_btn_clicked(bool checked)
{
    this->data.statu_299b=checked;
}
void MainWindow::on_sig_clear_pc_btn_clicked()
{
    this->on_qs_clear_pc_btn_clicked();
}

//TODO Optimize the process
/// hand t4 pulse run
void MainWindow::on_sig_t4_plus_btn_clicked()
{
    //要先处理完所有的数据，然后将该上总线的数据上总线，但是ar等有存储功能的部件，数据应该交换完再绘图
    //总线数据每次清0
    //pc++等逻辑必须处理完再绘图
    //299的信号更新别忘了,尤其是299作为输入
    ///ram、SW、299、alu、pc
    ///ram,led,299,dr1,dr2,IR,PC,AR,

    //总线数据清0
    this->data.data_bus="00";

    this->setTable();

    bool flag=false;//用于监测是否已经有了输出
    //输出检测
    if(this->data.load_ram && this->data.signal_we==READ && this->data.signal_ce && !this->data.statu_ldar){
        flag=true;
        RAM(&this->data);
    }
    if(this->data.statu_swb){
        if(flag) statusBar()->showMessage("[Error]输出冲突",4);
        flag=true;
        SW(&this->data);
    }
    if(this->data.load_shifter_299b && this->data.statu_299b){
        if(flag) statusBar()->showMessage("[Error]输出冲突",4);
        flag=true;
        _299(&this->data);
    }
    if(this->data.load_alu && this->data.statu_alub){
        if(flag) statusBar()->showMessage("[Error]输出冲突",4);
        flag=true;
        ALU(&this->data);
    }
    if(this->data.statu_pcb){
        if(flag) statusBar()->showMessage("[Error]输出冲突",4);
        flag=true;
        PC(&this->data);

    }


    //TODO 将该部分总线绘制移动到绘图，而非自动运行
    if(flag){
        this->busLine->setPen(linePenAct);
    }else{
        this->busLine->setPen(linePen);
    }


    //输入检测，必备的在下侧，不能删去避免重复执行
    if(this->data.load_ram && this->data.signal_we==WRITE && this->data.signal_ce){
        RAM(&this->data);
        this->ram_checker->freshData();
    }
    if(this->data.statu_ldled && this->data.signal_we==WRITE){
        LED(&this->data);
    }
    if(this->data.data_rom[this->data.data_mroAddress][ms1]
            && this->data.data_rom[this->data.data_mroAddress][ms0]){
        _299(&this->data);
    }

    DR1(&this->data);
    DR2(&this->data);
    IR(&this->data);
    PC(&this->data);
    AR(&this->data);

    //Save log file
    this->log_checker->addLog(this->data.getLogString());

    this->ui->circuit_diagram->repaint();
}





