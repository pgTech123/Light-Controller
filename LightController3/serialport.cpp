#include "serialport.h"
#include "ui_serialport.h"

SerialPort::SerialPort(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::SerialPort)
{
    ui->setupUi(this);
    this->setFixedSize(300,145);

    portConnected = false;
    numberOfAddresses = 0;

    tempsDEcriture = new QTime();
    waitForNextWriting = new QTimer(this);

    /* We set a pause of 100 ms between each writing on the serial port */
    waitForNextWriting->start(100);

    autoconnect();
}

SerialPort::~SerialPort()
{
    delete ui;

    if(portConnected ==true){
        disconnectPort();
    }
    delete[] dataToTransmit;
}

void SerialPort::closeEvent(QCloseEvent *closeEvent)
{
    closeEvent->ignore();
    this->hide();
    emit hidden();
}

void SerialPort::on_pushButtonConnect_clicked()
{
    if(portConnected == false){
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
    if(portConnected)
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

    for(int i = 5; i >0; i--)
    {
        ui->spinBoxPortNum->setValue(i);
        if(initConnection(true))
        {
            break;
        }
    }
}

bool SerialPort::initConnection(bool silent)
{
    if(portConnected)
    {
        QMessageBox::warning(this, "Warning", "Port already connected");
        return true;
    }
    const char* comPortName;
    int port = ui->spinBoxPortNum->value();

    if(port == 1){
        comPortName = "com1";
    }
    else if(port == 2){
        comPortName = "com2";
    }
    else if(port == 3){
        comPortName = "com3";
    }
    else if(port == 4){
        comPortName = "com4";
    }
    else if(port == 5){
        comPortName = "com5";
    }
    else{
        QMessageBox::warning(this, "Error", "Invalid port number");
        return false;
    }

    hcom=CreateFileA(comPortName,
                  GENERIC_READ|GENERIC_WRITE,
                  0,
                  NULL,
                  OPEN_EXISTING,
                  0,
                  NULL);
    if(hcom==INVALID_HANDLE_VALUE)
    {
        if(!silent){
            QMessageBox::warning(this, "Error", "Unable to open the port specified");
        }
        return false;
    }

    dcb.DCBlength= sizeof(DCB);

    dcb.ByteSize=8;

    //L'électronique ne fonctionne que sous 19200 Bd.
    dcb.BaudRate=CBR_19200;

    dcb.fBinary=true;
    dcb.fParity=false;

    dcb.fOutxCtsFlow=false;     //pas supposé causer de prob si signal appliqué
    dcb.fOutxDsrFlow= false;    //pas supposé causer de prob si signal appliqué

    dcb.fDtrControl=DTR_CONTROL_ENABLE;
    dcb.fRtsControl=RTS_CONTROL_ENABLE;

    dcb.fDsrSensitivity=false;
    dcb.Parity= NOPARITY;

    dcb.StopBits = TWOSTOPBITS;

    dcb.XoffLim = 16;
    dcb.XonLim = 16;


    SetCommState(hcom,&dcb);

    CommTimeouts.ReadIntervalTimeout         = 10;
    CommTimeouts.ReadTotalTimeoutMultiplier  = 0;
    CommTimeouts.ReadTotalTimeoutConstant    = 100;
    CommTimeouts.WriteTotalTimeoutMultiplier = 0;
    CommTimeouts.WriteTotalTimeoutConstant   = 100;
    SetCommTimeouts(hcom,&CommTimeouts);

    portConnected = true;
    ui->labelConnectionStatus->setText("Connected");
    ui->pushButtonConnect->setText("Disconnect");
    connect(waitForNextWriting,SIGNAL(timeout()),this,SLOT(writeOnPort()));
    return true;
}

void SerialPort::disconnectPort()
{
    disconnect(waitForNextWriting,SIGNAL(timeout()),this,SLOT(writeOnPort()));
    CloseHandle(hcom);
    portConnected = false;
    ui->labelConnectionStatus->setText("Not Connected");
    ui->pushButtonConnect->setText("Connect");
    ui->label_DigitWritingTime->setText("Unspecified");
}

void SerialPort::writeOnPort()
{
    //COMMUNICATION
    /*    Tx -> Data     */
    /*    RTS -> Strobe  */

    tempsDEcriture->start();

    //Writing
    if(numberOfAddresses > 0)
    {
        for(int i = 0; i<numberOfAddresses; i++)
        {
            //ÉCRITURE D'UNE ADRESSE
            long donnee = (long)dataToTransmit[i];
            DWORD transmitted;
            WriteFile(hcom,&donnee,1,&transmitted,NULL);
            Sleep(2);
        }

        //STROBE
        EscapeCommFunction(hcom,SETRTS);
        EscapeCommFunction(hcom,CLRRTS);
        EscapeCommFunction(hcom,SETRTS);

        //STATISTIQUES D'ÉCRITURE
        ui->label_DigitWritingTime->setNum(tempsDEcriture->elapsed());    //on écrit le temps que ca a pris à écrire
        waitForNextWriting->start(10);    //on crée un délais de 1ms avant la prochaine écriture
    }
}

bool SerialPort::setNumberOfAddresses(int numOfAddr)
{
    if(numberOfAddresses > 0)
    {
        return false;
    }
    else
    {
        dataToTransmit = new int[numOfAddr];
        /* Fill everything with 0s */
        for(int i = 0; i < numOfAddr; i++)
        {
            dataToTransmit[i] = 0;
        }
        numberOfAddresses = numOfAddr;
    }
    return true;
}

bool SerialPort::setData(int iData, int iAddress)
{
    if(iAddress > 0 && iAddress < numberOfAddresses)
    {
        dataToTransmit[iAddress] = iData;
        return true;
    }
    return false;
}
