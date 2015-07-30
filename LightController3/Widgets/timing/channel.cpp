#include "channel.h"

Channel::Channel()
{
}


void Channel::setVisible(bool visible)
{
    if(visible)
        cout << "Visible" << endl;
    else
        cout << "Non Visible" << endl;
}
