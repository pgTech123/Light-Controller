//DEPENDENCY:   FMOD Sound System, copyright © Firelight Technologies Pty, Ltd.

#ifndef TIMING_H
#define TIMING_H

#include <QDockWidget>
#include <QString>
#include <QList>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDesktopWidget>
#include <QTimer>
#include <fmod.hpp>
#include <fmod_common.h>
#include "dockablewindow.h"
#include "lightsavailable.h"
#include "faders.h"
#include "timing/fixturemaintimingui.h"

#include <iostream>
using namespace std;

#define TIME_RESOLUTION     10  //ms

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

    unsigned int getSongTotalLenght();
    unsigned int getSongCurrentTime();
    void setSongCurrentTime(unsigned int time_ms);

private:
    void initializeFMOD();
    void releaseFMOD();
    void loadSong(QString songPath);

    void setTimeUI();

private slots:
    void on_pushButtonSoundtrack_clicked();
    void on_pushButtonAddCue_clicked();
    void on_pushButtonSharpTransition_clicked();
    void on_pushButtonDeleteCue_clicked();

    void on_pushButtonPlay_clicked();
    void on_pushButtonRestart_clicked();
    void on_pushButtonPreviousCue_clicked();
    void on_pushButtonNextCue_clicked();
    void on_pushButtonGoToEnd_clicked();

    //Callback
    void update();

private:
    Ui::Timing *ui;

    LightsAvailable *m_ptrLightsAvailable;
    Faders *m_ptrFaders;

    FixtureMainTimingUI *m_FixtureMainTimingArr;

    //Callback timer
    QTimer *m_CallbackTimer;

    //Sound System (powered by FMOD)
    bool m_bIsPlaying;
    unsigned int m_uiCursor_ms;
    unsigned int m_uiSongLenght_ms;
    FMOD::System *m_fmodSystem;
    FMOD::Sound *m_fmodMusic;
    FMOD::Channel *m_fmodChannel;
};

#endif // TIMING_H
