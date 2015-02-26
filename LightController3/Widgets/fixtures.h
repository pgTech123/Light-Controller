#ifndef FIXTURES_H
#define FIXTURES_H

#include <QDockWidget>
#include <QListWidgetItem>
#include "dockablewindow.h"
#include "lightsavailable.h"

//DEBUG
#include <iostream>
using namespace std;
//END DEBUG

namespace Ui {
class Fixtures;
}

class Fixtures : public DockableWindow
{
    Q_OBJECT

public:
    explicit Fixtures(QWidget *parent = 0);
    ~Fixtures();

    void unselectAll();
    void setLightsAvailable(LightsAvailable *lightsAvailable);

private slots:
    void on_listWidget_currentRowChanged(int index);

private:
    void readStructureInfo();

private:
    Ui::Fixtures *ui;

    LightsAvailable *m_ptrLightsAvailable;
};

#endif // FIXTURES_H
