#include "deviceconfig.h"

DeviceConfig::DeviceConfig()
{
    etykieta = "Puste";

    page1[0] = new Option("aa11", "----   \n", "---");
    page1[1] = new Option("aa22", "----   \n", "---");
    page1[2] = new Option("aa33", "----   \n", "---");
    page1[3] = new Option("aa44", "----   \n", "---");

    page2[0] = new Option("bb11", "----   \n", "---");
    page2[1] = new Option("bb22", "----   \n", "---");
    page2[2] = new Option("bb33", "----   \n", "---");
    page2[3] = new Option("bb44", "----   \n", "---");

    page3[0] = new Option("cc11", "----   \n", "---");
    page3[1] = new Option("cc22", "----   \n", "---");
    page3[2] = new Option("cc33", "----   \n", "---");
    page3[3] = new Option("cc44", "----   \n", "---");

    page4[0] = new Option("dd11", "----   \n", "---");
    page4[1] = new Option("dd22", "----   \n", "---");
    page4[2] = new Option("dd33", "----   \n", "---");
    page4[3] = new Option("dd44", "----   \n", "---");
}


DeviceConfig::DeviceConfig(Option *p1[4], Option *p2[4], Option *p3[4], Option *p4[4], std::string et)
{
    etykieta = et;
    for(int clk=0;clk<4;clk++) page1[clk] = p1[clk];
    for(int clk=0;clk<4;clk++) page2[clk] = p2[clk];
    for(int clk=0;clk<4;clk++) page3[clk] = p3[clk];
    for(int clk=0;clk<4;clk++) page4[clk] = p4[clk];

}



