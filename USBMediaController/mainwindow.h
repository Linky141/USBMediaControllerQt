#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QIODevice>
#include <QMessageBox>
#include <QObject>
#include <QDebug>
#include <QString>
#include <stdio.h>
#include <tchar.h>
#include "SerialPort.h"
#include "Options.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include "io.h"
#include "deviceconfig.h"
#include "executecommand.h"
#include <QKeyEvent>
#include <stdexcept>
#include <QTextCodec>
#include <QMessageBox>
#include <QSystemTrayIcon>

class QSerialPort;
namespace Ui {
    class MainWindow;
}
class QSystemTrayIcon;


class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void UARTWriteLables();

private slots:
    void readSerialData();
    void on_btn_connect_clicked();
    void on_btn_disconnect_clicked();
    void on_btn_11_clicked();
    void on_btn_14_clicked();
    void on_btn_12_clicked();
    void on_btn_13_clicked();
    void on_btn_21_clicked();
    void on_btn_22_clicked();
    void on_btn_23_clicked();
    void on_btn_24_clicked();
    void on_btn_31_clicked();
    void on_btn_32_clicked();
    void on_btn_33_clicked();
    void on_btn_34_clicked();
    void on_btn_41_clicked();
    void on_btn_42_clicked();
    void on_btn_43_clicked();
    void on_btn_44_clicked();
    void on_btn_zapiskonfpolaczenia_clicked();
    void on_konf_checkbox_11_stateChanged(int arg1);
    void on_konf_checkbox_13_stateChanged(int arg1);
    void on_konf_checkbox_12_stateChanged(int arg1);
    void on_konf_checkbox_14_stateChanged(int arg1);
    void on_konf_checkbox_21_stateChanged(int arg1);
    void on_konf_checkbox_22_stateChanged(int arg1);
    void on_konf_checkbox_23_stateChanged(int arg1);
    void on_konf_checkbox_24_stateChanged(int arg1);
    void on_konf_checkbox_31_stateChanged(int arg1);
    void on_konf_checkbox_32_stateChanged(int arg1);
    void on_konf_checkbox_33_stateChanged(int arg1);
    void on_konf_checkbox_34_stateChanged(int arg1);
    void on_konf_checkbox_41_stateChanged(int arg1);
    void on_konf_checkbox_42_stateChanged(int arg1);
    void on_konf_checkbox_43_stateChanged(int arg1);
    void on_konf_checkbox_44_stateChanged(int arg1);
    void on_btnponfpolacz_przywroc_clicked();
    void on_toolButton_clicked();
    void on_btn_devinitialize_clicked();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void on_btn_hide_clicked();
    void on_btn_loadconf_1_clicked();
    void on_btn_saveconf_1_clicked();
    void on_btn_loadconf_2_clicked();
    void on_btn_saveconf_2_clicked();
    void on_btn_loadconf_3_clicked();
    void on_btn_saveconf_3_clicked();
    void on_btn_loadconf_4_clicked();
    void on_btn_saveconf_4_clicked();
    void on_btn_loadconf_5_clicked();
    void on_btn_saveconf_5_clicked();
    void on_btn_loadconf_6_clicked();
    void on_btn_saveconf_6_clicked();
    void on_btn_loadconf_7_clicked();
    void on_btn_saveconf_7_clicked();
    void on_btn_loadconf_8_clicked();
    void on_btn_saveconf_8_clicked();
    void on_btn_loadconf_9_clicked();
    void on_btn_saveconf_9_clicked();
    void on_btn_loadconf_10_clicked();
    void on_btn_saveconf_10_clicked();
    void on_btn_devinitialize2_clicked();
    void on_btn_uartconfig_connect_clicked();
    void on_btn_uartconfig_disconnect_clicked();

private:
    bool connectionstatus = false;

    Ui::MainWindow *ui;
    QSerialPort *mSerialPort;

    IO *io;
    DeviceConfig *devconf[10];
    Serial *sp;
    ExecuteCommand *ec;
    QSystemTrayIcon *mSystemTrayIcon;
    int IndexCurrentConfig;

    void UpdateCommunicationProfileLables();
    void Updatedevconf(int id);
    void SetUARTConnectionConfig();
    void CheckCommand(std::string command);
    void SetVirtualButtons(DeviceConfig dc);
    void FillConfigFields();
    void SetConfigFields();
    void FillComandsFields();
    void SetCommandsFields();
    void SetConnectionStatusLabel(bool status);
    void UARTDisconnect();
    void UARTConnect();
    void AddConfigFielsCommands();
    void UARTwriteError();
};

#endif // MAINWINDOW_H
