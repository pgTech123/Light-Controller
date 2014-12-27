#ifndef RS232LINUX_H
#define RS232LINUX_H

#ifdef __unix__
class RS232
{
public:
    RS232();
    bool init(const char* comPortName);
    void disconnect();
    void write(long data);
    void strobe();
};
#endif
#endif // RS232LINUX_H
