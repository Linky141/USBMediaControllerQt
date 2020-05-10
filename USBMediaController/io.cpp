#include "io.h"

IO::IO()
{

}


void IO::odczyt(DeviceConfig *devconf[], Serial &sp, int &index)
{
    odczyt_config(sp);

    std::ifstream f("C:\\USBMediaController\\DevConf.bin");

    try {

    if (f.good())
    {
        char description_buffer[100];
        char executecommand_buffer[100];
        char incommand_buffer[100];
        char idbuffer[100];
        char bufferetykieta[100];
        std::ifstream myFile("C:\\USBMediaController\\DevConf.bin", std::ios::in | std::ios::binary);

        if (!myFile.read(idbuffer, 100));
        index = atoi(idbuffer);

        for(int setting=0;setting<10;setting++)
        {
            if (!myFile.read(bufferetykieta, 100));
            devconf[setting]->set_etykieta(bufferetykieta);

            for (int clk = 0; clk < 4; clk++)
            {
                if (!myFile.read(description_buffer, 100));
                if (!myFile.read(executecommand_buffer, 100));
                if (!myFile.read(incommand_buffer, 100));

                Option *temp = new Option(incommand_buffer, description_buffer, executecommand_buffer);
                devconf[setting]->set_page1(clk, temp);
            }

            for (int clk = 0; clk < 4; clk++)
            {
                if (!myFile.read(description_buffer, 100));
                if (!myFile.read(executecommand_buffer, 100));
                if (!myFile.read(incommand_buffer, 100));

                Option *temp = new Option(incommand_buffer, description_buffer, executecommand_buffer);
                devconf[setting]->set_page2(clk, temp);
            }

            for (int clk = 0; clk < 4; clk++)
            {
                if (!myFile.read(description_buffer, 100));
                if (!myFile.read(executecommand_buffer, 100));
                if (!myFile.read(incommand_buffer, 100));

                Option *temp = new Option(incommand_buffer, description_buffer, executecommand_buffer);
                devconf[setting]->set_page3(clk, temp);
            }

            for (int clk = 0; clk < 4; clk++)
            {
                if (!myFile.read(description_buffer, 100));
                if (!myFile.read(executecommand_buffer, 100));
                if (!myFile.read(incommand_buffer, 100));

                Option *temp = new Option(incommand_buffer, description_buffer, executecommand_buffer);
                devconf[setting]->set_page4(clk, temp);
            }
        }
    }
    else
    {
        printf("BRAK PLIKU\n");
    }
    } catch (std::exception const& e) {
        std::cout<<"Exception!:\n"<<e.what()<<"\n";
    }

    std::cout << "ODCZYT DANYCH ZAKONCZONY POWODZENIEM!\n";
}

void IO::odczyt_config(Serial &sp)
{
    std::ifstream cfg_file("C:\\USBMediaController\\ConnConf.bin");

    if (cfg_file.good())
    {
        system("cls");
        std::cout << "ODCZYTYWANIE KONFIGU\n";

        char port_buffer[100];
        char baudrate_buffer[100];
        char parity_buffer[100];
        char byte_size_buffer[100];
        char stop_bits_buffer[100];
        char dtr_control_buffer[100];
        std::ifstream myFile("C:\\USBMediaController\\ConnConf.bin", std::ios::in | std::ios::binary);

        if (!myFile.read(port_buffer, 100));
        if (!myFile.read(baudrate_buffer, 100));
        if (!myFile.read(parity_buffer, 100));
        if (!myFile.read(byte_size_buffer, 100));
        if (!myFile.read(stop_bits_buffer, 100));
        if (!myFile.read(dtr_control_buffer, 100));

        sp.set_portnumber(atoi(port_buffer));
        sp.set_baudrate(baudrate_buffer);
        sp.set_parity(parity_buffer);
        sp.set_bytesize(byte_size_buffer);
        sp.set_stopbits(stop_bits_buffer);
        sp.set_dtrcontrol(dtr_control_buffer);


        std::cout << "PORT:" << sp.get_portname() << "\n";
        std::cout << "BAUDRATE:" << sp.get_baudrate() << "\n";
        std::cout << "PARITY:" << sp.get_parity() << "\n";
        std::cout << "BYTE SIZE:" << sp.get_bytesize() << "\n";
        std::cout << "STOP BITS:" << sp.get_stopbits() << "\n";
        std::cout << "DTR:" << sp.get_dtrcontrol() << "\n";
    }
}

void IO::zapisz(DeviceConfig *devconf[], Serial &sp, int &index)
{
    zapisz_config(sp);

    std::ofstream file("C:\\USBMediaController\\DevConf.bin", std::ios::out | std::ios::binary);

    if (file.good() == true)
    {
        std::cout << "Uzyskano dostep do pliku!" << std::endl;

        char num_buffer[100];
        itoa(index, num_buffer, 10);
        file.write(num_buffer, 100);


        for(int setting=0;setting<10;setting++)
        {
            file.write(devconf[setting]->get_etykieta().c_str(), 100);

            for (int clk = 0; clk < 4; clk++)
            {
                file.write(devconf[setting]->get_page1(clk).get_description().c_str(), 100);
                file.write(devconf[setting]->get_page1(clk).get_executecommand().c_str(), 100);
                file.write(devconf[setting]->get_page1(clk).get_incommand().c_str(), 100);
            }
            for (int clk = 0; clk < 4; clk++)
            {
                file.write(devconf[setting]->get_page2(clk).get_description().c_str(), 100);
                file.write(devconf[setting]->get_page2(clk).get_executecommand().c_str(), 100);
                file.write(devconf[setting]->get_page2(clk).get_incommand().c_str(), 100);
            }
            for (int clk = 0; clk < 4; clk++)
            {
                file.write(devconf[setting]->get_page3(clk).get_description().c_str(), 100);
                file.write(devconf[setting]->get_page3(clk).get_executecommand().c_str(), 100);
                file.write(devconf[setting]->get_page3(clk).get_incommand().c_str(), 100);
            }
            for (int clk = 0; clk < 4; clk++)
            {
                file.write(devconf[setting]->get_page4(clk).get_description().c_str(), 100);
                file.write(devconf[setting]->get_page4(clk).get_executecommand().c_str(), 100);
                file.write(devconf[setting]->get_page4(clk).get_incommand().c_str(), 100);
            }
        }
    }
    else std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;
}

void IO::zapisz_config(Serial &sp)
{
    std::ofstream cfgfile("C:\\USBMediaController\\ConnConf.bin", std::ios::out | std::ios::binary);

    if (cfgfile.good() == true)
    {
        std::cout << "Uzyskano dostep do pliku konfiguracyjnego!\nTRWA ZAPIS!" << std::endl;

        char num_buffer[100];
        itoa(sp.get_portnumber(), num_buffer, 10);

        cfgfile.write(num_buffer, 100);
        cfgfile.write(sp.get_baudrate().c_str(), 100);
        cfgfile.write(sp.get_parity().c_str(), 100);
        cfgfile.write(sp.get_bytesize().c_str(), 100);
        cfgfile.write(sp.get_stopbits().c_str(), 100);
        cfgfile.write(sp.get_dtrcontrol().c_str(), 100);

        std::cout << "\nZAPIS ZAKONCZONY!" << std::endl;
    }
}
