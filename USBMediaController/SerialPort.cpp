#include "SerialPort.h"


Serial::Serial()
    :portName(""), baudrate(""), parity(""), byteSize(""), stopBits(""), dtrControl(""), portnumber(0)
{}


Serial::Serial(int pn, std::string ba, std::string pa, std::string bs, std::string sb, std::string dc)
    :portName("\\\\.\\COM" + pn), baudrate(ba), parity(pa), byteSize(bs), stopBits(sb), dtrControl(dc), portnumber(pn)
{}
