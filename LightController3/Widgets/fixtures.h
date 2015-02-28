/*************************************************************************
 * Project   :      GV Light Controller 3
 * Filename  :      fixture.h
 * Author    :      Pascal Gendron
 * Version   :      3.0
 *
 * Copyright :      GNU GENERAL PUBLIC LICENSE
 * ************************************************************************/

#ifndef FIXTURES_H
#define FIXTURES_H

#include <QDockWidget>
#include <QListWidgetItem>
#include "dockablewindow.h"
#include "lightsavailable.h"
#include "faders.h"

namespace Ui {
class Fixtures;
}

class Fixtures : public DockableWindow
{
    Q_OBJECT

public:
    explicit Fixtures(QWidget *parent = 0);
    ~Fixtures();

    void setLightsAvailable(LightsAvailable *lightsAvailable);
    void setFaders(Faders *faders);

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void unselectAll(FixtureSelector);

private:
    void readStructureInfo();

private:
    Ui::Fixtures *ui;

    Faders *m_ptrFaders;
    LightsAvailable *m_ptrLightsAvailable;
};

#endif // FIXTURES_H
