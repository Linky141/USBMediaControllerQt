#include "mainwindow.h"
#include "ui_mainwindow.h"




//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
//Inicjalizacja i tworzenie

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    io(new IO()),
    sp(new Serial()),
    ec(new ExecuteCommand()),
    mSerialPort(new QSerialPort(this))
{
    for(int clk=0;clk<10;clk++) devconf[clk] = new DeviceConfig();

    ui->setupUi(this);
    SetConnectionStatusLabel(false);
    mSystemTrayIcon = new QSystemTrayIcon(this);
    mSystemTrayIcon->setIcon(QIcon(":/myappico.png"));
    mSystemTrayIcon->setVisible(true);
    connect(mSystemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    FillConfigFields();
    FillComandsFields();

    io->odczyt(devconf, *sp, IndexCurrentConfig);
    SetVirtualButtons(*devconf[IndexCurrentConfig]);
    SetConfigFields();
    SetCommandsFields();

    connect(mSerialPort, SIGNAL(readyRead()), this, SLOT(readSerialData()));
    SetUARTConnectionConfig();
    on_btn_connect_clicked();
    UARTWriteLables();
    UpdateCommunicationProfileLables();
}

MainWindow::~MainWindow()
{
    delete mSerialPort;
    delete ui;
}

void MainWindow::SetUARTConnectionConfig()
{
    mSerialPort->setPortName(QString::fromStdString(sp->get_portname()));

    if (sp->get_baudrate() == "1200")mSerialPort->setBaudRate(QSerialPort::Baud1200);
    else if (sp->get_baudrate() == "2400")mSerialPort->setBaudRate(QSerialPort::Baud2400);
    else if (sp->get_baudrate() == "4800")mSerialPort->setBaudRate(QSerialPort::Baud4800);
    else if (sp->get_baudrate() == "9600")mSerialPort->setBaudRate(QSerialPort::Baud9600);
    else if (sp->get_baudrate() == "19200")mSerialPort->setBaudRate(QSerialPort::Baud19200);
    else if (sp->get_baudrate() == "38400")mSerialPort->setBaudRate(QSerialPort::Baud38400);
    else if (sp->get_baudrate() == "57600")mSerialPort->setBaudRate(QSerialPort::Baud57600);
    else if (sp->get_baudrate() == "115200")mSerialPort->setBaudRate(QSerialPort::Baud115200);
    else mSerialPort->setBaudRate(QSerialPort::Baud9600);

    if (sp->get_bytesize() == "7")mSerialPort->setDataBits(QSerialPort::Data7);
    else if (sp->get_bytesize() == "8")mSerialPort->setDataBits(QSerialPort::Data8);
    else mSerialPort->setDataBits(QSerialPort::Data8);

    if (sp->get_parity() == "NOPARITY")mSerialPort->setParity(QSerialPort::NoParity);
    else if (sp->get_parity() == "ODDPARITY")mSerialPort->setParity(QSerialPort::OddParity);
    else if (sp->get_parity() == "EVENPARITY")mSerialPort->setParity(QSerialPort::EvenParity);
    else if (sp->get_parity() == "MARKPARITY")mSerialPort->setParity(QSerialPort::MarkParity);
    else if (sp->get_parity() == "SPACEPARITY")mSerialPort->setParity(QSerialPort::SpaceParity);
    else mSerialPort->setParity(QSerialPort::NoParity);

    if (sp->get_stopbits() == "ONESTOPBIT")mSerialPort->setStopBits(QSerialPort::OneStop);
    else if (sp->get_stopbits() == "ONE5STOPBITS")mSerialPort->setStopBits(QSerialPort::OneAndHalfStop);
    else if (sp->get_stopbits() == "TWOSTOPBITS")mSerialPort->setStopBits(QSerialPort::TwoStop);
    else mSerialPort->setStopBits(QSerialPort::OneStop);

    if (sp->get_dtrcontrol() == "NoFlowControl")mSerialPort->setFlowControl(QSerialPort::NoFlowControl);
    else if (sp->get_dtrcontrol() == "HardwareControl")mSerialPort->setFlowControl(QSerialPort::HardwareControl);
    else if (sp->get_dtrcontrol() == "SoftwareControl")mSerialPort->setFlowControl(QSerialPort::SoftwareControl);
    else mSerialPort->setFlowControl(QSerialPort::NoFlowControl);
}

void MainWindow::Updatedevconf(int id)
{
    //strona 1 pozycja 1
    if(ui->konf_checkbox_11->checkState() == Qt::CheckState::Checked)
    {
        Option *temp = new Option("aa11", ui->konf_tbx_11->text().toStdString(), ui->konf_command_tbx_11->text().toStdString());
        devconf[id]->set_page1(0, temp);
    }
    else
    {
        Option *temp = new Option("aa11", ui->konf_tbx_11->text().toStdString(), ec->GetCommand(ui->konf_command_cbx_11->currentText().toStdString()));
        devconf[id]->set_page1(0, temp);
    }

    //strona 1 pozycja 2
    if(ui->konf_checkbox_12->checkState() == Qt::CheckState::Checked)
    {
        Option *temp = new Option("aa12", ui->konf_tbx_12->text().toStdString(), ui->konf_command_tbx_12->text().toStdString());
        devconf[id]->set_page1(1, temp);
    }
    else
    {
        Option *temp = new Option("aa12", ui->konf_tbx_12->text().toStdString(), ec->GetCommand(ui->konf_command_cbx_12->currentText().toStdString()));
        devconf[id]->set_page1(1, temp);
    }

    //strona 1 pozycja 3
    if(ui->konf_checkbox_13->checkState() == Qt::CheckState::Checked)
    {
        Option *temp = new Option("aa13", ui->konf_tbx_13->text().toStdString(), ui->konf_command_tbx_13->text().toStdString());
        devconf[id]->set_page1(2, temp);
    }
    else
    {
        Option *temp = new Option("aa13", ui->konf_tbx_13->text().toStdString(), ec->GetCommand(ui->konf_command_cbx_13->currentText().toStdString()));
        devconf[id]->set_page1(2, temp);
    }

    //strona 1 pozycja 4
    if(ui->konf_checkbox_14->checkState() == Qt::CheckState::Checked)
    {
        Option *temp = new Option("aa14", ui->konf_tbx_14->text().toStdString(), ui->konf_command_tbx_14->text().toStdString());
        devconf[id]->set_page1(3, temp);
    }
    else
    {
        Option *temp = new Option("aa14", ui->konf_tbx_14->text().toStdString(), ec->GetCommand(ui->konf_command_cbx_14->currentText().toStdString()));
        devconf[id]->set_page1(3, temp);
    }

    //strona 2 pozycja 1
    if(ui->konf_checkbox_21->checkState() == Qt::CheckState::Checked)
    {
        Option *temp = new Option("aa21", ui->konf_tbx_21->text().toStdString(), ui->konf_command_tbx_21->text().toStdString());
        devconf[id]->set_page2(0, temp);
    }
    else
    {
        Option *temp = new Option("aa21", ui->konf_tbx_21->text().toStdString(), ec->GetCommand(ui->konf_command_cbx_21->currentText().toStdString()));
        devconf[id]->set_page2(0, temp);
    }

    //strona 2 pozycja 2
    if(ui->konf_checkbox_22->checkState() == Qt::CheckState::Checked)
    {
        Option *temp = new Option("aa22", ui->konf_tbx_22->text().toStdString(), ui->konf_command_tbx_22->text().toStdString());
        devconf[id]->set_page2(1, temp);
    }
    else
    {
        Option *temp = new Option("aa22", ui->konf_tbx_22->text().toStdString(), ec->GetCommand(ui->konf_command_cbx_22->currentText().toStdString()));
        devconf[id]->set_page2(1, temp);
    }

    //strona 2 pozycja 3
    if(ui->konf_checkbox_23->checkState() == Qt::CheckState::Checked)
    {
        Option *temp = new Option("aa23", ui->konf_tbx_23->text().toStdString(), ui->konf_command_tbx_23->text().toStdString());
        devconf[id]->set_page2(2, temp);
    }
    else
    {
        Option *temp = new Option("aa23", ui->konf_tbx_23->text().toStdString(), ec->GetCommand(ui->konf_command_cbx_23->currentText().toStdString()));
        devconf[id]->set_page2(2, temp);
    }

    //strona 2 pozycja 4
    if(ui->konf_checkbox_24->checkState() == Qt::CheckState::Checked)
    {
        Option *temp = new Option("aa24", ui->konf_tbx_24->text().toStdString(), ui->konf_command_tbx_24->text().toStdString());
        devconf[id]->set_page2(3, temp);
    }
    else
    {
        Option *temp = new Option("aa24", ui->konf_tbx_24->text().toStdString(), ec->GetCommand(ui->konf_command_cbx_24->currentText().toStdString()));
        devconf[id]->set_page2(3, temp);
    }

    //strona 3 pozycja 1
    if(ui->konf_checkbox_31->checkState() == Qt::CheckState::Checked)
    {
        Option *temp = new Option("aa31", ui->konf_tbx_31->text().toStdString(), ui->konf_command_tbx_31->text().toStdString());
        devconf[id]->set_page3(0, temp);
    }
    else
    {
        Option *temp = new Option("aa31", ui->konf_tbx_31->text().toStdString(), ec->GetCommand(ui->konf_command_cbx_31->currentText().toStdString()));
        devconf[id]->set_page3(0, temp);
    }

    //strona 3 pozycja 2
    if(ui->konf_checkbox_32->checkState() == Qt::CheckState::Checked)
    {
        Option *temp = new Option("aa32", ui->konf_tbx_32->text().toStdString(), ui->konf_command_tbx_32->text().toStdString());
        devconf[id]->set_page3(1, temp);
    }
    else
    {
        Option *temp = new Option("aa32", ui->konf_tbx_32->text().toStdString(), ec->GetCommand(ui->konf_command_cbx_32->currentText().toStdString()));
        devconf[id]->set_page3(1, temp);
    }

    //strona 3 pozycja 3
    if(ui->konf_checkbox_33->checkState() == Qt::CheckState::Checked)
    {
        Option *temp = new Option("aa33", ui->konf_tbx_33->text().toStdString(), ui->konf_command_tbx_33->text().toStdString());
        devconf[id]->set_page3(2, temp);
    }
    else
    {
        Option *temp = new Option("aa33", ui->konf_tbx_33->text().toStdString(), ec->GetCommand(ui->konf_command_cbx_33->currentText().toStdString()));
        devconf[id]->set_page3(2, temp);
    }

    //strona 3 pozycja 4
    if(ui->konf_checkbox_34->checkState() == Qt::CheckState::Checked)
    {
        Option *temp = new Option("aa34", ui->konf_tbx_34->text().toStdString(), ui->konf_command_tbx_34->text().toStdString());
        devconf[id]->set_page3(3, temp);
    }
    else
    {
        Option *temp = new Option("aa34", ui->konf_tbx_34->text().toStdString(), ec->GetCommand(ui->konf_command_cbx_34->currentText().toStdString()));
        devconf[id]->set_page3(3, temp);
    }

    //strona 4 pozycja 1
    if(ui->konf_checkbox_41->checkState() == Qt::CheckState::Checked)
    {
        Option *temp = new Option("aa41", ui->konf_tbx_41->text().toStdString(), ui->konf_command_tbx_41->text().toStdString());
        devconf[id]->set_page4(0, temp);
    }
    else
    {
        Option *temp = new Option("aa41", ui->konf_tbx_41->text().toStdString(), ec->GetCommand(ui->konf_command_cbx_41->currentText().toStdString()));
        devconf[id]->set_page4(0, temp);
    }

    //strona 4 pozycja 2
    if(ui->konf_checkbox_42->checkState() == Qt::CheckState::Checked)
    {
        Option *temp = new Option("aa42", ui->konf_tbx_42->text().toStdString(), ui->konf_command_tbx_42->text().toStdString());
        devconf[id]->set_page4(1, temp);
    }
    else
    {
        Option *temp = new Option("aa42", ui->konf_tbx_42->text().toStdString(), ec->GetCommand(ui->konf_command_cbx_42->currentText().toStdString()));
        devconf[id]->set_page4(1, temp);
    }

    //strona 4 pozycja 3
    if(ui->konf_checkbox_43->checkState() == Qt::CheckState::Checked)
    {
        Option *temp = new Option("aa43", ui->konf_tbx_43->text().toStdString(), ui->konf_command_tbx_43->text().toStdString());
        devconf[id]->set_page4(2, temp);
    }
    else
    {
        Option *temp = new Option("aa43", ui->konf_tbx_43->text().toStdString(), ec->GetCommand(ui->konf_command_cbx_43->currentText().toStdString()));
        devconf[id]->set_page4(2, temp);
    }

    //strona 4 pozycja 4
    if(ui->konf_checkbox_44->checkState() == Qt::CheckState::Checked)
    {
        Option *temp = new Option("aa44", ui->konf_tbx_44->text().toStdString(), ui->konf_command_tbx_44->text().toStdString());
        devconf[id]->set_page4(3, temp);
    }
    else
    {
        Option *temp = new Option("aa44", ui->konf_tbx_44->text().toStdString(), ec->GetCommand(ui->konf_command_cbx_44->currentText().toStdString()));
        devconf[id]->set_page4(3, temp);
    }

    io->zapisz(devconf, *sp, IndexCurrentConfig);
}

void MainWindow::AddConfigFielsCommands()
{
    ec->AddCommand("volumeup","Volume UP");
    ec->AddCommand("volumedown","Volume DOWN");
    ec->AddCommand("volumemute","Mute");
    ec->AddCommand("medianext","Next track");
    ec->AddCommand("medialast","Last track");
    ec->AddCommand("mediaplay","Play / pause");
    ec->AddCommand("mediastop","Stop");
    ec->AddCommand("mediaselect","Open media select");
    ec->AddCommand("closewindow","Close");
}



//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
//Wypełnianie elementów gui


void MainWindow::SetConfigFields()
{
    ui->portcfg_parity->setCurrentText(QString::fromStdString(sp->get_parity()));
    ui->portcfg_baudrate->setCurrentText(QString::fromStdString(sp->get_baudrate()));
    ui->portcfg_bytesize->setCurrentText(QString::fromStdString(sp->get_bytesize()));
    ui->portcfg_stopbits->setCurrentText(QString::fromStdString(sp->get_stopbits()));
    ui->portcfg_dtrcontrol->setCurrentText(QString::fromStdString(sp->get_dtrcontrol()));
    ui->portcfg_numerportu->setValue(sp->get_portnumber());
}

void MainWindow::SetCommandsFields()
{
    bool gate;

    //Strona 1 pozycja 1
    gate = false;
    for(int clk=0;clk<ec->get_length() && gate == false;clk++)
    {
        if(devconf[IndexCurrentConfig]->get_page1(0).get_executecommand() == ec->GetCommand(clk).get_command())
        {
            ui->konf_tbx_11->setEnabled(true);
            ui->konf_checkbox_11->setChecked(false);
            ui->konf_command_cbx_11->setEnabled(true);
            ui->konf_command_tbx_11->setEnabled(false);
            ui->konf_tbx_11->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page1(0).get_description()));
            ui->konf_command_cbx_11->setCurrentText(QString::fromStdString(ec->GetCommand(clk).get_description()));
            gate = true;
        }
    }
    if(gate == false)
    {
        ui->konf_tbx_11->setEnabled(true);
        ui->konf_checkbox_11->setChecked(true);
        ui->konf_command_cbx_11->setEnabled(false);
        ui->konf_command_tbx_11->setEnabled(true);
        ui->konf_tbx_11->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page1(0).get_description()));
        ui->konf_command_tbx_11->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page1(0).get_executecommand()));
    }

    //Strona 1 pozycja 2
   gate = false;
   for(int clk=0;clk<ec->get_length() && gate == false;clk++)
   {
       if(devconf[IndexCurrentConfig]->get_page1(1).get_executecommand() == ec->GetCommand(clk).get_command())
       {
           ui->konf_tbx_12->setEnabled(true);
           ui->konf_checkbox_12->setChecked(false);
           ui->konf_command_cbx_12->setEnabled(true);
           ui->konf_command_tbx_12->setEnabled(false);
           ui->konf_tbx_12->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page1(1).get_description()));
           ui->konf_command_cbx_12->setCurrentText(QString::fromStdString(ec->GetCommand(clk).get_description()));
           gate = true;
       }
   }
   if(gate == false)
   {
       ui->konf_tbx_12->setEnabled(true);
       ui->konf_checkbox_12->setChecked(true);
       ui->konf_command_cbx_12->setEnabled(false);
       ui->konf_command_tbx_12->setEnabled(true);
       ui->konf_tbx_12->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page1(1).get_description()));
       ui->konf_command_tbx_12->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page1(1).get_executecommand()));
   }

   //Strona 1 pozycja 3
  gate = false;
  for(int clk=0;clk<ec->get_length() && gate == false;clk++)
  {
      if(devconf[IndexCurrentConfig]->get_page1(2).get_executecommand() == ec->GetCommand(clk).get_command())
      {
          ui->konf_tbx_13->setEnabled(true);
          ui->konf_checkbox_13->setChecked(false);
          ui->konf_command_cbx_13->setEnabled(true);
          ui->konf_command_tbx_13->setEnabled(false);
          ui->konf_tbx_13->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page1(2).get_description()));
          ui->konf_command_cbx_13->setCurrentText(QString::fromStdString(ec->GetCommand(clk).get_description()));
          gate = true;
      }
  }
  if(gate == false)
  {
      ui->konf_tbx_13->setEnabled(true);
      ui->konf_checkbox_13->setChecked(true);
      ui->konf_command_cbx_13->setEnabled(false);
      ui->konf_command_tbx_13->setEnabled(true);
      ui->konf_tbx_13->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page1(2).get_description()));
      ui->konf_command_tbx_13->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page1(2).get_executecommand()));
  }

  //Strona 1 pozycja 4
 gate = false;
 for(int clk=0;clk<ec->get_length() && gate == false;clk++)
 {
     if(devconf[IndexCurrentConfig]->get_page1(3).get_executecommand() == ec->GetCommand(clk).get_command())
     {
         ui->konf_tbx_14->setEnabled(true);
         ui->konf_checkbox_14->setChecked(false);
         ui->konf_command_cbx_14->setEnabled(true);
         ui->konf_command_tbx_14->setEnabled(false);
         ui->konf_tbx_14->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page1(3).get_description()));
         ui->konf_command_cbx_14->setCurrentText(QString::fromStdString(ec->GetCommand(clk).get_description()));
         gate = true;
     }
 }
 if(gate == false)
 {
     ui->konf_tbx_14->setEnabled(true);
     ui->konf_checkbox_14->setChecked(true);
     ui->konf_command_cbx_14->setEnabled(false);
     ui->konf_command_tbx_14->setEnabled(true);
     ui->konf_tbx_14->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page1(3).get_description()));
     ui->konf_command_tbx_14->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page1(3).get_executecommand()));
 }

 //Strona 2 pozycja 1
 gate = false;
 for(int clk=0;clk<ec->get_length() && gate == false;clk++)
 {
     if(devconf[IndexCurrentConfig]->get_page2(0).get_executecommand() == ec->GetCommand(clk).get_command())
     {
         ui->konf_tbx_21->setEnabled(true);
         ui->konf_checkbox_21->setChecked(false);
         ui->konf_command_cbx_21->setEnabled(true);
         ui->konf_command_tbx_21->setEnabled(false);
         ui->konf_tbx_21->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page2(0).get_description()));
         ui->konf_command_cbx_21->setCurrentText(QString::fromStdString(ec->GetCommand(clk).get_description()));
         gate = true;
     }
 }
 if(gate == false)
 {
     ui->konf_tbx_21->setEnabled(true);
     ui->konf_checkbox_21->setChecked(true);
     ui->konf_command_cbx_21->setEnabled(false);
     ui->konf_command_tbx_21->setEnabled(true);
     ui->konf_tbx_21->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page2(0).get_description()));
     ui->konf_command_tbx_21->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page2(0).get_executecommand()));
 }

 //Strona 2 pozycja 2
gate = false;
for(int clk=0;clk<ec->get_length() && gate == false;clk++)
{
    if(devconf[IndexCurrentConfig]->get_page2(1).get_executecommand() == ec->GetCommand(clk).get_command())
    {
        ui->konf_tbx_22->setEnabled(true);
        ui->konf_checkbox_22->setChecked(false);
        ui->konf_command_cbx_22->setEnabled(true);
        ui->konf_command_tbx_22->setEnabled(false);
        ui->konf_tbx_22->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page2(1).get_description()));
        ui->konf_command_cbx_22->setCurrentText(QString::fromStdString(ec->GetCommand(clk).get_description()));
        gate = true;
    }
}
if(gate == false)
{
    ui->konf_tbx_22->setEnabled(true);
    ui->konf_checkbox_22->setChecked(true);
    ui->konf_command_cbx_22->setEnabled(false);
    ui->konf_command_tbx_22->setEnabled(true);
    ui->konf_tbx_22->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page2(1).get_description()));
    ui->konf_command_tbx_22->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page2(1).get_executecommand()));
}

//Strona 2 pozycja 3
gate = false;
for(int clk=0;clk<ec->get_length() && gate == false;clk++)
{
   if(devconf[IndexCurrentConfig]->get_page2(2).get_executecommand() == ec->GetCommand(clk).get_command())
   {
       ui->konf_tbx_23->setEnabled(true);
       ui->konf_checkbox_23->setChecked(false);
       ui->konf_command_cbx_23->setEnabled(true);
       ui->konf_command_tbx_23->setEnabled(false);
       ui->konf_tbx_23->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page2(2).get_description()));
       ui->konf_command_cbx_23->setCurrentText(QString::fromStdString(ec->GetCommand(clk).get_description()));
       gate = true;
   }
}
if(gate == false)
{
   ui->konf_tbx_23->setEnabled(true);
   ui->konf_checkbox_23->setChecked(true);
   ui->konf_command_cbx_23->setEnabled(false);
   ui->konf_command_tbx_23->setEnabled(true);
   ui->konf_tbx_23->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page2(2).get_description()));
   ui->konf_command_tbx_23->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page2(2).get_executecommand()));
}

//Strona 2 pozycja 4
gate = false;
for(int clk=0;clk<ec->get_length() && gate == false;clk++)
{
  if(devconf[IndexCurrentConfig]->get_page2(3).get_executecommand() == ec->GetCommand(clk).get_command())
  {
      ui->konf_tbx_24->setEnabled(true);
      ui->konf_checkbox_24->setChecked(false);
      ui->konf_command_cbx_24->setEnabled(true);
      ui->konf_command_tbx_24->setEnabled(false);
      ui->konf_tbx_24->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page2(3).get_description()));
      ui->konf_command_cbx_24->setCurrentText(QString::fromStdString(ec->GetCommand(clk).get_description()));
      gate = true;
  }
}
if(gate == false)
{
  ui->konf_tbx_24->setEnabled(true);
  ui->konf_checkbox_24->setChecked(true);
  ui->konf_command_cbx_24->setEnabled(false);
  ui->konf_command_tbx_24->setEnabled(true);
  ui->konf_tbx_24->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page2(3).get_description()));
  ui->konf_command_tbx_24->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page2(3).get_executecommand()));
}

//Strona 3 pozycja 1
gate = false;
for(int clk=0;clk<ec->get_length() && gate == false;clk++)
{
    if(devconf[IndexCurrentConfig]->get_page3(0).get_executecommand() == ec->GetCommand(clk).get_command())
    {
        ui->konf_tbx_31->setEnabled(true);
        ui->konf_checkbox_31->setChecked(false);
        ui->konf_command_cbx_31->setEnabled(true);
        ui->konf_command_tbx_31->setEnabled(false);
        ui->konf_tbx_31->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page3(0).get_description()));
        ui->konf_command_cbx_31->setCurrentText(QString::fromStdString(ec->GetCommand(clk).get_description()));
        gate = true;
    }
}
if(gate == false)
{
    ui->konf_tbx_31->setEnabled(true);
    ui->konf_checkbox_31->setChecked(true);
    ui->konf_command_cbx_31->setEnabled(false);
    ui->konf_command_tbx_31->setEnabled(true);
    ui->konf_tbx_31->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page3(0).get_description()));
    ui->konf_command_tbx_31->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page3(0).get_executecommand()));
}

//Strona 3 pozycja 2
gate = false;
for(int clk=0;clk<ec->get_length() && gate == false;clk++)
{
   if(devconf[IndexCurrentConfig]->get_page3(1).get_executecommand() == ec->GetCommand(clk).get_command())
   {
       ui->konf_tbx_32->setEnabled(true);
       ui->konf_checkbox_32->setChecked(false);
       ui->konf_command_cbx_32->setEnabled(true);
       ui->konf_command_tbx_32->setEnabled(false);
       ui->konf_tbx_32->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page3(1).get_description()));
       ui->konf_command_cbx_32->setCurrentText(QString::fromStdString(ec->GetCommand(clk).get_description()));
       gate = true;
   }
}
if(gate == false)
{
   ui->konf_tbx_32->setEnabled(true);
   ui->konf_checkbox_32->setChecked(true);
   ui->konf_command_cbx_32->setEnabled(false);
   ui->konf_command_tbx_32->setEnabled(true);
   ui->konf_tbx_32->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page3(1).get_description()));
   ui->konf_command_tbx_32->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page3(1).get_executecommand()));
}

//Strona 3 pozycja 3
gate = false;
for(int clk=0;clk<ec->get_length() && gate == false;clk++)
{
  if(devconf[IndexCurrentConfig]->get_page3(2).get_executecommand() == ec->GetCommand(clk).get_command())
  {
      ui->konf_tbx_33->setEnabled(true);
      ui->konf_checkbox_33->setChecked(false);
      ui->konf_command_cbx_33->setEnabled(true);
      ui->konf_command_tbx_33->setEnabled(false);
      ui->konf_tbx_33->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page3(2).get_description()));
      ui->konf_command_cbx_33->setCurrentText(QString::fromStdString(ec->GetCommand(clk).get_description()));
      gate = true;
  }
}
if(gate == false)
{
  ui->konf_tbx_33->setEnabled(true);
  ui->konf_checkbox_33->setChecked(true);
  ui->konf_command_cbx_33->setEnabled(false);
  ui->konf_command_tbx_33->setEnabled(true);
  ui->konf_tbx_33->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page3(2).get_description()));
  ui->konf_command_tbx_33->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page3(2).get_executecommand()));
}

//Strona 3 pozycja 4
gate = false;
for(int clk=0;clk<ec->get_length() && gate == false;clk++)
{
 if(devconf[IndexCurrentConfig]->get_page3(3).get_executecommand() == ec->GetCommand(clk).get_command())
 {
     ui->konf_tbx_34->setEnabled(true);
     ui->konf_checkbox_34->setChecked(false);
     ui->konf_command_cbx_34->setEnabled(true);
     ui->konf_command_tbx_34->setEnabled(false);
     ui->konf_tbx_34->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page3(3).get_description()));
     ui->konf_command_cbx_34->setCurrentText(QString::fromStdString(ec->GetCommand(clk).get_description()));
     gate = true;
 }
}
if(gate == false)
{
 ui->konf_tbx_34->setEnabled(true);
 ui->konf_checkbox_34->setChecked(true);
 ui->konf_command_cbx_34->setEnabled(false);
 ui->konf_command_tbx_34->setEnabled(true);
 ui->konf_tbx_34->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page3(3).get_description()));
 ui->konf_command_tbx_34->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page3(3).get_executecommand()));
}

//Strona 4 pozycja 1
gate = false;
for(int clk=0;clk<ec->get_length() && gate == false;clk++)
{
    if(devconf[IndexCurrentConfig]->get_page4(0).get_executecommand() == ec->GetCommand(clk).get_command())
    {
        ui->konf_tbx_41->setEnabled(true);
        ui->konf_checkbox_41->setChecked(false);
        ui->konf_command_cbx_41->setEnabled(true);
        ui->konf_command_tbx_41->setEnabled(false);
        ui->konf_tbx_41->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page4(0).get_description()));
        ui->konf_command_cbx_41->setCurrentText(QString::fromStdString(ec->GetCommand(clk).get_description()));
        gate = true;
    }
}
if(gate == false)
{
    ui->konf_tbx_41->setEnabled(true);
    ui->konf_checkbox_41->setChecked(true);
    ui->konf_command_cbx_41->setEnabled(false);
    ui->konf_command_tbx_41->setEnabled(true);
    ui->konf_tbx_41->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page4(0).get_description()));
    ui->konf_command_tbx_41->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page4(0).get_executecommand()));
}

//Strona 4 pozycja 2
gate = false;
for(int clk=0;clk<ec->get_length() && gate == false;clk++)
{
   if(devconf[IndexCurrentConfig]->get_page4(1).get_executecommand() == ec->GetCommand(clk).get_command())
   {
       ui->konf_tbx_42->setEnabled(true);
       ui->konf_checkbox_42->setChecked(false);
       ui->konf_command_cbx_42->setEnabled(true);
       ui->konf_command_tbx_42->setEnabled(false);
       ui->konf_tbx_42->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page4(1).get_description()));
       ui->konf_command_cbx_42->setCurrentText(QString::fromStdString(ec->GetCommand(clk).get_description()));
       gate = true;
   }
}
if(gate == false)
{
   ui->konf_tbx_42->setEnabled(true);
   ui->konf_checkbox_42->setChecked(true);
   ui->konf_command_cbx_42->setEnabled(false);
   ui->konf_command_tbx_42->setEnabled(true);
   ui->konf_tbx_42->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page4(1).get_description()));
   ui->konf_command_tbx_42->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page4(1).get_executecommand()));
}

//Strona 4 pozycja 3
gate = false;
for(int clk=0;clk<ec->get_length() && gate == false;clk++)
{
  if(devconf[IndexCurrentConfig]->get_page4(2).get_executecommand() == ec->GetCommand(clk).get_command())
  {
      ui->konf_tbx_43->setEnabled(true);
      ui->konf_checkbox_43->setChecked(false);
      ui->konf_command_cbx_43->setEnabled(true);
      ui->konf_command_tbx_43->setEnabled(false);
      ui->konf_tbx_43->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page4(2).get_description()));
      ui->konf_command_cbx_43->setCurrentText(QString::fromStdString(ec->GetCommand(clk).get_description()));
      gate = true;
  }
}
if(gate == false)
{
  ui->konf_tbx_43->setEnabled(true);
  ui->konf_checkbox_43->setChecked(true);
  ui->konf_command_cbx_43->setEnabled(false);
  ui->konf_command_tbx_43->setEnabled(true);
  ui->konf_tbx_43->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page4(2).get_description()));
  ui->konf_command_tbx_43->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page4(2).get_executecommand()));
}

//Strona 4 pozycja 4
gate = false;
for(int clk=0;clk<ec->get_length() && gate == false;clk++)
{
 if(devconf[IndexCurrentConfig]->get_page4(3).get_executecommand() == ec->GetCommand(clk).get_command())
 {
     ui->konf_tbx_44->setEnabled(true);
     ui->konf_checkbox_44->setChecked(false);
     ui->konf_command_cbx_44->setEnabled(true);
     ui->konf_command_tbx_44->setEnabled(false);
     ui->konf_tbx_44->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page4(3).get_description()));
     ui->konf_command_cbx_44->setCurrentText(QString::fromStdString(ec->GetCommand(clk).get_description()));
     gate = true;
 }
}
if(gate == false)
{
 ui->konf_tbx_44->setEnabled(true);
 ui->konf_checkbox_44->setChecked(true);
 ui->konf_command_cbx_44->setEnabled(false);
 ui->konf_command_tbx_44->setEnabled(true);
 ui->konf_tbx_44->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page4(3).get_description()));
 ui->konf_command_tbx_44->setText(QString::fromStdString(devconf[IndexCurrentConfig]->get_page4(3).get_executecommand()));
}


}

void MainWindow::UpdateCommunicationProfileLables()
{
    ui->lbl_commandset_1->setText(QString::fromStdString(devconf[0]->get_etykieta()));
    ui->lbl_commandset_2->setText(QString::fromStdString(devconf[1]->get_etykieta()));
    ui->lbl_commandset_3->setText(QString::fromStdString(devconf[2]->get_etykieta()));
    ui->lbl_commandset_4->setText(QString::fromStdString(devconf[3]->get_etykieta()));
    ui->lbl_commandset_5->setText(QString::fromStdString(devconf[4]->get_etykieta()));
    ui->lbl_commandset_6->setText(QString::fromStdString(devconf[5]->get_etykieta()));
    ui->lbl_commandset_7->setText(QString::fromStdString(devconf[6]->get_etykieta()));
    ui->lbl_commandset_8->setText(QString::fromStdString(devconf[7]->get_etykieta()));
    ui->lbl_commandset_9->setText(QString::fromStdString(devconf[8]->get_etykieta()));
    ui->lbl_commandset_10->setText(QString::fromStdString(devconf[9]->get_etykieta()));
}

void MainWindow::FillComandsFields()
{
    AddConfigFielsCommands();

    for(int clk=0;clk<ec->get_length();clk++)
    {
        ui->konf_command_cbx_11->addItem(QString::fromStdString(ec->GetCommand(clk).get_description()));
        ui->konf_command_cbx_12->addItem(QString::fromStdString(ec->GetCommand(clk).get_description()));
        ui->konf_command_cbx_13->addItem(QString::fromStdString(ec->GetCommand(clk).get_description()));
        ui->konf_command_cbx_14->addItem(QString::fromStdString(ec->GetCommand(clk).get_description()));

        ui->konf_command_cbx_21->addItem(QString::fromStdString(ec->GetCommand(clk).get_description()));
        ui->konf_command_cbx_22->addItem(QString::fromStdString(ec->GetCommand(clk).get_description()));
        ui->konf_command_cbx_23->addItem(QString::fromStdString(ec->GetCommand(clk).get_description()));
        ui->konf_command_cbx_24->addItem(QString::fromStdString(ec->GetCommand(clk).get_description()));

        ui->konf_command_cbx_31->addItem(QString::fromStdString(ec->GetCommand(clk).get_description()));
        ui->konf_command_cbx_32->addItem(QString::fromStdString(ec->GetCommand(clk).get_description()));
        ui->konf_command_cbx_33->addItem(QString::fromStdString(ec->GetCommand(clk).get_description()));
        ui->konf_command_cbx_34->addItem(QString::fromStdString(ec->GetCommand(clk).get_description()));

        ui->konf_command_cbx_41->addItem(QString::fromStdString(ec->GetCommand(clk).get_description()));
        ui->konf_command_cbx_42->addItem(QString::fromStdString(ec->GetCommand(clk).get_description()));
        ui->konf_command_cbx_43->addItem(QString::fromStdString(ec->GetCommand(clk).get_description()));
        ui->konf_command_cbx_44->addItem(QString::fromStdString(ec->GetCommand(clk).get_description()));
    }
}

void MainWindow::FillConfigFields()
{
    ui->portcfg_baudrate->addItem("1200");
    ui->portcfg_baudrate->addItem("2400");
    ui->portcfg_baudrate->addItem("4800");
    ui->portcfg_baudrate->addItem("9600");
    ui->portcfg_baudrate->addItem("19200");
    ui->portcfg_baudrate->addItem("38400");
    ui->portcfg_baudrate->addItem("57600");
    ui->portcfg_baudrate->addItem("115200");

    ui->portcfg_parity->addItem("NOPARITY");
    ui->portcfg_parity->addItem("ODDPARITY");
    ui->portcfg_parity->addItem("EVENPARITY");
    ui->portcfg_parity->addItem("MARKPARITY");
    ui->portcfg_parity->addItem("SPACEPARITY");

    ui->portcfg_bytesize->addItem("7");
    ui->portcfg_bytesize->addItem("8");

    ui->portcfg_stopbits->addItem("ONESTOPBIT");
    ui->portcfg_stopbits->addItem("ONE5STOPBITS");
    ui->portcfg_stopbits->addItem("TWOSTOPBITS");

    ui->portcfg_dtrcontrol->addItem("NoFlowControl");
    ui->portcfg_dtrcontrol->addItem("HardwareControl");
    ui->portcfg_dtrcontrol->addItem("SoftwareControl");
}

void MainWindow::SetVirtualButtons(DeviceConfig dc)
{
    ui->btn_11->setText(QString::fromStdString(dc.get_page1(0).get_description()));
    ui->btn_12->setText(QString::fromStdString(dc.get_page1(1).get_description()));
    ui->btn_13->setText(QString::fromStdString(dc.get_page1(2).get_description()));
    ui->btn_14->setText(QString::fromStdString(dc.get_page1(3).get_description()));

    ui->btn_21->setText(QString::fromStdString(dc.get_page2(0).get_description()));
    ui->btn_22->setText(QString::fromStdString(dc.get_page2(1).get_description()));
    ui->btn_23->setText(QString::fromStdString(dc.get_page2(2).get_description()));
    ui->btn_24->setText(QString::fromStdString(dc.get_page2(3).get_description()));

    ui->btn_31->setText(QString::fromStdString(dc.get_page3(0).get_description()));
    ui->btn_32->setText(QString::fromStdString(dc.get_page3(1).get_description()));
    ui->btn_33->setText(QString::fromStdString(dc.get_page3(2).get_description()));
    ui->btn_34->setText(QString::fromStdString(dc.get_page3(3).get_description()));

    ui->btn_41->setText(QString::fromStdString(dc.get_page4(0).get_description()));
    ui->btn_42->setText(QString::fromStdString(dc.get_page4(1).get_description()));
    ui->btn_43->setText(QString::fromStdString(dc.get_page4(2).get_description()));
    ui->btn_44->setText(QString::fromStdString(dc.get_page4(3).get_description()));
}


//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
//obsługa przycisków


void MainWindow::on_btn_connect_clicked()
{
    UARTConnect();
}

void MainWindow::on_btn_disconnect_clicked()
{
    UARTDisconnect();
}

void MainWindow::on_btn_uartconfig_connect_clicked()
{
    UARTConnect();
}

void MainWindow::on_btn_uartconfig_disconnect_clicked()
{
    UARTDisconnect();
}

void MainWindow::on_btn_hide_clicked()
{
    hide();
}

void MainWindow::on_btn_devinitialize_clicked()
{
    UARTWriteLables();
}

void MainWindow::on_toolButton_clicked()
{
    ui->tbx_commandhistory->clear();
}


void MainWindow::on_btn_zapiskonfpolaczenia_clicked()
{
    sp->set_parity(ui->portcfg_parity->currentText().toStdString());
    sp->set_baudrate(ui->portcfg_baudrate->currentText().toStdString());
    sp->set_bytesize(ui->portcfg_bytesize->currentText().toStdString());
    sp->set_stopbits(ui->portcfg_stopbits->currentText().toStdString());
    sp->set_dtrcontrol(ui->portcfg_dtrcontrol->currentText().toStdString());
    sp->set_portnumber(ui->portcfg_numerportu->value());

    io->zapisz_config(*sp);
    SetUARTConnectionConfig();
    UARTDisconnect();
}

void MainWindow::on_btnponfpolacz_przywroc_clicked()
{
    SetConfigFields();
}

void MainWindow::on_btn_devinitialize2_clicked()
{
    UARTWriteLables();
}

void MainWindow::on_btn_loadconf_1_clicked()
{
    ui->lbl_commandset_1->setText(QString::fromStdString(devconf[0]->get_etykieta()));
    IndexCurrentConfig = 0;
    SetCommandsFields();
}

void MainWindow::on_btn_saveconf_1_clicked()
{
    devconf[0]->set_etykieta(ui->lbl_commandset_1->text().toStdString());
    Updatedevconf(0);
}

void MainWindow::on_btn_loadconf_2_clicked()
{
    ui->lbl_commandset_2->setText(QString::fromStdString(devconf[1]->get_etykieta()));
    IndexCurrentConfig = 1;
    SetCommandsFields();
}

void MainWindow::on_btn_saveconf_2_clicked()
{
    devconf[1]->set_etykieta(ui->lbl_commandset_2->text().toStdString());
    Updatedevconf(1);
}

void MainWindow::on_btn_loadconf_3_clicked()
{
    ui->lbl_commandset_3->setText(QString::fromStdString(devconf[2]->get_etykieta()));
    IndexCurrentConfig = 2;
    SetCommandsFields();
}

void MainWindow::on_btn_saveconf_3_clicked()
{
    devconf[2]->set_etykieta(ui->lbl_commandset_3->text().toStdString());
    Updatedevconf(2);
}

void MainWindow::on_btn_loadconf_4_clicked()
{
    ui->lbl_commandset_4->setText(QString::fromStdString(devconf[3]->get_etykieta()));
    IndexCurrentConfig = 3;
    SetCommandsFields();
}

void MainWindow::on_btn_saveconf_4_clicked()
{
    devconf[3]->set_etykieta(ui->lbl_commandset_4->text().toStdString());
    Updatedevconf(3);
}

void MainWindow::on_btn_loadconf_5_clicked()
{
    ui->lbl_commandset_5->setText(QString::fromStdString(devconf[4]->get_etykieta()));
    IndexCurrentConfig = 4;
    SetCommandsFields();
}

void MainWindow::on_btn_saveconf_5_clicked()
{
    devconf[4]->set_etykieta(ui->lbl_commandset_5->text().toStdString());
    Updatedevconf(4);
}

void MainWindow::on_btn_loadconf_6_clicked()
{
    ui->lbl_commandset_6->setText(QString::fromStdString(devconf[5]->get_etykieta()));
    IndexCurrentConfig = 5;
    SetCommandsFields();
}

void MainWindow::on_btn_saveconf_6_clicked()
{
    devconf[5]->set_etykieta(ui->lbl_commandset_6->text().toStdString());
    Updatedevconf(5);
}

void MainWindow::on_btn_loadconf_7_clicked()
{
    ui->lbl_commandset_7->setText(QString::fromStdString(devconf[6]->get_etykieta()));
    IndexCurrentConfig = 6;
    SetCommandsFields();
}

void MainWindow::on_btn_saveconf_7_clicked()
{
    devconf[6]->set_etykieta(ui->lbl_commandset_7->text().toStdString());
    Updatedevconf(6);
}

void MainWindow::on_btn_loadconf_8_clicked()
{
    ui->lbl_commandset_8->setText(QString::fromStdString(devconf[7]->get_etykieta()));
    IndexCurrentConfig = 7;
    SetCommandsFields();
}

void MainWindow::on_btn_saveconf_8_clicked()
{
    devconf[7]->set_etykieta(ui->lbl_commandset_8->text().toStdString());
    Updatedevconf(7);
}

void MainWindow::on_btn_loadconf_9_clicked()
{
    ui->lbl_commandset_9->setText(QString::fromStdString(devconf[8]->get_etykieta()));
    IndexCurrentConfig = 8;
    SetCommandsFields();
}

void MainWindow::on_btn_saveconf_9_clicked()
{
    devconf[8]->set_etykieta(ui->lbl_commandset_9->text().toStdString());
    Updatedevconf(8);
}

void MainWindow::on_btn_loadconf_10_clicked()
{
    ui->lbl_commandset_10->setText(QString::fromStdString(devconf[9]->get_etykieta()));
    IndexCurrentConfig = 9;
    SetCommandsFields();
}

void MainWindow::on_btn_saveconf_10_clicked()
{
    devconf[9]->set_etykieta(ui->lbl_commandset_10->text().toStdString());
    Updatedevconf(9);
}

void MainWindow::on_btn_11_clicked()
{
    ec->Execute(devconf[IndexCurrentConfig]->get_page1(0).get_executecommand());
}

void MainWindow::on_btn_12_clicked()
{
    ec->Execute(devconf[IndexCurrentConfig]->get_page1(1).get_executecommand());
}

void MainWindow::on_btn_13_clicked()
{
    ec->Execute(devconf[IndexCurrentConfig]->get_page1(2).get_executecommand());
}

void MainWindow::on_btn_14_clicked()
{
    ec->Execute(devconf[IndexCurrentConfig]->get_page1(3).get_executecommand());
}

void MainWindow::on_btn_21_clicked()
{
    ec->Execute(devconf[IndexCurrentConfig]->get_page2(0).get_executecommand());
}

void MainWindow::on_btn_22_clicked()
{
    ec->Execute(devconf[IndexCurrentConfig]->get_page2(1).get_executecommand());
}

void MainWindow::on_btn_23_clicked()
{
    ec->Execute(devconf[IndexCurrentConfig]->get_page2(2).get_executecommand());
}

void MainWindow::on_btn_24_clicked()
{
    ec->Execute(devconf[IndexCurrentConfig]->get_page2(3).get_executecommand());
}

void MainWindow::on_btn_31_clicked()
{
    ec->Execute(devconf[IndexCurrentConfig]->get_page3(0).get_executecommand());
}

void MainWindow::on_btn_32_clicked()
{
    ec->Execute(devconf[IndexCurrentConfig]->get_page3(1).get_executecommand());
}

void MainWindow::on_btn_33_clicked()
{
    ec->Execute(devconf[IndexCurrentConfig]->get_page3(2).get_executecommand());
}

void MainWindow::on_btn_34_clicked()
{
    ec->Execute(devconf[IndexCurrentConfig]->get_page3(3).get_executecommand());
}

void MainWindow::on_btn_41_clicked()
{
    ec->Execute(devconf[IndexCurrentConfig]->get_page4(0).get_executecommand());
}

void MainWindow::on_btn_42_clicked()
{
    ec->Execute(devconf[IndexCurrentConfig]->get_page4(1).get_executecommand());
}

void MainWindow::on_btn_43_clicked()
{
    ec->Execute(devconf[IndexCurrentConfig]->get_page4(2).get_executecommand());
}

void MainWindow::on_btn_44_clicked()
{
    ec->Execute(devconf[IndexCurrentConfig]->get_page4(3).get_executecommand());
}



//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
//obsługa innych elementów interaktywnych

void MainWindow::on_konf_checkbox_11_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->konf_tbx_11->setEnabled(true);
        ui->konf_command_cbx_11->setEnabled(false);
        ui->konf_command_tbx_11->setEnabled(true);
    }
    else
    {
        ui->konf_tbx_11->setEnabled(true);
        ui->konf_command_cbx_11->setEnabled(true);
        ui->konf_command_tbx_11->setEnabled(false);
    }
}

void MainWindow::on_konf_checkbox_12_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->konf_tbx_12->setEnabled(true);
        ui->konf_command_cbx_12->setEnabled(false);
        ui->konf_command_tbx_12->setEnabled(true);
    }
    else
    {
        ui->konf_tbx_12->setEnabled(true);
        ui->konf_command_cbx_12->setEnabled(true);
        ui->konf_command_tbx_12->setEnabled(false);
    }
}

void MainWindow::on_konf_checkbox_13_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->konf_tbx_13->setEnabled(true);
        ui->konf_command_cbx_13->setEnabled(false);
        ui->konf_command_tbx_13->setEnabled(true);
    }
    else
    {
        ui->konf_tbx_13->setEnabled(true);
        ui->konf_command_cbx_13->setEnabled(true);
        ui->konf_command_tbx_13->setEnabled(false);
    }
}

void MainWindow::on_konf_checkbox_14_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->konf_tbx_14->setEnabled(true);
        ui->konf_command_cbx_14->setEnabled(false);
        ui->konf_command_tbx_14->setEnabled(true);
    }
    else
    {
        ui->konf_tbx_14->setEnabled(true);
        ui->konf_command_cbx_14->setEnabled(true);
        ui->konf_command_tbx_14->setEnabled(false);
    }
}

void MainWindow::on_konf_checkbox_21_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->konf_tbx_21->setEnabled(true);
        ui->konf_command_cbx_21->setEnabled(false);
        ui->konf_command_tbx_21->setEnabled(true);
    }
    else
    {
        ui->konf_tbx_21->setEnabled(true);
        ui->konf_command_cbx_21->setEnabled(true);
        ui->konf_command_tbx_21->setEnabled(false);
    }
}

void MainWindow::on_konf_checkbox_22_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->konf_tbx_22->setEnabled(true);
        ui->konf_command_cbx_22->setEnabled(false);
        ui->konf_command_tbx_22->setEnabled(true);
    }
    else
    {
        ui->konf_tbx_22->setEnabled(true);
        ui->konf_command_cbx_22->setEnabled(true);
        ui->konf_command_tbx_22->setEnabled(false);
    }
}

void MainWindow::on_konf_checkbox_23_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->konf_tbx_23->setEnabled(true);
        ui->konf_command_cbx_23->setEnabled(false);
        ui->konf_command_tbx_23->setEnabled(true);
    }
    else
    {
        ui->konf_tbx_23->setEnabled(true);
        ui->konf_command_cbx_23->setEnabled(true);
        ui->konf_command_tbx_23->setEnabled(false);
    }
}

void MainWindow::on_konf_checkbox_24_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->konf_tbx_24->setEnabled(true);
        ui->konf_command_cbx_24->setEnabled(false);
        ui->konf_command_tbx_24->setEnabled(true);
    }
    else
    {
        ui->konf_tbx_24->setEnabled(true);
        ui->konf_command_cbx_24->setEnabled(true);
        ui->konf_command_tbx_24->setEnabled(false);
    }
}

void MainWindow::on_konf_checkbox_31_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->konf_tbx_31->setEnabled(true);
        ui->konf_command_cbx_31->setEnabled(false);
        ui->konf_command_tbx_31->setEnabled(true);
    }
    else
    {
        ui->konf_tbx_31->setEnabled(true);
        ui->konf_command_cbx_31->setEnabled(true);
        ui->konf_command_tbx_31->setEnabled(false);
    }
}

void MainWindow::on_konf_checkbox_32_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->konf_tbx_32->setEnabled(true);
        ui->konf_command_cbx_32->setEnabled(false);
        ui->konf_command_tbx_32->setEnabled(true);
    }
    else
    {
        ui->konf_tbx_32->setEnabled(true);
        ui->konf_command_cbx_32->setEnabled(true);
        ui->konf_command_tbx_32->setEnabled(false);
    }
}

void MainWindow::on_konf_checkbox_33_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->konf_tbx_33->setEnabled(true);
        ui->konf_command_cbx_33->setEnabled(false);
        ui->konf_command_tbx_33->setEnabled(true);
    }
    else
    {
        ui->konf_tbx_33->setEnabled(true);
        ui->konf_command_cbx_33->setEnabled(true);
        ui->konf_command_tbx_33->setEnabled(false);
    }
}

void MainWindow::on_konf_checkbox_34_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->konf_tbx_34->setEnabled(true);
        ui->konf_command_cbx_34->setEnabled(false);
        ui->konf_command_tbx_34->setEnabled(true);
    }
    else
    {
        ui->konf_tbx_34->setEnabled(true);
        ui->konf_command_cbx_34->setEnabled(true);
        ui->konf_command_tbx_34->setEnabled(false);
    }
}

void MainWindow::on_konf_checkbox_41_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->konf_tbx_41->setEnabled(true);
        ui->konf_command_cbx_41->setEnabled(false);
        ui->konf_command_tbx_41->setEnabled(true);
    }
    else
    {
        ui->konf_tbx_41->setEnabled(true);
        ui->konf_command_cbx_41->setEnabled(true);
        ui->konf_command_tbx_41->setEnabled(false);
    }
}

void MainWindow::on_konf_checkbox_42_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->konf_tbx_42->setEnabled(true);
        ui->konf_command_cbx_42->setEnabled(false);
        ui->konf_command_tbx_42->setEnabled(true);
    }
    else
    {
        ui->konf_tbx_42->setEnabled(true);
        ui->konf_command_cbx_42->setEnabled(true);
        ui->konf_command_tbx_42->setEnabled(false);
    }
}

void MainWindow::on_konf_checkbox_43_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->konf_tbx_43->setEnabled(true);
        ui->konf_command_cbx_43->setEnabled(false);
        ui->konf_command_tbx_43->setEnabled(true);
    }
    else
    {
        ui->konf_tbx_43->setEnabled(true);
        ui->konf_command_cbx_43->setEnabled(true);
        ui->konf_command_tbx_43->setEnabled(false);
    }
}

void MainWindow::on_konf_checkbox_44_stateChanged(int arg1)
{
    if(arg1 == 2)
    {
        ui->konf_tbx_44->setEnabled(true);
        ui->konf_command_cbx_44->setEnabled(false);
        ui->konf_command_tbx_44->setEnabled(true);
    }
    else
    {
        ui->konf_tbx_44->setEnabled(true);
        ui->konf_command_cbx_44->setEnabled(true);
        ui->konf_command_tbx_44->setEnabled(false);
    }
}


//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
//UART


void MainWindow::readSerialData()
{
    QByteArray buff;
    char d;

    while(mSerialPort->waitForReadyRead(10)){
        while (mSerialPort->bytesAvailable() > 0){
           mSerialPort->read(&d,1);
           buff.append(d);
           if (d == '\n')
               break;
        }
    }
    std::cout<<"Recived: "<<buff.toStdString()<<"\n";
    if(buff.toStdString() != "")
    {
        ui->tbx_commandhistory->insertPlainText(buff);
        CheckCommand(buff.toStdString());
    }
}

void MainWindow::UARTWriteLables()
{
    if(connectionstatus==true)
    {
        mSystemTrayIcon->showMessage(tr("UART"), tr("Zapisywanie do urządzenia"));
        Sleep(100);
        for (int clk = 0; clk < 4; clk++)
        {
            mSerialPort->write(devconf[IndexCurrentConfig]->get_page1(clk).get_description().c_str(), 7);
            mSerialPort->write("\n", 1);
            ui->tbx_commandhistory->insertPlainText("Write->" + QString::fromStdString(devconf[IndexCurrentConfig]->get_page1(clk).get_description()) + "\n");
            QApplication::processEvents();
            Sleep(200);
        }
        for (int clk = 0; clk < 4; clk++)
        {
            mSerialPort->write(devconf[IndexCurrentConfig]->get_page2(clk).get_description().c_str(), 8);
            mSerialPort->write("\n", 1);
            ui->tbx_commandhistory->insertPlainText("Write->" + QString::fromStdString(devconf[IndexCurrentConfig]->get_page2(clk).get_description()) + "\n");
            QApplication::processEvents();
            Sleep(200);
        }
        for (int clk = 0; clk < 4; clk++)
        {
            mSerialPort->write(devconf[IndexCurrentConfig]->get_page3(clk).get_description().c_str(), 8);
            mSerialPort->write("\n", 1);
            ui->tbx_commandhistory->insertPlainText("Write->" + QString::fromStdString(devconf[IndexCurrentConfig]->get_page3(clk).get_description()) + "\n");
            QApplication::processEvents();
            Sleep(200);
        }
        for (int clk = 0; clk < 4; clk++)
        {
            mSerialPort->write(devconf[IndexCurrentConfig]->get_page4(clk).get_description().c_str(), 8);
            mSerialPort->write("\n", 1);
            ui->tbx_commandhistory->insertPlainText("Write->" + QString::fromStdString(devconf[IndexCurrentConfig]->get_page4(clk).get_description()) + "\n");
            QApplication::processEvents();
            Sleep(200);
        }

        io->zapisz(devconf, *sp, IndexCurrentConfig);
        SetVirtualButtons(*devconf[IndexCurrentConfig]);
        mSystemTrayIcon->showMessage(tr("UART"), tr("Zakończono zapisywanie do urządzenia"));
    }
    else UARTwriteError();
}

void MainWindow::UARTConnect()
{
    if (mSerialPort->open(QIODevice::ReadWrite)) {
            connectionstatus = true;
           std::cout<<"Connected\n";
           SetConnectionStatusLabel(true);
               mSystemTrayIcon->showMessage(tr("Połączenie"), tr("Connected"));

       } else {
           connectionstatus = false;
           SetConnectionStatusLabel(false);
           std::cout<<"Open error\n";
               mSystemTrayIcon->showMessage(tr("Połączenie"), tr("Open error"));
       }
}

void MainWindow::UARTDisconnect()
{
    if (mSerialPort->isOpen()) mSerialPort->close();
    connectionstatus = false;
    SetConnectionStatusLabel(false);
    std::cout<<"Disconnected\n";
    mSystemTrayIcon->showMessage(tr("Połączenie"), tr("Disconnected"));
}

void MainWindow::CheckCommand(std::string command)
 {
     if(command[0] != 0 && command[1] != 0 && command[2] != 0 && command[3] != 0)
     {
         printf("[%c][%c][%c][%c]: %s\n", command[0], command[1], command[2], command[3], command.c_str());
     }
     Sleep(100);
     int howmuchsleep = 0;

     if (command[0] == 'a' && command[1] == 'a' && command[2] == '1' && command[3] == '1') { ec->Execute(devconf[IndexCurrentConfig]->get_page1(0).get_executecommand()); Sleep(howmuchsleep); }
     else if (command[0] == 'a' && command[1] == 'a' && command[2] == '2' && command[3] == '2') { ec->Execute(devconf[IndexCurrentConfig]->get_page1(1).get_executecommand()); Sleep(howmuchsleep); }
     else if (command[0] == 'a' && command[1] == 'a' && command[2] == '3' && command[3] == '3') { ec->Execute(devconf[IndexCurrentConfig]->get_page1(2).get_executecommand()); Sleep(howmuchsleep); }
     else if (command[0] == 'a' && command[1] == 'a' && command[2] == '4' && command[3] == '4') { ec->Execute(devconf[IndexCurrentConfig]->get_page1(3).get_executecommand()); Sleep(howmuchsleep); }

     else if (command[0] == 'b' && command[1] == 'b' && command[2] == '1' && command[3] == '1') { ec->Execute(devconf[IndexCurrentConfig]->get_page2(0).get_executecommand()); Sleep(howmuchsleep); }
     else if (command[0] == 'b' && command[1] == 'b' && command[2] == '2' && command[3] == '2') { ec->Execute(devconf[IndexCurrentConfig]->get_page2(1).get_executecommand()); Sleep(howmuchsleep); }
     else if (command[0] == 'b' && command[1] == 'b' && command[2] == '3' && command[3] == '3') { ec->Execute(devconf[IndexCurrentConfig]->get_page2(2).get_executecommand()); Sleep(howmuchsleep); }
     else if (command[0] == 'b' && command[1] == 'b' && command[2] == '4' && command[3] == '4') { ec->Execute(devconf[IndexCurrentConfig]->get_page2(3).get_executecommand()); Sleep(howmuchsleep); }

     else if (command[0] == 'c' && command[1] == 'c' && command[2] == '1' && command[3] == '1') { ec->Execute(devconf[IndexCurrentConfig]->get_page3(0).get_executecommand()); Sleep(howmuchsleep); }
     else if (command[0] == 'c' && command[1] == 'c' && command[2] == '2' && command[3] == '2') { ec->Execute(devconf[IndexCurrentConfig]->get_page3(1).get_executecommand()); Sleep(howmuchsleep); }
     else if (command[0] == 'c' && command[1] == 'c' && command[2] == '3' && command[3] == '3') { ec->Execute(devconf[IndexCurrentConfig]->get_page3(2).get_executecommand()); Sleep(howmuchsleep); }
     else if (command[0] == 'c' && command[1] == 'c' && command[2] == '4' && command[3] == '4') { ec->Execute(devconf[IndexCurrentConfig]->get_page3(3).get_executecommand()); Sleep(howmuchsleep); }

     else if (command[0] == 'd' && command[1] == 'd' && command[2] == '1' && command[3] == '1') { ec->Execute(devconf[IndexCurrentConfig]->get_page4(0).get_executecommand()); Sleep(howmuchsleep); }
     else if (command[0] == 'd' && command[1] == 'd' && command[2] == '2' && command[3] == '2') { ec->Execute(devconf[IndexCurrentConfig]->get_page4(1).get_executecommand()); Sleep(howmuchsleep); }
     else if (command[0] == 'd' && command[1] == 'd' && command[2] == '3' && command[3] == '3') { ec->Execute(devconf[IndexCurrentConfig]->get_page4(2).get_executecommand()); Sleep(howmuchsleep); }
     else if (command[0] == 'd' && command[1] == 'd' && command[2] == '4' && command[3] == '4') { ec->Execute(devconf[IndexCurrentConfig]->get_page4(3).get_executecommand()); Sleep(howmuchsleep); }
 }

void MainWindow::SetConnectionStatusLabel(bool status)
{
    if(status)
    {
        ui->lbl_constatus->setText("<font color='green'>Connected</font>");
    }
    else
    {
        ui->lbl_constatus->setText("<font color='red'>Disconnected</font>");
    }
}

void MainWindow::UARTwriteError()
{
    mSystemTrayIcon->showMessage(tr("UART"), tr("Nie można wysłać danych do urządzenia"));
    ui->tbx_commandhistory->insertPlainText("Nie można wysłać danych do urządzenia\n");
}

//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
//SysTray


void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        show();
        break;
    case QSystemTrayIcon::MiddleClick:
         close();
        break;
    default:
        ;
    }
}




//------------------------------------------------------------------
//------------------------------------------------------------------
//------------------------------------------------------------------
//Koniec programu
