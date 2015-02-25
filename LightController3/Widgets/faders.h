#ifndef FADERS_H
#define FADERS_H

#include <QDockWidget>
#include "dockablewindow.h"

namespace Ui {
class Faders;
}

class Faders : public DockableWindow
{
    Q_OBJECT

public:
    explicit Faders(QWidget *parent = 0);
    ~Faders();

private:
    Ui::Faders *ui;
};

#endif // FADERS_H
