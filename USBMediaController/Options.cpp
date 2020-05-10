#include "Options.h"

Option::Option(std::string in, std::string name, std::string out)
    :in_command(in), description(name), execute_command(out)
{}

Option::Option()
    : in_command(""), description(""), execute_command("")
{}
