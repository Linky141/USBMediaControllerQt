#ifndef COMMANDS_H
#define COMMANDS_H

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

class Commands
{
private:
    std::string command;
    std::string description;

public:
    Commands();
    Commands(std::string com, std::string des);


    void set_command(std::string val) {command = val;}
    void set_description(std::string val) {command = val;}
    std::string get_command() {return command;}
    std::string get_description() {return description;}
};

#endif // COMMANDS_H
