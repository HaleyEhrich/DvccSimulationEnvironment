#include "componentsettingpannel.h"
#include "ui_componentsettingpannel.h"

componentSettingPannel::componentSettingPannel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::componentSettingPannel)
{
    ui->setupUi(this);
}

componentSettingPannel::~componentSettingPannel()
{
    delete ui;
}
