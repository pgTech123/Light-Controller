#ifndef CHANNEL_H
#define CHANNEL_H

#include <QWidget>

//DEBUG
#include <iostream>
//END DEBUG

using namespace std;

class Channel: public QWidget
{

    Q_OBJECT

public:
    Channel();

public slots:
    void setVisible(bool visible);
};

#endif // CHANNEL_H
