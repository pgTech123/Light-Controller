#include "timing.h"
#include "ui_timing.h"

Timing::Timing(QWidget *parent) :
    DockableWindow(parent),
    ui(new Ui::Timing)
{
    ui->setupUi(this);
    ui->dockWidgetContents->setLayout(ui->verticalLayout);
    ui->scrollAreaWidgetContents->setLayout(ui->verticalLayoutScrollArea);

    m_ptrLightsAvailable = NULL;
    m_ptrFaders = NULL;
    m_FixtureMainTimingArr = NULL;
}

Timing::~Timing()
{
    delete ui;
    if(m_FixtureMainTimingArr != NULL){
        delete[] m_FixtureMainTimingArr;
    }
}

bool Timing::loadShow(QString path)
{
    return true;
}

bool Timing::saveShow(bool saveAs)
{
    //TODO
    return true;
}

void Timing::setPathToScenes(QString path)
{

}

void Timing::setPathToGroups(QString path)
{

}

QString Timing::getPathToScenes()
{
    return QString("");
}

QString Timing::getPathToGroups()
{
    return QString("");
}

void Timing::reset()
{

}

void Timing::setLightsAvailable(LightsAvailable *lightsAvailable)
{
    m_ptrLightsAvailable = lightsAvailable;
    int fixtAvailable = m_ptrLightsAvailable->getNumOfFixturesAvailable();
    m_FixtureMainTimingArr = new FixtureMainTimingUI[fixtAvailable];

    for(int i = 0; i < fixtAvailable; i++)
    {
        //Fixture name
        m_FixtureMainTimingArr[i].setFixtureName(m_ptrLightsAvailable->getFixtureName(i));

        //Fader names
        QList<QString> faderNameList;
        for(int j = 0; j < m_ptrLightsAvailable->getNumOfFadersForFixture(i); j++){
            faderNameList.append(m_ptrLightsAvailable->getFaderName(i, j));
        }
        m_FixtureMainTimingArr[i].addFaderNames(faderNameList);

        //Add to UI
        ui->verticalLayoutScrollArea->addWidget(&m_FixtureMainTimingArr[i]);
    }
}

void Timing::setFaders(Faders *faders)
{
    m_ptrFaders = faders;
}
