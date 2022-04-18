#ifndef ROMCHECK_H
#define ROMCHECK_H

#include <QFont>
#include <QFontDatabase>
#include <QMessageBox>
#include <QString>
#include <QTableWidgetItem>
#include <QWidget>

#include "systemdataset.h"
#include "../DVCC/functionset.h"

namespace Ui {
class ROMCheck;
}

class ROMCheck : public QWidget
{
    Q_OBJECT

public:
    char hexNumberSet[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

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


    /// \brief 更新数据，更新第i行rom数据为输入的字符串
    /// \param row 行数
    /// \param mcString 更新字符串
    /// \return 更新成功返回true，否则返回false
    bool updateRomRowData(int& row,QString mcString);

    /// \brief getMCInHex 获取第row行微指令的16进制字符串
    /// \param row 行数
    /// \param dataBack 返回的字符串位置
    /// \return [true]获取成功 [false]获取失败
    bool getMCInHex(int row,QString& dataBack);


    /// \brief getB1B0Statu 获取第row行微指令的B1B0字段状态描述
    /// \param row 行数
    /// \param dataBack 返回的字符串位置
    /// \return [true]获取成功 [false]获取失败
    bool getB1B0Statu(int row,QString& dataBack);

    /// \brief getB1B0Statu 获取第row行微指令的B1B0字段
    /// \param row 行数
    /// \param dataBack 返回的字符串位置
    /// \return [true]获取成功 [false]获取失败
    bool getB1B0(int row,QString& dataBack);


    /// \brief getAStatu 获取第row行微指令的A字段状态描述
    /// \param row 行数
    /// \param dataBack 返回的字符串位置
    /// \return [true]获取成功 [false]获取失败
    bool getAStatu(int row,QString& dataBack);

    /// \brief getAStatu 获取第row行微指令的A字段
    /// \param row 行数
    /// \param dataBack 返回的字符串位置
    /// \return [true]获取成功 [false]获取失败
    bool getA(int row,QString& dataBack);

    /// \brief getBStatu 获取第row行微指令的B字段状态描述
    /// \param row 行数
    /// \param dataBack 返回的字符串位置
    /// \return [true]获取成功 [false]获取失败
    bool getBStatu(int row,QString& dataBack);

    /// \brief getBStatu 获取第row行微指令的B字段
    /// \param row 行数
    /// \param dataBack 返回的字符串位置
    /// \return [true]获取成功 [false]获取失败
    bool getB(int row,QString& dataBack);

    /// \brief getCStatu 获取第row行微指令的C字段状态描述
    /// \param row 行数
    /// \param dataBack 返回的字符串位置
    /// \return [true]获取成功 [false]获取失败
    bool getCStatu(int row,QString& dataBack);

    /// \brief getCStatu 获取第row行微指令的C字段
    /// \param row 行数
    /// \param dataBack 返回的字符串位置
    /// \return [true]获取成功 [false]获取失败
    bool getC(int row,QString& dataBack);

    /// \brief getNextMroAD 获取第row行微指令的下一微指令字段
    /// \param row 行数
    /// \param dataBack 返回的字符串位置
    /// \return [true]获取成功 [false]获取失败
    bool getNextMroAD(int row,QString& dataBack);

    /// \brief getS3S0 获取ALu S3-S0 数据
    /// \param row 行数
    /// \param dataBack 返回的字符串位置
    /// \return [true]获取成功 [false]获取失败
    bool getS3S0(int row,QString& dataBack);

    /// \brief getM 获取ALU M 数据
    /// \param row 行数
    /// \param dataBack 返回的字符串位置
    /// \return [true]获取成功 [false]获取失败
    bool getM(int row,QString& dataBack);

    /// \brief getM 获取ALU CN 数据
    /// \param row 行数
    /// \param dataBack 返回的字符串位置
    /// \return [true]获取成功 [false]获取失败
    bool getCn(int row,QString& dataBack);


    bool getWe(int row,QString&dataBack);



    explicit ROMCheck(QWidget *parent = nullptr,systemDataSet* data=nullptr);

    ~ROMCheck();

private slots:

    void on_freshRom_clicked();

    void on_ROMTable_itemChanged(QTableWidgetItem *item);

    void on_ROMTable_cellDoubleClicked(int row, int column);

    void on_edit_btn_clicked(bool checked);

private:
    systemDataSet* data;

    QRegularExpression *matchPattrn;

    QString oldText;

    Ui::ROMCheck *ui;
};

#endif // ROMCHECK_H
