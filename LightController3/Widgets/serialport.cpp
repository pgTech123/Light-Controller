#include "serialport.h"
#include "ui_serialport.h"

SerialPort::SerialPort(QWidget *parent) :
    DockableWindow(parent),
    ui(new Ui::SerialPort)
{
    ui->setupUi(this);
    ui->dockWidgetContents->setLayout(ui->gridLayout);

    //Init variables
    m_iSelectedPort = -1;
    m_ucDataToTransmit = NULL;
    m_iNumberOfAddresses = 0;
    m_timerWaitForNextWriting = new QTimer(this);
    m_writingTime = new QTime();
    m_serialPort = new QSerialPort(this);

    //We set a pause of 10 ms between each writing on the serial port
    m_timerWaitForNextWriting->start(10);

    m_PortAvailable = QSerialPortInfo::availablePorts();
    for(int i = 0; i < m_PortAvailable.size(); i++){
        ui->comboBoxSerialPort->addItem(m_PortAvailable.at(i).portName());
    }

    autoconnect();
}

SerialPort::~SerialPort()
{
    disconnectPort();   //Calls UI so must be called before deleting |ui|
    delete ui;
    delete m_writingTime;
    if(m_ucDataToTransmit != NULL){
        delete[] m_ucDataToTransmit;
        m_ucDataToTransmit = NULL;
    }
}

void SerialPort::on_pushButtonConnect_clicked()
{
    if(!m_serialPort->isOpen()){
        initConnection();
    }
    else{
        askForDisconnection();
    }
}

void SerialPort::autoconnect()
{
    if(m_serialPort->isOpen())
    {
        if(!askForDisconnection()){//Catch abort
            return;
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

//When returns true => |disconnetPort()| was called
//When returns false => abort
bool SerialPort::askForDisconnection()
{
    int answer = QMessageBox::warning(this, "Warning",
                                      "Do you really want to disconnect the port?",
                                      QMessageBox::Yes | QMessageBox::No);
    if(answer == QMessageBox::Yes){
        disconnectPort();
        return true;
    }
    else{
        return false;
    }
}

//When returns true => a serial port is opened
//When returns false => no serial port are opened
bool SerialPort::initConnection(bool silent)
{
    if(m_serialPort->isOpen()){
        QMessageBox::warning(this, "Warning",
                             "There is already a port used by LightController3");
        return true;
    }

    m_serialPort->setPortName(ui->comboBoxSerialPort->currentText());
    m_serialPort->setBaudRate(QSerialPort::Baud19200);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::TwoStop);
    m_serialPort->setFlowControl(QSerialPort::HardwareControl);
    bool connected = m_serialPort->open(QIODevice::WriteOnly);

    if(connected){
        ui->labelConnectionStatus->setText("Connected");
        ui->pushButtonConnect->setText("Disconnect");
        connect(m_timerWaitForNextWriting,SIGNAL(timeout()),this,SLOT(writeOnPort()));
        return true;
    }
    else if(!silent){
        QMessageBox::critical(this, tr("Serial Port Error"), m_serialPort->errorString());
    }

    return false;
}

void SerialPort::disconnectPort()
{
    if(m_serialPort->isOpen()){
        disconnect(m_timerWaitForNextWriting,SIGNAL(timeout()),this,SLOT(writeOnPort()));
        ui->labelConnectionStatus->setText("Not Connected");
        ui->pushButtonConnect->setText("Connect");
        ui->label_DigitWritingTime->setText("Unspecified");
        m_serialPort->close();
    }
}

void SerialPort::writeOnPort()
{
    //COMMUNICATION
    //  Tx -> Data
    //  RTS -> Strobe

    m_writingTime->start();

    //Writing
    if(m_iNumberOfAddresses > 0 && m_serialPort->isOpen())
    {
        //Write data
        QByteArray dataStream = QByteArray(reinterpret_cast<char*>(m_ucDataToTransmit), m_iNumberOfAddresses);
        /*for(int i = 0; i < m_iNumberOfAddresses; i++){
            //if(m_serialPort->putChar((char)m_ucDataToTransmit[i])){
            if(m_serialPort->write(dataStream)){
                cout << "Success!" << endl;
            }
            else{
                cout << "NO success :(" << endl;
            }
            m_serialPort->waitForBytesWritten(-1);
        }*/

        if(m_serialPort->write(dataStream)){
            cout << "Success!" << endl;
        }
        else{
            cout << "NO success :(" << endl;
        }

        //Strobe signal
        m_serialPort->setRequestToSend(true);
        m_serialPort->setRequestToSend(false);

        //Writing stats
        ui->label_DigitWritingTime->setNum(m_writingTime->elapsed());

        //Wait before next write
        m_timerWaitForNextWriting->start(10);
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
        //Fill everything with 0s
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
