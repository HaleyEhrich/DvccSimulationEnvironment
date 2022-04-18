#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDesktopServices>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileSystemModel>
#include <QFont>
#include <QFontDatabase>
#include <QFontDialog>
#include <QList>
#include <QInputDialog>
#include <QGraphicsBlurEffect>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QSettings>
#include <QMainWindow>
#include <QMap>
#include <QMessageBox>
#include <QProcess>
#include <QResizeEvent>
#include <QSettings>
#include <QVariant>

#include <string>

#include "systemdataset.h"
#include "configset.h"
#include "../DVCC/functionset.h"
#include ".\\toolpannel\\ramcheck.h"
#include ".\\toolpannel\\romcheck.h"
#include ".\\toolpannel\\settingpannel.h"
#include ".\\toolpannel\\logpannel.h"
\
#include ".\\paint\\ramqgitem.h"
#include ".\\paint\\aluqgitem.h"
#include ".\\paint\\shifter299qgitem.h"
#include ".\\paint\\dr1qgitem.h"
#include ".\\paint\\dr2qgitem.h"
#include ".\\paint\\pcqgitem.h"
#include ".\\paint\\arqgitem.h"
#include ".\\paint\\outputqgitem.h"
#include ".\\paint\\inputqgitem.h"
#include ".\\paint\\microconqgitem.h"
#include ".\\paint\\r0qgitem.h"
#include ".\\paint\\r1qgitem.h"
#include ".\\paint\\r2qgitem.h"
#include ".\\paint\\irqgitem.h"
#include ".\\paint\\signalsqgitem.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //加载环境
    bool loadEnviroMent(QString envPath=QDir::currentPath());

    bool initGraphics();

    inline int loadMCLine(QString &mcLine);

    void resetSystem(bool freshRaom);

    void setTable();

    void setSigBtn();

protected:

    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;

private slots:

    void on_fm_new_win_triggered();

    void on_fm_open_file_triggered();

    void on_fm_paste_code_triggered();

    void on_fm_save_file_triggered();

    void on_fm_save_as_file_triggered();

    void on_fm_checker_triggered();

    void on_rm_run_micro_set_triggered(bool checked);

    void on_rm_run_setting_triggered();

    void on_rm_run_log_file_triggered();

    void on_rm_save_run_log_triggered();


    void on_pm_ram_checker_triggered();

    void on_pm_rom_checker_triggered();

    void on_pm_machine_code_translator_triggered();

    void on_pm_designer_triggered();

    void on_pm_other_pannel_triggered();

    void on_pm_load_ram_triggered(bool checked);

    void on_pm_load_rom_triggered(bool checked);

    void on_pm_load_299b_triggered(bool checked);

    void on_pm_load_alu_triggered(bool checked);

    void on_pm_load_register_triggered(bool checked);

    void on_pm_load_pc_triggered(bool checked);


    void on_om_settings_triggered();

    void on_om_default_win_size_triggered();

    void on_om_style_triggered();

    void on_om_font_set_triggered();


    void on_am_use_handbook_triggered();

    void on_am_app_constructer_info_triggered();

    void on_am_copyright_info_triggered();

    void on_am_app_version_info_triggered();


    void on_qs_open_file_btn_clicked();

    void on_qs_save_file_btn_clicked();

    void on_qs_run_set_btn_clicked();

    void on_qs_micro_code_info_btn_clicked();

    void on_qs_load_preset_btn_clicked();

    void on_qs_clear_pc_btn_clicked();

    void on_qs_cmd_run_step_btn_clicked();

    void on_qs_micro_run_step_btn_clicked();

    void on_qs_pause_run_btn_clicked(bool checked);

    void on_qs_stop_run_btn_clicked(bool checked);


    void on_auto_run_ck_clicked(bool checked);

    void on_micro_start_spb_valueChanged(int arg1);

    void on_switch_spb_valueChanged(int arg1);

    void on_alu_cmd_spb_editingFinished();

    void on_interval_time_slider_valueChanged(int value);

    void on_swc_ck_stateChanged(int arg1);

    void on_swa_ck_stateChanged(int arg1);


    void on_sig_ldar_btn_clicked(bool checked);

    void on_sig_ldad_btn_clicked(bool checked);

    void on_sig_lddr1_btn_clicked(bool checked);

    void on_sig_lddr2_btn_clicked(bool checked);

    void on_sig_ldpc_btn_clicked(bool checked);

    void on_sig_ce_btn_clicked(bool checked);

    void on_sig_we_clicked(bool checked);

    void on_sig_ar_btn_clicked(bool checked);

    void on_sig_swb_btn_clicked(bool checked);

    void on_sig_alub_btn_clicked(bool checked);

    void on_sig_pcb_btn_clicked(bool checked);

    void on_sig_299b_btn_clicked(bool checked);

    void on_sig_clear_pc_btn_clicked();

    void on_sig_t4_plus_btn_clicked();



private:

    Ui::MainWindow *ui;

    ///
    QSettings* config_file=nullptr;

    ConfigSet config_set;

    int ram_row_size=128,rom_row_size=64;
    int ram_col_size=2,rom_col_size=25;

    //微代码文件正则匹配式/Microcode file regular match type
    QRegularExpression romLineNewPattern{"^(\\$|＄)M[0-9A-Fa-f]{10}.*"};
    QRegularExpression romLineOldPattern{"^(\\$|＄)M[0-9A-Fa-f]{8}.*"};
    QRegularExpression ramLineNewPattern{"^(\\$|＄)P[0-9A-Fa-f]{6}.*"};
    QRegularExpression ramLineOldPattern{"^(\\$|＄)P[0-9A-Fa-f]{4}.*"};

    //更改data大小，每次动态选择
    systemDataSet data;
    RAMCheck* ram_checker;
    ROMCheck* rom_checker;
    LogPannel* log_checker;

    QFile* micro_code_file=nullptr;

    QGraphicsScene *scene=nullptr;
    RamQGItem* ram=nullptr;
    ALUQGItem* alu=nullptr;
    Shifter299QGItem* shifter=nullptr;
    Dr1QGItem* dr1=nullptr;
    Dr2QGItem* dr2=nullptr;
    PCQGItem* pc=nullptr;
    ARQGItem* ar=nullptr;
    OutputQGItem* led=nullptr;
    InputQGItem* switcher=nullptr;
    MicroConQGItem* microCon=nullptr;
    IrQGItem* ir=nullptr;
    R0QGItem* r0=nullptr;
    R1QGItem* r1=nullptr;
    R2QGItem* r2=nullptr;
    SignalsQGItem* signalsLed=nullptr;
    QGraphicsLineItem* busLine=nullptr;
//    QGraphicsSimpleTextItem* busText=nullptr;



};
#endif // MAINWINDOW_H
