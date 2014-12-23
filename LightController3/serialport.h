#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QDockWidget>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTime>
#include <QTimer>
#include <windows.h>

namespace Ui {
class SerialPort;
}

class SerialPort : public QDockWidget
{
    Q_OBJECT

public:
    explicit SerialPort(QWidget *parent = 0);
    ~SerialPort();

    void closeEvent(QCloseEvent*);

    bool initConnection(bool silent = false);
    void disconnectPort();

    void autoconnect();

    bool setNumberOfAddresses(int numOfAddr);
    bool setData(int iData, int iAddress);

signals:
    void hidden();

private slots:
    void on_pushButtonConnect_clicked();
    void writeOnPort();

private:
    Ui::SerialPort *ui;

    bool portConnected;

    /* Serial port data */
    HANDLE hcom;
    DCB dcb;
    _COMMTIMEOUTS CommTimeouts;

    /* Timers */
    QTime *tempsDEcriture;
    QTimer *waitForNextWriting;

    /* Data to transmit */
    int numberOfAddresses;
    int *dataToTransmit;
};

#endif // SERIALPORT_H
