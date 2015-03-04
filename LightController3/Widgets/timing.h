#ifndef TIMING_H
#define TIMING_H

#include <QDockWidget>
#include <QString>
#include <QList>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDesktopWidget>
#include <fmod.hpp>
#include <fmod_common.h>
#include "dockablewindow.h"
#include "lightsavailable.h"
#include "faders.h"
#include "timing/fixturemaintimingui.h"

#include <iostream>
using namespace std;

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
    void initializeFMOD();
    void releaseFMOD();
    void loadSong(QString songPath);

private slots:
    void on_pushButtonPlay_clicked();

private:
    Ui::Timing *ui;

    LightsAvailable *m_ptrLightsAvailable;
    Faders *m_ptrFaders;

    FixtureMainTimingUI *m_FixtureMainTimingArr;

    //Sound System (powered by FMOD)
    bool m_bIsPlaying;
    unsigned int m_uiCursor_ms;
    unsigned int m_uiSongLenght_ms;
    FMOD::System *m_fmodSystem;
    FMOD::Sound *m_fmodMusic;
    FMOD::Channel *m_fmodChannel;
};

#endif // TIMING_H
