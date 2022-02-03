#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //微代码文件正则匹配式/Microcode file regular match type
    QRegularExpression romLineNewPattern{"^(\\$|＄)M[0-9A-Fa-f]{10}.*"};
    QRegularExpression romLineOldPattern{"^(\\$|＄)M[0-9A-Fa-f]{8}.*"};
    QRegularExpression ramLineNewPattern{"^(\\$|＄)P[0-9A-Fa-f]{6}.*"};
    QRegularExpression ramLineOldPattern{"^(\\$|＄)P[0-9A-Fa-f]{4}.*"};

    QString *convToStd(QString softMCLines);
    QString *convToSoft(QString stdMCLines);
protected slots:
    void on_conv_to_soft_clicked();
    void on_conv_to_std_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
