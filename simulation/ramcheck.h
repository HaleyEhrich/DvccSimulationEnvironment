#ifndef RAMCHECK_H
#define RAMCHECK_H

#include <QAbstractItemView>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QString>
#include <QTableView>
#include <QTableWidgetItem>
#include <QWidget>

#include "dataSet.h"

namespace Ui {
class RAMCheck;
}

class RAMCheck : public QWidget
{
    Q_OBJECT

public:
    char hexNumberSet[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    _data* data;
    bool isFreshData;
    bool editAble;
    QRegularExpression *matchPattrn;
    QString oldText;

    bool freshData();
    bool editModel();

    explicit RAMCheck(QWidget *parent = nullptr, _data* data=nullptr);
    ~RAMCheck();
private slots:
    void on_freshRam_clicked();

    void on_editRam_clicked();

    void on_RAMTable_itemChanged(QTableWidgetItem *item);

    void on_RAMTable_cellDoubleClicked(int row, int column);

private:
    Ui::RAMCheck *ui;

};

#endif // RAMCHECK_H
