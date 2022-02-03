#ifndef COMPONENTSETTINGPANNEL_H
#define COMPONENTSETTINGPANNEL_H

#include <QDialog>

namespace Ui {
class componentSettingPannel;
}

class componentSettingPannel : public QDialog
{
    Q_OBJECT

public:
    explicit componentSettingPannel(QWidget *parent = nullptr);
    ~componentSettingPannel();

private:
    Ui::componentSettingPannel *ui;
};

#endif // COMPONENTSETTINGPANNEL_H
