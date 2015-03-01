/*************************************************************************
 * Project   :      GV Light Controller 3
 * Filename  :      faders.h
 * Author    :      Pascal Gendron
 * Version   :      3.0
 *
 * Copyright :      GNU GENERAL PUBLIC LICENSE
 * ************************************************************************/

#ifndef FADERS_H
#define FADERS_H

#include <QDockWidget>
#include <QList>
#include <QString>
#include <vector>
#include "dockablewindow.h"
#include "lightsavailable.h"
#include "singlefader.h"

using namespace std;

typedef struct{
    vector<int> faderValue;
}FixtureStatus;

typedef struct{
    vector<FixtureStatus> fixtureStatus;
}LightsStatus;

typedef enum{
    FIXTURE, GROUP
}FixtureSelector;

namespace Ui {
class Faders;
}

class Faders : public DockableWindow
{
    Q_OBJECT

public:
    explicit Faders(QWidget *parent = 0);
    ~Faders();

    void setLightsAvailable(LightsAvailable *lightsAvailable);

    void accessFixture(int fixture);
    void accessFixtures(QList<int> fixture, QString name="Group");

    int getFader(int fixture, int fader);

public slots:
    void setFader(int fixture, int fader, int value);
    void setFaderFromSlider(int fixture, int fader, int value);

private:
    void deleteFaders();

signals:
    void unselect(FixtureSelector);
    void valueChanged(int, int, int);

private:
    Ui::Faders *ui;

    LightsAvailable *m_ptrLightsAvailable;
    LightsStatus m_LightsStatus;
    SingleFader *m_SingleFaderArr;
};

#endif // FADERS_H
