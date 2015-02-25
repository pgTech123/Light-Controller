#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QDesktopWidget>

//Widgets
#include "faders.h"
#include "timing.h"
#include "fixtures.h"
#include "groups.h"
#include "scenes.h"
#include "serialport.h"
#include "aboutlightcontroller.h"

//History
#include "History/history.h"

/*DEBUG*/
#include <iostream>
using namespace std;
/*END DEBUG*/

#define HISTORY_LENGTH      50

typedef enum{
    GO_ON, ABORT
}SavingStatus;

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

private:
    void initialize();

    SavingStatus doYouWantToSaveChanges();

signals:
    void undoSignal();
    void redoSignal();

private slots:
    void enableUndo(bool enable);
    void enableRedo(bool enable);
    void modificationUnsaved();

    /* Menu File */
    void on_actionSave_as_triggered();
    void on_actionSave_triggered();
        /* Submenu Open */
        void on_actionShow_triggered();
        void on_actionScenes_List_triggered();
        void on_actionGroup_List_triggered();
    void on_actionQuit_triggered();

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

    bool m_bAllModifSaved;

    //Widgets
    Faders fadersWindows;
    Timing timingWindows;
    Fixtures fixturesWindow;
    Groups groupsWindows;
    Scenes scenesWindows;
    SerialPort serialPortWindow;
    AboutLightController aboutLightController;

    //History
    History *m_GlobalHistory;
};

#endif // MAINWINDOW_H