#ifndef SERIALCLASS_H_INCLUDED
#define SERIALCLASS_H_INCLUDED

#define ARDUINO_WAIT_TIME 2000

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

class QSerialPort;

namespace Ui
{
class Serial;
}

class Serial
{
private:

    std::string portName;
    int portnumber;
    std::string baudrate;
    std::string parity;
    std::string byteSize;
    std::string stopBits;
    std::string dtrControl;


public:
   Serial();
   Serial(int pn, std::string ba, std::string pa, std::string bs, std::string sb, std::string dc);

   void set_portnumber(int val) {portnumber = val; portName = "COM" + std::to_string(val);}
   void set_baudrate(std::string val) {baudrate = val;}
   void set_parity(std::string val) {parity = val;}
   void set_bytesize(std::string val) {byteSize = val;}
   void set_stopbits(std::string val) {stopBits = val;}
   void set_dtrcontrol(std::string val) {dtrControl = val;}


   std::string get_portname() {return portName;}
   int get_portnumber() {return portnumber;}
   std::string get_baudrate() {return baudrate;}
   std::string get_parity() {return parity;}
   std::string get_bytesize() {return byteSize;}
   std::string get_stopbits() {return stopBits;}
   std::string get_dtrcontrol() {return dtrControl;}
};

#endif // SERIALPORT_H
