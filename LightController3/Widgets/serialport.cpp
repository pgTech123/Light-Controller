#include "serialport.h"
#include "ui_serialport.h"

SerialPort::SerialPort(QWidget *parent) :
    DockableWindow(parent),
    ui(new Ui::SerialPort)
{
    ui->setupUi(this);
    ui->dockWidgetContents->setLayout(ui->gridLayout);

    m_bPortConnected = false;
    m_iSelectedPort = -1;
    m_ucDataToTransmit = NULL;
    m_iNumberOfAddresses = 0;
    m_timerWaitForNextWriting = new QTimer(this);
    m_serialPort = new QSerialPort(this);

    /* We set a pause of 10 ms between each writing on the serial port */
    m_timerWaitForNextWriting->start(10);

    m_PortAvailable = QSerialPortInfo::availablePorts();
    for(int i = 0; i < m_PortAvailable.size(); i++){
        ui->comboBoxSerialPort->addItem(m_PortAvailable.at(i).portName());
    }

    autoconnect();
}

SerialPort::~SerialPort()
{
    delete ui;

    if(m_bPortConnected ==true){
        disconnectPort();
    }
    if(m_ucDataToTransmit != NULL){
        delete[] m_ucDataToTransmit;
    }
}

void SerialPort::on_pushButtonConnect_clicked()
{
    if(m_bPortConnected == false){
        initConnection();
    }
    else{   /*(ask if we want to disconnect)*/
        int answer = QMessageBox::warning(this, "Warning", "Do you really want to disconnect the port?",
                                          QMessageBox::Yes | QMessageBox::No);

        if(answer == QMessageBox::Yes){         //Yes
            disconnectPort();                   //Disconnect
        }
        else{                                   //No
            return;                             //Do nothing
        }
    }
}

void SerialPort::autoconnect()
{
    if(m_bPortConnected)
    {
        int answer = QMessageBox::warning(this, "Warning", "A port is already connected. Do you want to disconnect it?",
                                          QMessageBox::Yes | QMessageBox::No);

        if(answer == QMessageBox::Yes){         //Yes
            disconnectPort();                   //Disconnect
        }
        else{                                   //No
            return;                             //Do nothing
        }
    }

    for(int i = 1; i < ui->comboBoxSerialPort->count(); i++){
        m_iSelectedPort = i-1;
        ui->comboBoxSerialPort->setCurrentIndex(i);
        if(initConnection(true)){
            break;
        }
    }
}

bool SerialPort::initConnection(bool silent)
{
    if(m_bPortConnected){
        QMessageBox::warning(this, "Warning", "There is already a port used by LightController3");
        return true;
    }

    m_serialPort->setPortName(ui->comboBoxSerialPort->currentText());
    m_serialPort->setBaudRate(QSerialPort::Baud19200);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::TwoStop);
    m_serialPort->setFlowControl(QSerialPort::HardwareControl);
    m_bPortConnected = m_serialPort->open(QIODevice::WriteOnly);

    if(m_bPortConnected){
        ui->labelConnectionStatus->setText("Connected");
        ui->pushButtonConnect->setText("Disconnect");
        connect(m_timerWaitForNextWriting,SIGNAL(timeout()),this,SLOT(writeOnPort()));
        return true;
    }
    else{
        QMessageBox::critical(this, tr("Serial Port Error"), m_serialPort->errorString());
    }

    return false;
}

void SerialPort::disconnectPort()
{
    if(m_serialPort->isOpen()){
        m_serialPort->close();
    }
    disconnect(m_timerWaitForNextWriting,SIGNAL(timeout()),this,SLOT(writeOnPort()));
    m_bPortConnected = false;
    ui->labelConnectionStatus->setText("Not Connected");
    ui->pushButtonConnect->setText("Connect");
    ui->label_DigitWritingTime->setText("Unspecified");
}

void SerialPort::writeOnPort()
{
    //COMMUNICATION
    /*    Tx -> Data     */
    /*    RTS -> Strobe  */

    m_writingTime->start();

    //Writing
    if(m_iNumberOfAddresses > 0)
    {
        QByteArray byteArray;
        for(int i = 0; i<m_iNumberOfAddresses; i++)
        {
            byteArray.append((char)m_ucDataToTransmit[i]);
        }

        m_serialPort->write(byteArray);

        //Strobe
        m_serialPort->setRequestToSend(true);
        m_serialPort->setRequestToSend(false);

        //Writing stats
        ui->label_DigitWritingTime->setNum(m_writingTime->elapsed());    //on écrit le temps que ca a pris à écrire
        m_timerWaitForNextWriting->start(10);    //on crée un délais de 1ms avant la prochaine écriture
    }
}

bool SerialPort::setNumberOfAddresses(int numOfAddr)
{
    if(m_iNumberOfAddresses > 0)
    {
        return false;
    }
    else
    {
        if(m_ucDataToTransmit != NULL){
            delete[] m_ucDataToTransmit;
            m_ucDataToTransmit = NULL;
        }
        m_ucDataToTransmit = new unsigned char[numOfAddr];
        /* Fill everything with 0s */
        for(int i = 0; i < numOfAddr; i++)
        {
            m_ucDataToTransmit[i] = 0;
        }
        m_iNumberOfAddresses = numOfAddr;
    }
    return true;
}

bool SerialPort::setData(int iData, int iAddress)
{
    if(iAddress > 0 && iAddress < m_iNumberOfAddresses)
    {
        //cout<< "Data changed" << endl;
        m_ucDataToTransmit[iAddress] = (unsigned char)iData;
        return true;
    }
    return false;
}
