#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QDockWidget>
#include "dockablewindow.h"
#include <QMessageBox>
#include <QByteArray>
#include <QTime>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <iostream>
using namespace std;

namespace Ui {
class SerialPort;
}

class SerialPort : public DockableWindow
{
    Q_OBJECT

public:
    explicit SerialPort(QWidget *parent = 0);
    ~SerialPort();

    bool initConnection(bool silent = false);
    void disconnectPort();

    void autoconnect();

    bool setNumberOfAddresses(int numOfAddr);
    bool setData(int iData, int iAddress);

private slots:
    void on_pushButtonConnect_clicked();
    void writeOnPort();

private:
    Ui::SerialPort *ui;

    bool m_bPortConnected;
    QList<QSerialPortInfo> m_PortAvailable;
    int m_iSelectedPort;
    QSerialPort *m_serialPort;

    /* Timers */
    QTime *m_writingTime;
    QTimer *m_timerWaitForNextWriting;

    /* Data to transmit */
    int m_iNumberOfAddresses;
    unsigned char *m_ucDataToTransmit;
};

#endif // SERIALPORT_H
