#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <tchar.h>
#include "SerialPort.h"
#include "Options.h"
#include "deviceconfig.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <fstream>


class IO
{
public:
    IO();
    void odczyt(DeviceConfig *devconf[], Serial &sp, int &index);
    void odczyt_config(Serial &sp);
    void zapisz(DeviceConfig *devconf[], Serial &sp, int &index);
    void zapisz_config(Serial &sp);
};

#endif // IO_H
