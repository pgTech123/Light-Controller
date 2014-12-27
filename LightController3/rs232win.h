#ifndef RS232WIN_H
#define RS232WIN_H

#ifdef WIN32
#include <windows.h>

class RS232
{
public:
    RS232();

    bool init(const char* comPortName);
    void disconnect();
    void write(long data);
    void strobe();

private:
    /* Serial port data */
    HANDLE hcom;
    DCB dcb;
    _COMMTIMEOUTS CommTimeouts;
};

#endif
#endif // RS232WIN_H
