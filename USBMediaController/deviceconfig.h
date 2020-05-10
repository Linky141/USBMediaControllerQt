#ifndef DEVICECONFIG_H
#define DEVICECONFIG_H

#include "Options.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <fstream>

class DeviceConfig
{
private:
    Option *page1[4];
    Option *page2[4];
    Option *page3[4];
    Option *page4[4];
    std::string etykieta;

public:
    DeviceConfig();
    DeviceConfig(Option *p1[4], Option *p2[4], Option *p3[4], Option *p4[4], std::string et);

    Option get_page1(int num) {return *page1[num];}
    Option get_page2(int num) {return *page2[num];}
    Option get_page3(int num) {return *page3[num];}
    Option get_page4(int num) {return *page4[num];}

    Option* get_page1() {return *page1;}
    Option* get_page2() {return *page2;}
    Option* get_page3() {return *page3;}
    Option* get_page4() {return *page4;}
    std::string get_etykieta() {return etykieta;}

    void set_page1(int num, Option *opt) {page1[num] = opt;}
    void set_page2(int num, Option *opt) {page2[num] = opt;}
    void set_page3(int num, Option *opt) {page3[num] = opt;}
    void set_page4(int num, Option *opt) {page4[num] = opt;}
    void set_etykieta(std::string val) {etykieta = val;}
};

#endif // DEVICECONFIG_H
