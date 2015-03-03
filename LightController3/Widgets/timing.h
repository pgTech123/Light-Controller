#ifndef TIMING_H
#define TIMING_H

#include <QDockWidget>
#include <QString>
#include <QList>
#include "dockablewindow.h"
#include "lightsavailable.h"
#include "faders.h"
#include "timing/fixturemaintimingui.h"

namespace Ui {
class Timing;
}

class Timing : public DockableWindow
{
    Q_OBJECT

public:
    explicit Timing(QWidget *parent = 0);
    ~Timing();

    bool loadShow(QString path);
    bool saveShow(bool saveAs = false);
    void setPathToScenes(QString path);
    void setPathToGroups(QString path);
    QString getPathToScenes();
    QString getPathToGroups();

    void reset();

    void setLightsAvailable(LightsAvailable *lightsAvailable);
    void setFaders(Faders *faders);

private:
    Ui::Timing *ui;

    LightsAvailable *m_ptrLightsAvailable;
    Faders *m_ptrFaders;

    FixtureMainTimingUI *m_FixtureMainTimingArr;
};

#endif // TIMING_H
