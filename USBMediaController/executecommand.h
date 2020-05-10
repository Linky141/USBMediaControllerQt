#ifndef EXECUTECOMMAND_H
#define EXECUTECOMMAND_H

#include "SerialPort.h"
#include "Options.h"
#include <Windows.h>
#include <vector>
#include "commands.h"

class ExecuteCommand
{
private:
    std::vector<Commands> commands;

public:
    ExecuteCommand();
    ExecuteCommand(std::vector<Commands> com);

    void Execute(std::string command);

    void AddCommand(std::string com, std::string des);

    std::vector<Commands> GetCommands();

    Commands GetCommand(int num);

    std::string GetCommand(std::string com);

    void ClearCommands();

    int get_length();
};

#endif // EXECUTECOMMAND_H
