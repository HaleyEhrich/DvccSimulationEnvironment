#ifndef ROMCHECK_H
#define ROMCHECK_H

#include <QMessageBox>
#include <QString>
#include <QTableWidgetItem>
#include <QWidget>

#include "dataSet.h"
#include "functionSet.h"

namespace Ui {
class ROMCheck;
}

class ROMCheck : public QWidget
{
    Q_OBJECT

public:
    char hexNumberSet[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    _data* data;
    bool isFreshData;
    bool editAble;
    QRegularExpression *matchPattrn;
    QString oldText;

    bool getBin(int&);
    bool getHex(int,QString&);
    bool getB1B0Statu(int,QString&);
    bool getAStatu(int,QString&);
    bool getBStatu(int,QString&);
    bool getCStatu(int,QString&);
    bool getNextMroAD(int,QString&);
    //刷新数据
    bool freshData();
    bool editModel();
    explicit ROMCheck(QWidget *parent = nullptr,_data* data=nullptr);
    ~ROMCheck();

private slots:
    void on_editRom_clicked();

    void on_freshRom_clicked();

    void on_ROMTable_itemChanged(QTableWidgetItem *item);

    void on_ROMTable_cellDoubleClicked(int row, int column);

private:
    Ui::ROMCheck *ui;
};

#endif // ROMCHECK_H
