#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Docking Windows */
    this->addDockWidget(Qt::LeftDockWidgetArea, &fadersWindows);
    this->addDockWidget(Qt::LeftDockWidgetArea, &timingWindows);
    this->addDockWidget(Qt::RightDockWidgetArea, &fixturesWindow);
    this->addDockWidget(Qt::RightDockWidgetArea, &groupsWindows);
    this->addDockWidget(Qt::RightDockWidgetArea, &scenesWindows);
    this->addDockWidget(Qt::RightDockWidgetArea, &serialPortWindow);

    /* View Menu Connections */
    connect(&fadersWindows, SIGNAL(hidden()), this, SLOT(setFadersHidden()));
    connect(&timingWindows, SIGNAL(hidden()), this, SLOT(setTimingHidden()));
    connect(&fixturesWindow, SIGNAL(hidden()), this, SLOT(setFixtureHidden()));
    connect(&groupsWindows, SIGNAL(hidden()), this, SLOT(setGroupHidden()));
    connect(&scenesWindows, SIGNAL(hidden()), this, SLOT(setSceneHidden()));
    connect(&serialPortWindow, SIGNAL(hidden()), this, SLOT(setSerialPortHidden()));

    //Init Everything Else
    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_GlobalHistory;
}

void MainWindow::closeEvent(QCloseEvent* closeEvent)
{
    if(m_bAllModifSaved){
        qApp->exit();
    }
    else{
        if(doYouWantToSaveChanges() == GO_ON){
            qApp->exit();
        }
        else{
            closeEvent->ignore();
        }
    }
}

void MainWindow::initialize()
{
    //Initial Project Status
    m_bAllModifSaved = true;
    ui->actionPrevious->setDisabled(true);
    ui->actionNext->setDisabled(true);

    //History
    m_GlobalHistory = new History(HISTORY_LENGTH);
    //Insert all other element that needs to be connected to history here

    connect(m_GlobalHistory, SIGNAL(newElementInHistory()), this, SLOT(modificationUnsaved()));
    connect(m_GlobalHistory, SIGNAL(enableUndoButton(bool)), this, SLOT(enableUndo(bool)));
    connect(m_GlobalHistory, SIGNAL(enableRedoButton(bool)), this, SLOT(enableRedo(bool)));
    connect(this, SIGNAL(undoSignal()), m_GlobalHistory, SLOT(undo()));
    connect(this, SIGNAL(redoSignal()), m_GlobalHistory, SLOT(redo()));

    //TODO: read available
}

SavingStatus MainWindow::doYouWantToSaveChanges()
{
    /* Ask if we want to save changes */
    int answer = QMessageBox::warning(this, "Modification not saved",
                         tr("The document has been modified.\n"
                         "Do you want to save changes?"),
                         QMessageBox::Save | QMessageBox::No
                         | QMessageBox::Cancel,
                         QMessageBox::Save);

    /* Catch answer and do the action associated to it */
    if(answer == QMessageBox::Save){
        on_actionSave_triggered();
        /* We verify if it worked */
        if(m_bAllModifSaved){
            return GO_ON;
        }
        else{
            return ABORT;
        }
    }
    else if(answer == QMessageBox::No){
        return GO_ON;
    }
    else{
       return ABORT;
    }

}


/* History Control */
void MainWindow::enableUndo(bool enabled)
{
    ui->actionPrevious->setEnabled(enabled);
}

void MainWindow::enableRedo(bool enabled)
{
    ui->actionNext->setEnabled(enabled);
}

void MainWindow::modificationUnsaved()
{
    m_bAllModifSaved = false;
}


/* Menu File */
void MainWindow::on_actionSave_as_triggered()
{
    /*TODO*/
    m_bAllModifSaved = true;
}

void MainWindow::on_actionSave_triggered()
{
    /*TODO*/
    m_bAllModifSaved = true;
}

/* Submenu Open */
void MainWindow::on_actionShow_triggered()
{
    if(!m_bAllModifSaved){
        if(doYouWantToSaveChanges() == ABORT){
            return;
        }
    }
    QString path = QFileDialog::getOpenFileName(this, "Load Show", QString(),
                                                "Show(*.gsw)");

    if(path == NULL){   //Cancel Button Pressed
        return;
    }

    if(timingWindows.loadShow(path)){
        QMessageBox::warning(this, "ERROR",
                             "An error orrured while trying to load the show");
    }

    //Open Scenes and Groups associated with the show
    if(scenesWindows.loadScene(timingWindows.getPathToScenes())){
        QMessageBox::warning(this, "ERROR",
                             "An error orrured while trying to load the scenes");
    }
    if(groupsWindows.loadGroups(timingWindows.getPathToGroups())){
        QMessageBox::warning(this, "ERROR",
                             "An error orrured while trying to load the groups");
    }
}

void MainWindow::on_actionScenes_List_triggered()
{
    if(!m_bAllModifSaved){
        if(doYouWantToSaveChanges() == ABORT){
            return;
        }
    }
    QString path = QFileDialog::getOpenFileName(this, "Load Scenes", QString(),
                                                "Scenes(*.gsn)");

    if(path == NULL){   //Cancel Button Pressed
        return;
    }
    if(scenesWindows.loadScene(path)){
        QMessageBox::warning(this, "ERROR",
                             "An error orrured while trying to load the scenes");
    }
}

void MainWindow::on_actionGroup_List_triggered()
{
    if(!m_bAllModifSaved){
        if(doYouWantToSaveChanges() == ABORT){
            return;
        }
    }
    QString path = QFileDialog::getOpenFileName(this, "Load Groups", QString(),
                                                "Groups(*.ggp)");

    if(path == NULL){   //Cancel Button Pressed
        return;
    }
    if(groupsWindows.loadGroups(path)){
        QMessageBox::warning(this, "ERROR",
                             "An error orrured while trying to load the groups");
    }
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

/* Menu Edit */
void MainWindow::on_actionPrevious_triggered()
{
    m_bAllModifSaved = false;
    emit undoSignal();
}

void MainWindow::on_actionNext_triggered()
{
    m_bAllModifSaved = false;
    emit redoSignal();
}

void MainWindow::on_actionAutoconnect_triggered()
{
    serialPortWindow.autoconnect();
}

/* Menu View */
void MainWindow::on_actionFaders_triggered()
{
    if(!ui->actionFaders->isChecked()){
        fadersWindows.hide();
    }
    else
    {
        fadersWindows.show();
    }
}

void MainWindow::on_actionTiming_triggered()
{
    if(!ui->actionTiming->isChecked()){
        timingWindows.hide();
    }
    else
    {
        timingWindows.show();
    }
}

void MainWindow::on_actionFixture_triggered()
{
    if(!ui->actionFixture->isChecked()){
        fixturesWindow.hide();
    }
    else
    {
        fixturesWindow.show();
    }
}

void MainWindow::on_actionGroups_triggered()
{
    if(!ui->actionGroups->isChecked()){
        groupsWindows.hide();
    }
    else{
        groupsWindows.show();
    }
}

void MainWindow::on_actionScenes_triggered()
{
    if(!ui->actionScenes->isChecked()){
        scenesWindows.hide();
    }
    else{
        scenesWindows.show();
    }
}

void MainWindow::on_actionSerial_Port_Interface_triggered()
{
    if(!ui->actionSerial_Port_Interface->isChecked()){
        serialPortWindow.hide();
    }
    else{
        serialPortWindow.show();
    }
}

/* Menu About Us */
void MainWindow::on_actionAbout_Light_Controller_3_triggered()
{
    aboutLightController.show();
}


/* Hidding Status Functions */
void MainWindow::setFadersHidden()
{
    ui->actionFaders->setChecked(false);
}

void MainWindow::setTimingHidden()
{
    ui->actionTiming->setChecked(false);
}

void MainWindow::setFixtureHidden()
{
    ui->actionFixture->setChecked(false);
}

void MainWindow::setGroupHidden()
{
    ui->actionGroups->setChecked(false);
}

void MainWindow::setSceneHidden()
{
    ui->actionScenes->setChecked(false);
}

void MainWindow::setSerialPortHidden()
{
    ui->actionSerial_Port_Interface->setChecked(false);
}