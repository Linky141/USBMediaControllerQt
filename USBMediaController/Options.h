#ifndef OPTIONS_H
#define OPTIONS_H

#include <string>

class Option
{
private:
    std::string in_command;
    std::string description;
    std::string execute_command;
public:
    Option(std::string in, std::string name, std::string out);
    Option();

    std::string get_incommand() { return in_command; }
    std::string get_description() { return description; }
    std::string get_executecommand() { return execute_command; }

    void set_incommand(std::string val) { in_command = val; }
    void set_description(std::string val) { description = val; }
    void set_executecommand(std::string val) { execute_command = val; }
};

#endif // OPTIONS_H
