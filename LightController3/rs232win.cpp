#ifdef WIN32

#include "rs232win.h"
RS232::RS232()
{

}

bool RS232::init(const char* comPortName)
{
    hcom=CreateFileA(comPortName,
                  GENERIC_READ|GENERIC_WRITE,
                  0,
                  NULL,
                  OPEN_EXISTING,
                  0,
                  NULL);
    if(hcom==INVALID_HANDLE_VALUE)
    {
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

    return true;
}

void RS232::disconnect()
{
    CloseHandle(hcom);
}

void RS232::write(long data)
{
    DWORD transmitted;
    WriteFile(hcom,&data,1,&transmitted,NULL);
    Sleep(2);
}

void RS232::strobe()
{
    EscapeCommFunction(hcom,SETRTS);
    EscapeCommFunction(hcom,CLRRTS);
    EscapeCommFunction(hcom,SETRTS);
}
#endif
