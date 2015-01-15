#ifndef TIMING_H
#define TIMING_H

#include <QDockWidget>
#include "dockablewindow.h"

namespace Ui {
class Timing;
}

class Timing : public DockableWindow
{
    Q_OBJECT

public:
    explicit Timing(QWidget *parent = 0);
    ~Timing();

private:
    Ui::Timing *ui;
};

#endif // TIMING_H
