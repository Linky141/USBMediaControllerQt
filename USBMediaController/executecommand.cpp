#include "executecommand.h"

ExecuteCommand::ExecuteCommand()
{
    commands.clear();
}

ExecuteCommand::ExecuteCommand(std::vector<Commands> com)
{
    commands.clear();
    commands = com;
}


void ExecuteCommand::Execute(std::string command)
{
    INPUT ip;
    ip.type = INPUT_KEYBOARD;

    if (command == "volumeup") ip.ki.wVk = VK_VOLUME_UP;
    else if (command == "volumedown") ip.ki.wVk = VK_VOLUME_DOWN;
    else if (command == "volumemute") ip.ki.wVk = VK_VOLUME_MUTE;
    else if (command == "medianext") ip.ki.wVk = VK_MEDIA_NEXT_TRACK;
    else if (command == "medialast") ip.ki.wVk = VK_MEDIA_PREV_TRACK;
    else if (command == "mediaplay") ip.ki.wVk = VK_MEDIA_PLAY_PAUSE;
    else if (command == "mediastop") ip.ki.wVk = VK_MEDIA_STOP;
    else if (command == "mediaselect") ip.ki.wVk = VK_LAUNCH_MEDIA_SELECT;
    else if (command == "closewindow")
    {
        keybd_event(VK_MENU, 0, 0, 0);
        keybd_event(VK_F4, 0, 0, 0);
        Sleep(50);
        keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
        keybd_event(VK_F4, 0, KEYEVENTF_KEYUP, 0);
    }
    else if (command == "") {}
    else if (command == "") {}
    else
    {
        system(command.c_str());
        return;
    }
    SendInput(1, &ip, sizeof(INPUT));
    ip.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &ip, sizeof(INPUT));
    return;

}


void ExecuteCommand::AddCommand(std::string com, std::string des)
{
    Commands *temp = new Commands(com, des);
    commands.push_back(*temp);
}

std::vector<Commands> ExecuteCommand::GetCommands()
{
    return commands;
}

Commands ExecuteCommand::GetCommand(int num)
{
    if(num<=(int)commands.max_size()) return commands.at(num);

    Commands x;
    return x;
}

void ExecuteCommand::ClearCommands()
{
    commands.clear();
}

int ExecuteCommand::get_length()
{
    return commands.size();
}


std::string ExecuteCommand::GetCommand(std::string com)
{
    for(int clk=0;clk<commands.size();clk++)
    {
        if(com == commands[clk].get_description()) return commands[clk].get_command();
    }
    return "Fail";
}
