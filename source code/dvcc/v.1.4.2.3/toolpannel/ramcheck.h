#ifndef RAMCHECK_H
#define RAMCHECK_H

#include <QAbstractItemView>
#include <QFont>
#include <QFontDatabase>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QString>
#include <QTableView>
#include <QTableWidgetItem>
#include <QWidget>

#include "systemdataset.h"

namespace Ui {
class RAMCheck;
}

class RAMCheck : public QWidget
{
    Q_OBJECT

public:

    /// \brief 接口,将rom面板编辑按钮隐藏设置为hidden
    /// \param hiddden [True]设置编辑按钮不可见 [false]设置编辑按钮可见
    void setEditBtnHide(bool hiddden);

    /// \brief 设置rom面板为编辑模式/查看模式
    /// \param edit [True]设置为编辑模式 [false]设置为查看模式
    /// \return 设置成功返回true
    bool setEditModel(bool edit);


    /// \brief 刷新数据接口，调用该接口会对rom面板数据进行刷新
    /// \return 成功返回true，否则返回false
    bool freshData();

    explicit RAMCheck(QWidget *parent = nullptr, systemDataSet* data=nullptr);

    ~RAMCheck();

private slots:

    void on_freshRam_clicked();
    void on_RAMTable_itemChanged(QTableWidgetItem *item);
    void on_RAMTable_cellDoubleClicked(int row, int column);
    void on_edit_btn_clicked(bool checked);

private:

    systemDataSet* data;

    QRegularExpression *matchPattrn=nullptr;

    QString oldText;

    Ui::RAMCheck *ui;

};

#endif // RAMCHECK_H
