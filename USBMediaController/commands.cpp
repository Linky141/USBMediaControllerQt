#include "commands.h"

Commands::Commands()
    :command(""), description("")
{}

Commands::Commands(std::string com, std::string des)
    :command(com), description(des)
{}
