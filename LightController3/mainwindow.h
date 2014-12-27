#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "faders.h"
#include "timing.h"
#include "fixtures.h"
#include "groups.h"
#include "scenes.h"
#include "serialport.h"
#include "aboutlightcontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent*);

signals:
    void record();
    void previous();
    void next();

private slots:
    /* ctrl-z fnc */
    void requestToRecord();

    /* Menu File */
    void on_actionSave_as_triggered();
    void on_actionSave_triggered();
        /* Submenu Open */
        void on_actionShow_triggered();
        void on_actionCue_List_triggered();
        void on_actionScenes_List_triggered();
        void on_actionGroup_List_triggered();

    /* Menu Edit */
    void on_actionPrevious_triggered();
    void on_actionNext_triggered();
    void on_actionAutoconnect_triggered();

    /* Menu View */
    void on_actionFaders_triggered();
    void on_actionTiming_triggered();
    void on_actionFixture_triggered();
    void on_actionGroups_triggered();
    void on_actionScenes_triggered();
    void on_actionSerial_Port_Interface_triggered();

    /* Menu About Us */
    void on_actionAbout_Light_Controller_3_triggered();

    /* Hidding Functions */
    void setFadersHidden();
    void setTimingHidden();
    void setFixtureHidden();
    void setGroupHidden();
    void setSceneHidden();
    void setSerialPortHidden();


private:
    Ui::MainWindow *ui;

    bool m_bAllChangeSaved;

    Faders fadersWindows;
    Timing timingWindows;
    Fixtures fixturesWindow;
    Groups groupsWindows;
    Scenes scenesWindows;
    SerialPort serialPortWindow;
    AboutLightController aboutLightController;
};

#endif // MAINWINDOW_H
