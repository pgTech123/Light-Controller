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

    /* Menu File */
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    /* View Menu Connections */
    connect(&fadersWindows, SIGNAL(hidden()), this, SLOT(setFadersHidden()));
    connect(&timingWindows, SIGNAL(hidden()), this, SLOT(setTimingHidden()));
    connect(&fixturesWindow, SIGNAL(hidden()), this, SLOT(setFixtureHidden()));
    connect(&groupsWindows, SIGNAL(hidden()), this, SLOT(setGroupHidden()));
    connect(&scenesWindows, SIGNAL(hidden()), this, SLOT(setSceneHidden()));
    connect(&serialPortWindow, SIGNAL(hidden()), this, SLOT(setSerialPortHidden()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::requestToRecord()
{
    emit record();
    m_bAllChangeSaved = false;
}

void MainWindow::closeEvent(QCloseEvent* closeEvent)
{
    if(m_bAllChangeSaved){
        qApp->exit();
    }
    else{
        int answer = QMessageBox::warning(this, "Modif not saved",
                             tr("The document has been modified.\n"
                             "Do you want to save changes?"),
                             QMessageBox::Save | QMessageBox::No
                             | QMessageBox::Cancel,
                             QMessageBox::Save);

        if(answer == QMessageBox::Save)    //Oui on veut enregistrer
        {
            on_actionSave_triggered();    //on tente d'enregistrer

            //ça ti marché?
            if(m_bAllChangeSaved)
            {
                qApp->exit();
            }
            else
            {
                closeEvent->ignore();
            }
        }

        else if(answer == QMessageBox::No)
        {
            qApp->exit();
        }

        else
        {
           closeEvent->ignore();                //On ne quitte pas
        }
    }
}

/* Menu File */
void MainWindow::on_actionSave_as_triggered()
{
    /*TODO*/
}

void MainWindow::on_actionSave_triggered()
{
    /*TODO*/
}

/* Submenu Open */
void MainWindow::on_actionShow_triggered()
{
    /*TODO*/
}

void MainWindow::on_actionCue_List_triggered()
{
    /*TODO*/
}

void MainWindow::on_actionScenes_List_triggered()
{
    /*TODO*/
}

void MainWindow::on_actionGroup_List_triggered()
{
    /*TODO*/
}

/* Menu Edit */
void MainWindow::on_actionPrevious_triggered()
{
    emit previous();
}

void MainWindow::on_actionNext_triggered()
{
    emit next();
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
