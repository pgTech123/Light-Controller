#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QDockWidget>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTime>
#include <QTimer>

#ifdef WIN32
// Windows
    #include "rs232win.h"
#elif __unix__
// Linux
    #include "rs232linux.h"
#else
//NOT SUPPORTED: TODO: error
#endif

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

    /* RS232 */
    RS232 m_rs232;

    /* Timers */
    QTime *tempsDEcriture;
    QTimer *waitForNextWriting;

    /* Data to transmit */
    int numberOfAddresses;
    int *dataToTransmit;
};

#endif // SERIALPORT_H
