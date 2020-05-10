#include "mainwindow.h"
#include <QApplication>
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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    MainWindow w;

    return a.exec();
}
