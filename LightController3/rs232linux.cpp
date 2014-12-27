#ifdef __unix__
#include "rs232linux.h"

RS232::RS232()
{
}

bool RS232::init(const char* comPortName)
{
    return false;
}

void RS232::disconnect()
{

}

void RS232::write(long data)
{

}

void RS232::strobe()
{

}
#endif
