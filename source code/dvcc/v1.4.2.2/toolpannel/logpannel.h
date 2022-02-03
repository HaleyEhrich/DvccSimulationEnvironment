#ifndef LOGPANNEL_H
#define LOGPANNEL_H

#include <QString>
#include <QFileDialog>
#include <QStringList>
#include <QMessageBox>
#include <QWidget>

namespace Ui {
class LogPannel;
}

class LogPannel : public QWidget
{
    Q_OBJECT

public:
    explicit LogPannel(QWidget *parent = nullptr);
    ~LogPannel();

    void addLog(const QString& log);

    void saveLog();

    void freshLog();

private slots:
    void on_save_btn_clicked();

    void on_clear_btn_clicked();

    void on_fresh_log_clicked();

private:
    Ui::LogPannel *ui;

    QStringList logLine;
};

#endif // LOGPANNEL_H
